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

namespace part1 {

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
} // namespace part1

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    auto input = reader(path);

    std::cout << part1::solution(input) << std::endl;
    // std::cout << part2::solution(input) << std::endl;

    return 0;
}