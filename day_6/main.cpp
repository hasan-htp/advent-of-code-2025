#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

#include <vector>

struct data {
    std::vector<uint64_t> numbers;
    char operation;
};

namespace part1 {
std::vector<data> reader(const std::string &path) {

    size_t data_size = 0;

    {
        std::vector<uint64_t> numbers;
        std::ifstream ifs(path);
        if (ifs.is_open()) {
            std::string line;
            std::getline(ifs, line);
            std::stringstream ss;
            ss << line;
            uint64_t x = 0;
            while (ss >> x) {
                data_size++;
            }
        }
        ifs.close();
    }

    std::vector<data> data(data_size);

    std::ifstream ifs(path);
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {

            std::stringstream ss;
            ss << line;

            if (line[0] == '+' || line[0] == '*') {
                char c = '0';
                size_t i = 0;
                while (ss >> c) {
                    data[i].operation = c;
                    i++;
                }
                break; // last line
            }

            uint64_t x = 0;
            size_t i = 0;
            while (ss >> x) {
                data.at(i).numbers.push_back(x);
                i++;
            }
        }
    }
    return data;
}

} // namespace part1

namespace part2 {

std::vector<data> reader(const std::string &path) {

    std::vector<std::string> rows;
    std::string line;

    {
        std::ifstream ifs(path);
        while (std::getline(ifs, line)) {
            rows.push_back(line);
        }
    }

    std::string op_row = rows.back();
    rows.pop_back();

    size_t width = 0;
    for (auto &r : rows) {
        width = std::max(width, r.size());
    }
    width = std::max(width, op_row.size());

    for (auto &r : rows) {
        r.resize(width, ' ');
    }

    std::vector<std::vector<int>> groups;
    bool in_group = false;

    for (int c = static_cast<int>(width) - 1; c >= 0; --c) {
        bool empty = true;
        for (auto &r : rows)
            if (r[c] != ' ') {
                empty = false;
            }

        if (!empty && !in_group) {
            groups.emplace_back();
            in_group = true;
        }
        if (!empty) {
            groups.back().push_back(c);
        }
        if (empty && in_group) {
            in_group = false;
        }
    }

    size_t data_size = groups.size();
    std::vector<data> result(data_size);

    {
        std::stringstream ssop;
        ssop << op_row;

        size_t op_index = data_size - 1; // to reverse
        char c = '0';
        while (ssop >> c) {
            result[op_index].operation = c;
            op_index--;
        }
    }

    for (size_t i = 0; i < data_size; ++i) {
        auto &cols = groups[i];

        for (int col : cols) {
            std::string digits;
            for (const auto &r : rows) {
                if (r[col] != ' ')
                    digits.push_back(r[col]);
            }
            if (!digits.empty()) {
                result[i].numbers.push_back(std::stoull(digits));
            }
        }

        std::reverse(result[i].numbers.begin(), result[i].numbers.end());
    }

    return result;
}

} // namespace part2

uint64_t solution(const std::vector<data> &alldata) {
    uint64_t sum = 0;
    return std::accumulate(alldata.begin(), alldata.end(), uint64_t{0}, [](uint64_t sum, const data &entry) {
        uint64_t init = entry.operation == '+' ? 0ULL : 1ULL;
        return sum +
               std::accumulate(entry.numbers.begin(), entry.numbers.end(), init, [init](uint64_t sub_acc, uint64_t x) {
                   return init == 0ULL ? sub_acc + x : sub_acc * x;
               });
    });
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    {
        auto input = part1::reader(path);
        std::cout << solution(input) << std::endl;
    }
    {
        auto input = part2::reader(path);
        std::cout << solution(input) << std::endl;
    }

    return 0;
}