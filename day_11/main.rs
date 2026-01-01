use std::collections::HashMap;
use std::env;
use std::fs;

fn reader(path: &str) -> HashMap<String, Vec<String>> {
    let input = fs::read_to_string(path)
        .expect("Failed to read file");

    let mut graph: HashMap<String, Vec<String>> = HashMap::new();

    for line in input.lines() {
        let line = line.trim();
        if line.is_empty() {
            continue;
        }

        let parts: Vec<&str> = line.split(':').collect();
        let device = parts[0].trim().to_string();

        let outputs = if parts.len() > 1 {
            parts[1]
                .split_whitespace()
                .map(|s| s.to_string())
                .collect()
        } else {
            Vec::new()
        };

        graph.insert(device, outputs);
    }

    graph
}

fn count_paths(
    current: &str,
    graph: &HashMap<String, Vec<String>>,
    memo: &mut HashMap<String, usize>,
) -> usize {
    if current == "out" {
        return 1;
    }

    if let Some(&cached) = memo.get(current) {
        return cached;
    }

    let mut total_paths = 0;

    if let Some(neighbors) = graph.get(current) {
        for next in neighbors {
            total_paths += count_paths(next, graph, memo);
        }
    }

    memo.insert(current.to_string(), total_paths);
    total_paths
}

fn solution(graph: &HashMap<String, Vec<String>>) -> usize {
    let mut memo = HashMap::new();
    count_paths("you", graph, &mut memo)
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() != 2 {
        eprintln!("Usage: {} <input_file>", args[0]);
        std::process::exit(1);
    }

    let input_path = &args[1];
    let graph = reader(input_path);
    let result = solution(&graph);

    println!("{}", result);
}
