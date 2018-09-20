#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;
using std::string;

class AbsurdGenerator {
public:

    AbsurdGenerator(const string& filename);
    vector<string> generate_strophe();

private:

    void read(const string& filename);
    void add_strophe(const vector<string>& lines);
    int randrange(int left, int right);
    string get_random_line(const vector<string>& lines);
    string get_matched_line(const vector<string>& lines, const string& previous);
    static bool reversed_last_word_comparator(const string& first, const string& second);
    
private:

    std::mt19937 random_generator;
    vector<vector<string>> lines_by_strophe;
    
    static const unsigned STROPHE_SIZE;
    static const unsigned STROPHE_DEPENDENCY[];
};
