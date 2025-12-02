
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct ID {
    ID(const std::string &pair) {
        size_t pos = pair.find('-');
        auto first_str = pair.substr(0, pos);
        auto last_str = pair.substr(pos + 1, pair.length());

        first = std::stoll(first_str);
        last = std::stoll(last_str);
    }

    uint64_t first;
    uint64_t last;
};

std::vector<ID> id_reader(const std::string &path) {
    std::ifstream ifsr(path);

    // c++ shit
    std::string content((std::istreambuf_iterator<char>(ifsr)), (std::istreambuf_iterator<char>()));

    std::vector<ID> ids;

    size_t start = 0, end = 0;
    while (end != std::string::npos) {
        end = content.find(',', start);
        auto pair = content.substr(start, end - start);
        ids.emplace_back(ID(pair));
        start = end + 1;
    }

    return ids;
}

namespace part1 {

bool is_invalid(uint64_t input) {
    auto s = std::to_string(input);
    const auto size = s.size();
    if (size % 2 != 0) {
        return false;
    }

    auto half = size / 2;
    return s.compare(0, half, s, half, half) == 0;
}

uint64_t solution(const std::vector<ID> &ids) {
    uint64_t res = 0;

    for (const auto &id : ids) {
        for (uint64_t num = id.first; num <= id.last; num++) {
            if (is_invalid(num)) {
                res += num;
            }
        }
    }
    return res;
}
} // namespace part1

namespace part2 {

// example input is 2424 -> ss is 24242424 mid is 42424, 2424 is in 424242 -> return true
// example input is 599 -> ss is 599599 mid is 9959, 599 is NOT in 9959 -> return false

bool is_invalid(uint64_t input) {
    auto s = std::to_string(input);
    auto ss = s + s;
    auto mid = ss.substr(1, ss.size() - 2);
    return mid.find(s) != std::string::npos;
}

uint64_t solution(const std::vector<ID> &ids) {
    uint64_t res = 0;

    for (const auto &id : ids) {
        for (uint64_t num = id.first; num <= id.last; num++) {
            if (is_invalid(num)) {
                res += num;
            }
        }
    }
    return res;
}
} // namespace part2

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    std::string path = argv[1];

    auto input = id_reader(path);

    {
        auto sol = part1::solution(input);
        std::cout << "Part 1: " << sol << std::endl;
    }

    {
        auto sol = part2::solution(input);
        std::cout << "Part 2: " << sol << std::endl;
    }

    return 0;
}