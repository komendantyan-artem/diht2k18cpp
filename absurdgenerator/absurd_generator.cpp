#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <string_view>
#include <map>
#include <algorithm>
#include <random>
#include <cassert>
#include <chrono>
#include "absurd_generator.h"

using std::vector;
using std::string_view;

const unsigned AbsurdGenerator::STROPHE_SIZE = 14;
const unsigned AbsurdGenerator::STROPHE_DEPENDENCY[] = {
     2,  3, 0, 1,  // AbAb
     5,  4, 7, 6,  // CCdd
    11, 10, 9, 8,  // EffE
    13, 12         // gg
};

bool AbsurdGenerator::reversed_last_word_comparator(const string_view& first, const string_view& second) {
    assert(!first.empty() && !second.empty());
    const char* p1 = &first[first.size() - 1];
    const char* p2 = &second[second.size() - 1];
    while (isspace(*p1) || ispunct(*p1)) {
        --p1;
    }
    while (isspace(*p2) || ispunct(*p2)) {
        --p2;
    }
    for (;; --p1, --p2) {
        if (p2 < &second[0] || isspace(*p2)) {
            return false;
        }
        if (p1 < &first[0] || isspace(*p1)) {
            return true;
        }
        if (*p1 != *p2) {
            return *p1 < *p2;
        }
    }
}

AbsurdGenerator::AbsurdGenerator(const std::string& filename):
    random_generator(std::chrono::steady_clock::now().time_since_epoch().count()),
    lines_by_strophe(STROPHE_SIZE)
{
    read(filename);
    for (size_t i = 0; i < lines_by_strophe.size(); ++i) {
        sort(lines_by_strophe[i].begin(), lines_by_strophe[i].end(), reversed_last_word_comparator);
    }
}

void AbsurdGenerator::read(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "There is no input file" << std::endl;
        exit(1);
    }
    fin.seekg(0, std::ios::end);
    buffer.reserve(fin.tellg());
    fin.seekg(0, std::ios::beg);
    buffer.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    
    vector<string_view> lines;
    for (unsigned start = 0, it = 0; it < buffer.size(); ++it) {
        if (buffer[it] == '\n') {
            if (start == it) {
                lines.clear();
            } else {
                lines.emplace_back(&buffer[start], it - start);
                if (lines.size() == STROPHE_SIZE) {
                    add_strophe(lines);
                    lines.clear();
                }
            }
            start = it + 1;
        }
    }
}

void AbsurdGenerator::add_strophe(const vector<string_view>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        lines_by_strophe[i].push_back(lines[i]);
    }
}

vector<string_view> AbsurdGenerator::generate_strophe() {
    vector<string_view> result;
    for (size_t i = 0; i < STROPHE_SIZE; ++i) {
        if (STROPHE_DEPENDENCY[i] >= i) {
            result.push_back(get_random_line(lines_by_strophe[i]));
        } else {
            const string_view& previous = result[STROPHE_DEPENDENCY[i]];
            result.push_back(get_matched_line(lines_by_strophe[i], previous));
        }
    }
    return result;
}

string_view AbsurdGenerator::get_random_line(const vector<string_view>& lines) {
    return lines[randrange(0, static_cast<int>(lines.size()))];
}

string_view AbsurdGenerator::get_matched_line(const vector<string_view>& lines, const string_view& previous) {
    auto it = upper_bound(lines.begin(), lines.end(), previous, reversed_last_word_comparator);
    if (it != lines.end()) {
        return *it;
    }
    it = lower_bound(lines.begin(), lines.end(), previous, reversed_last_word_comparator);
    if (it == lines.begin()) {
        return get_random_line(lines);
    }
    return *prev(it);
}

int AbsurdGenerator::randrange(int left, int right) {
    std::uniform_int_distribution<> distribution(left, right - 1);
    return distribution(random_generator);
}
