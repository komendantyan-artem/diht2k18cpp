#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include <cassert>
#include <chrono>
#include "absurd_generator.h"

using std::vector;
using std::string;

const unsigned AbsurdGenerator::STROPHE_SIZE = 14;
const unsigned AbsurdGenerator::STROPHE_DEPENDENCY[] = {
     2,  3, 0, 1,  // AbAb
     5,  4, 7, 6,  // CCdd
    11, 10, 9, 8,  // EffE
    13, 12         // gg
};

bool AbsurdGenerator::reversed_last_word_comparator(const string& first, const string& second) {
    assert(!first.empty() && !second.empty());
    const char* p1 = &first[first.size() - 1];
    const char* p2 = &second[second.size() - 1];
    while (ispunct(*p1)) {
        --p1;
    }
    while (ispunct(*p2)) {
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

AbsurdGenerator::AbsurdGenerator(const string& filename):
    random_generator(std::chrono::steady_clock::now().time_since_epoch().count()),
    lines_by_strophe(STROPHE_SIZE)
{
    read(filename);
    for (size_t i = 0; i < lines_by_strophe.size(); ++i) {
        sort(lines_by_strophe[i].begin(), lines_by_strophe[i].end(), reversed_last_word_comparator);
    }
}

void AbsurdGenerator::read(const string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "There is no input file" << std::endl;
        exit(1);
    }
    vector<string> lines;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) {
            lines.clear();
        } else {
            lines.push_back(line);
            if (lines.size() == STROPHE_SIZE) {
                add_strophe(lines);
                lines.clear();
            }
        }
    }
}

void AbsurdGenerator::add_strophe(const vector<string>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        lines_by_strophe[i].push_back(lines[i]);
    }
}

vector<string> AbsurdGenerator::generate_strophe() {
    vector<string> result;
    for (size_t i = 0; i < STROPHE_SIZE; ++i) {
        if (STROPHE_DEPENDENCY[i] >= i) {
            result.push_back(get_random_line(lines_by_strophe[i]));
        } else {
            const string& previous = result[STROPHE_DEPENDENCY[i]];
            result.push_back(get_matched_line(lines_by_strophe[i], previous));
        }
    }
    return result;
}

string AbsurdGenerator::get_random_line(const vector<string>& lines) {
    return lines[randrange(0, static_cast<int>(lines.size()))];
}

string AbsurdGenerator::get_matched_line(const vector<string>& lines, const string& previous) {
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
