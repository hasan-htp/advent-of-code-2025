#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using data = std::vector<std::vector<char>>;

// I swapped i with j, but I'm a lazy fucker, assume j is i and i is j
bool check_eight_adjacent(const data &rows, size_t j, size_t i) {
    //
    int count = 0;
    if (j > 0 && rows[j - 1][i] == '@') {
        count++;
    }
    if (j < rows.size() - 1 && rows[j + 1][i] == '@') {
        count++;
    }
    if (j > 0 && i > 0 && rows[j - 1][i - 1] == '@') {
        count++;
    }
    if (i > 0 && rows[j][i - 1] == '@') {
        count++;
    }
    if (i > 0 && j < rows.size() - 1 && rows[j + 1][i - 1] == '@') {
        count++;
    }
    if (i < rows[0].size() - 1 && j > 0 && rows[j - 1][i + 1] == '@') {
        count++;
    }
    if (i < rows[0].size() - 1 && rows[j][i + 1] == '@') {
        count++;
    }
    if (i < rows[0].size() - 1 && j < rows.size() - 1 && rows[j + 1][i + 1] == '@') {
        count++;
    }

    if (count < 4) {
        return true;
    }
    return false;
}

int solution(const data &rows) {
    int rolls = 0;
    for (size_t i = 0; i < rows.size(); ++i) {
        for (size_t j = 0; j < rows[0].size(); ++j) {
            if (rows[i][j] == '@' && check_eight_adjacent(rows, i, j)) {
                rolls++;
            }
        }
    }
    return rolls;
}

auto reader(const std::string &path) {
    data ret;

    std::ifstream ifs(path);
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            std::vector<char> row;
            for (char c : line) {
                row.push_back(c);
            }
            ret.emplace_back(std::move(row));
        }
    }

    return ret;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "<input_file_path>" << std::endl;
        return 1;
    }

    const std::string path = argv[1];

    const auto input = reader(path);
    std::cout << solution(input) << std::endl;

    return 0;
}