#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

struct movement {
    bool right;
    int steps;
};

struct position {
    int pos = 50;

    void rotate(const movement &mov) {
        int steps = mov.steps;
        if (steps >= 100) {
            steps = steps % 100;
        }
        if (mov.right) {
            pos = pos + steps;
            pos = pos > 99 ? pos - 100 : pos;
        } else {
            pos = pos - steps;
            pos = pos < 0 ? pos + 100 : pos;
        }
    }

    int rotate_and_count_clicks(const movement &mov) {
        int clicks = 0;
        int steps = mov.steps;
        if (steps >= 100) {
            steps = mov.steps % 100;
            clicks += mov.steps / 100;
        }
        if (mov.right) {
            pos = pos + steps;

            if (pos > 99) {
                if ((pos - steps) != 0) {
                    clicks++;
                }
                pos = pos - 100;
            } else if (pos == 0) {
                clicks++;
            }

        } else {
            pos = pos - steps;

            if (pos < 0) {
                if ((pos + steps) != 0) {
                    clicks++;
                }
                pos = pos + 100;
            } else if (pos == 0) {
                clicks++;
            }
        }

        return clicks;
    }
};

std::vector<movement> reader(const std::string &path) {
    std::vector<movement> ret;

    std::ifstream ifs(path);
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            ret.emplace_back(movement{
                .right = line[0] == 'R' ? true : false,
                .steps = std::stoi(line.substr(1)),
            });
        }
    }
    return ret;
}

namespace part1 {
int solution(const std::vector<movement> &moves) {

    position pos{};
    return std::ranges::count_if(moves, [&pos](const movement &m) {
        pos.rotate(m);
        return pos.pos == 0;
    });
}
} // namespace part1

namespace part2 {
int solution(const std::vector<movement> &moves) {

    position pos{};
    return std::accumulate(moves.begin(), moves.end(), 0, [&](int acc, const movement &m) {
        //
        return acc + pos.rotate_and_count_clicks(m);
    });
}
} // namespace part2

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    const auto input = reader(path);
    std::cout << part1::solution(input) << std::endl;
    std::cout << part2::solution(input) << std::endl;

    return 0;
}