

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
};

uint64_t area(const Point &p1, const Point &p2) {
    //
    return static_cast<uint64_t>(std::abs(p1.x - p2.x + 1)) * static_cast<uint64_t>(std::abs(p1.y - p2.y + 1));
}

std::vector<Point> reader(const std::string &path) {

    std::vector<Point> output;
    std::ifstream ifs(path);

    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            auto pos_1 = line.find(',', 0);
            int x = std::stoi(line.substr(0, pos_1));
            int y = std::stoi(line.substr(pos_1 + 1, line.length()));

            output.emplace_back(Point{x, y});
        }
    }

    return output;
}

uint64_t solution(const std::vector<Point> &points) {

    uint64_t biggest = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + i; j < points.size(); ++j) {
            if (points[i].x == points[j].x && points[i].y == points[j].y) {
                continue;
            }

            biggest = std::max(biggest, area(points[i], points[j]));
        }
    }

    return biggest;
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
