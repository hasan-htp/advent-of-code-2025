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

    for (size_t i = 1; i < output.size() - 1; i++) {
        if (output[i].find('^') == std::string::npos) {
            output.erase(output.begin() + i);
            i--;
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

uint64_t count(const std::vector<std::string> &input, std::vector<std::vector<uint64_t>> &dp, size_t row, size_t col) {

    size_t rows = input.size();
    size_t cols = input[0].size();

    if (row == rows - 2) {
        return 1;
    }

    if (dp[row][col] != -1) {
        return dp[row][col];
    }

    dp[row][col] = 0;
    auto below = input[row + 1][col];

    if (below == '.') {
        dp[row][col] = count(input, dp, row + 1, col);
    } else if (below == '^') {
        if (col > 0) {
            dp[row][col] += count(input, dp, row + 1, col - 1);
        }
        if (col + 1 < cols) {
            dp[row][col] += count(input, dp, row + 1, col + 1);
        }
    }

    return dp[row][col];
}

uint64_t solution_2(const std::vector<std::string> &input) {
    size_t rows = input.size();
    size_t cols = input[0].size();
    size_t mid = cols / 2;

    std::vector<std::vector<uint64_t>> dp(rows, std::vector<uint64_t>(cols, -1));
    return count(input, dp, 0, mid);
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    auto input = reader(path);
    auto input2 = input;

    std::cout << solution(input) << std::endl;
    std::cout << solution_2(input2) << std::endl;

    return 0;
}
