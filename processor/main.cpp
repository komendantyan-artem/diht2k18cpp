#include "compiler.cpp"
#include "processor.cpp"
#include <iostream>

int main() {
    compile("input.txt", "output");
    decompile("output", "output.txt");
    execute("output");
}
