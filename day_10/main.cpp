#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

int solve_machine(const std::string &line) {
    auto lb = line.find('[');
    auto rb = line.find(']');
    std::string diagram = line.substr(lb + 1, rb - lb - 1);

    int n_lights = diagram.size();
    uint64_t target = 0;
    for (int i = 0; i < n_lights; ++i) {
        if (diagram[i] == '#') {
            target |= (1ULL << i);
        }
    }

    std::vector<uint64_t> buttons;
    for (size_t i = rb + 1; i < line.size(); ++i) {
        if (line[i] == '(') {
            uint64_t mask = 0;
            ++i;
            while (line[i] != ')') {
                if (isdigit(line[i])) {
                    int idx = 0;
                    while (isdigit(line[i])) {
                        idx = idx * 10 + (line[i] - '0');
                        ++i;
                    }
                    mask |= (1ULL << idx);
                } else {
                    ++i;
                }
            }
            buttons.push_back(mask);
        }
    }

    int best = std::numeric_limits<int>::max();

    for (int s = 0; s < (1 << buttons.size()); ++s) {
        uint64_t current = 0;
        int press_count = 0;
        for (int i = 0; i < buttons.size(); ++i) {
            if (s & (1 << i)) {
                current ^= buttons[i];
                ++press_count;
            }
        }
        if (current == target) {
            best = std::min(best, press_count);
        }
    }

    return best;
}

int solution(const std::vector<std::string> &lines) {

    int count = 0;
    for (const auto &line : lines) {
        count += solve_machine(line);
    }
    return count;
}

std::vector<std::string> reader(const std::string &path) {
    std::vector<std::string> lines;
    std::string line;

    std::ifstream in(path);
    while (std::getline(in, line)) {
        if (!line.empty())
            lines.push_back(line);
    }
    return lines;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    auto lines = reader(path);

    std::cout << solution(lines) << std::endl;
    return 0;
}
