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
#include <chrono>

using std::vector;
using std::string_view;

class AbsurdGenerator {
public:

    AbsurdGenerator(const std::string& filename);
    vector<string_view> generate_strophe();

private:

    void read(const std::string& filename);
    void add_strophe(const vector<string_view>& lines);
    int randrange(int left, int right);
    string_view get_random_line(const vector<string_view>& lines);
    string_view get_matched_line(const vector<string_view>& lines, const string_view& previous);
    static bool reversed_last_word_comparator(const string_view& first, const string_view& second);
    
private:

    std::mt19937 random_generator;
    vector<vector<string_view>> lines_by_strophe;
    std::string buffer;
    
    static const unsigned STROPHE_SIZE;
    static const unsigned STROPHE_DEPENDENCY[];
};
