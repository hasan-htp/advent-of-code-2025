

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Point {
    int x;
    int y;
    int z;

    double distance(const Point &p2) const {
        //
        return std::sqrt((pow(x - p2.x, 2) + pow(y - p2.y, 2) + pow(z - p2.z, 2)));
    }
};

std::vector<Point> reader(const std::string &path) {
    std::vector<Point> output;

    std::ifstream ifs(path);

    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            auto pos_1 = line.find(',', 0);
            int x = std::stoi(line.substr(0, pos_1));

            auto pos_2 = line.find(',', pos_1 + 1);
            int y = std::stoi(line.substr(pos_1 + 1, pos_2));

            int z = std::stoi(line.substr(pos_2 + 1, line.length()));

            output.emplace_back(Point{x, y, z});
        }
    }

    return output;
}

struct Entry {

    double distance;
    size_t i;
    size_t j;
};

int solution(const std::vector<Point> &points) {
    std::unordered_map<size_t, int> connected; // inbdex -> group id
    std::unordered_map<int, int> group_size;   // group id -> size of group

    auto cmp = [](const Entry &a, const Entry &b) { return a.distance > b.distance; };

    std::priority_queue<Entry, std::vector<Entry>, decltype(cmp)> distances(cmp);

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            auto new_dis = points[i].distance(points[j]);
            distances.push(Entry{
                .distance = new_dis,
                .i = i,
                .j = j,
            });
        }
    }

    int group_id = 0;
    int connection_size = 0;
    while (connection_size < 1000) {
        auto shortest = distances.top();
        distances.pop();

        if (!connected.contains(shortest.i) && !connected.contains(shortest.j)) {
            connected[shortest.i] = group_id;
            connected[shortest.j] = group_id;
            group_size[group_id] = 2;
            group_id++;
        } else if (connected.contains(shortest.i) and !connected.contains(shortest.j)) {
            connected[shortest.j] = connected[shortest.i];
            group_size[connected[shortest.j]]++;

        } else if (connected.contains(shortest.j) and !connected.contains(shortest.i)) {
            connected[shortest.i] = connected[shortest.j];
            group_size[connected[shortest.j]]++;
        } else if (connected.contains(shortest.i) && connected.contains(shortest.j)) {
            int gi = connected[shortest.i];
            int gj = connected[shortest.j];
            if (gi != gj) {
                for (auto &[idx, group] : connected) {
                    if (group == gj) {
                        group = gi;
                    }
                }
                group_size[gi] += group_size[gj];
                group_size.erase(gj);
            }
        }
        connection_size++;
    }
    // for (auto &[id, size] : connected) {
    //     std::cout << "connected: id: " << id << " gr:" << size << std::endl;
    // }

    std::vector<int> sizes;
    sizes.reserve(group_size.size());
    for (auto &[id, size] : group_size) {
        sizes.push_back(size);
    }
    std::sort(sizes.begin(), sizes.end(), std::greater<>());

    return sizes[0] * sizes[1] * sizes[2];
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    auto input = reader(path);

    std::cout << solution(input) << std::endl;

    return 0;
}