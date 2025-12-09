#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include <vector>

std::vector<std::string> reader(const std::string &path) {

    std::vector<std::string> output;
    // we dont need first line

    std::ifstream ifs(path);
    if (ifs.is_open()) {
        std::string line;
        std::getline(ifs, line);
        while (std::getline(ifs, line)) {
            output.push_back(std::move(line));
        }
    }

    return output;
}

uint64_t solution(std::vector<std::string> &input) {
    uint64_t split_count = 0;
    size_t len = input[0].length();
    size_t mid = len / 2;
    input[0][mid] = '|';
    for (size_t line = 0; line < input.size() - 1; line++) {
        for (size_t ch = 0; ch < len; ch++) {
            if (input[line][ch] == '|' and input[line + 1][ch] == '.') {
                input[line + 1][ch] = '|';
            } else if (input[line][ch] == '|' and input[line + 1][ch] == '^') {
                split_count++;

                if (ch < len - 1) {
                    input[line + 1][ch + 1] = '|';
                }
                if (ch > 0) {
                    input[line + 1][ch - 1] = '|';
                }
            }
        }
    }
    return split_count;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    auto input = reader(path);

    for (const auto line : input) {
        std::cout << line << std::endl;
    }

    std::cout << std::endl;

    std::cout << solution(input) << std::endl;

    for (const auto line : input) {
        std::cout << line << std::endl;
    }
    return 0;
}
