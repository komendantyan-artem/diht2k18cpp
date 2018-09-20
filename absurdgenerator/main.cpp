#include "absurd_generator.cpp"
#include <iostream>

int main() {
    AbsurdGenerator gen("onegin.txt");
    for (const auto& line: gen.generate_strophe()) {
        std::cout << line << std::endl;
    }
}
