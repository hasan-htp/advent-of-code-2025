#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

struct range {
    uint64_t start;
    uint64_t end;
};

namespace part1 {

int solution(std::vector<range> &fresh_products, std::vector<uint64_t> &products) {
    int count = 0;

    for (auto product : products) {
        for (const auto &fresh_product : fresh_products) {
            if (product >= fresh_product.start && product <= fresh_product.end) {
                count++;
                break;
            }
        }
    }
    return count;
}
} // namespace part1

namespace part2 {

uint64_t solution(std::vector<range> &fresh_products) {
    uint64_t count = 0;
    uint64_t prev_end = 0;

    std::sort(fresh_products.begin(), fresh_products.end(), [](const range &a, const range &b) {
        if (a.start == b.start) {
            return a.end < b.end;
        }
        return a.start < b.start;
    });

    for (const auto &range : fresh_products) {
        if (range.end <= prev_end) {
            continue;
        }

        count += range.end - range.start + 1;

        if (range.start <= prev_end) {
            count -= std::min(static_cast<uint64_t>(prev_end), range.end) - range.start + 1;
        }

        prev_end = range.end;
    }
    return count;
}
} // namespace part2

void reader(const std::string &path, std::vector<range> &fresh_products, std::vector<uint64_t> &products) {

    std::ifstream ifs(path);
    if (ifs.is_open()) {
        std::string line;
        bool the_emtpy_line = false;

        while (std::getline(ifs, line)) {
            if (!the_emtpy_line) {
                if (line.empty()) {
                    the_emtpy_line = true;
                } else {

                    auto pos = line.find('-');
                    uint64_t a = std::stoll(line.substr(0, pos));
                    uint64_t b = std::stoll(line.substr(pos + 1));
                    fresh_products.emplace_back(range{.start = a, .end = b});
                }
            } else {
                uint64_t x = std::stoll(line);
                products.push_back(x);
            }
        }
    }
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    std::vector<range> fresh_products;
    std::vector<uint64_t> products;

    reader(path, fresh_products, products);
    std::cout << part1::solution(fresh_products, products) << std::endl;
    std::cout << part2::solution(fresh_products) << std::endl;

    return 0;
}