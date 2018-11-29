#include "absurd_generator.cpp"
#include <iostream>
#include <fstream>

int main() {
    AbsurdGenerator gen;
    gen.read_and_init("onegin.txt");
    
    gen.write_all_lines(std::ofstream("same_output.txt"));
    
    gen.sort_all_lines(gen.comparator);
    gen.write_all_lines(std::ofstream("sorted_output.txt"));
    
    gen.sort_all_lines(gen.reversed_comparator);
    gen.write_all_lines(std::ofstream("reversed_output.txt"));
    
    for (const auto& line: gen.generate_strophe()) {
        std::cout << line << std::endl;
    }
}
