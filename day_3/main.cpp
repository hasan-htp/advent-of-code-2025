#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using banks = std::vector<std::vector<int>>;

void print(banks input) {
    for (const auto &line : input) {
        for (int num : line) {
            std::cout << num;
        }
        std::cout << std::endl;
    }
}

auto battery_banks_reader(const std::string &path) {
    banks ret;

    std::ifstream ifs(path);
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            std::vector<int> numbers;
            for (char c : line) {
                numbers.push_back(static_cast<int>(c - '0'));
            }
            ret.emplace_back(std::move(numbers));
        }
    }

    return ret;
}

namespace part1 {

int solution(const banks &banks) {
    int sum = 0;
    for (const auto &bank : banks) {
        auto first_digit = std::max_element(bank.begin(), bank.end() - 1);
        auto second_digit = std::max_element(first_digit + 1, bank.end());

        const int num = (*first_digit) * 10 + (*second_digit);

        sum += num;
    }
    return sum;
}
} // namespace part1

namespace part2 {

uint64_t solution(const banks &banks) {
    uint64_t sum = 0;
    for (const auto &bank : banks) {

        uint64_t num = 0;
        auto digit = bank.begin();
        for (int i = 11; i >= 0; i--) {
            digit = std::max_element(digit, bank.end() - i);
            num += (*digit) * std::pow(10UL, i);

            digit++;
        }

        sum += num;
    }
    return sum;
}
} // namespace part2

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    auto input = battery_banks_reader(path);
    std::cout << part1::solution(input) << std::endl;
    std::cout << part2::solution(input) << std::endl;

    return 0;
}