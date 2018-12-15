#include "compiler.cpp"

int main(int argc, char** argv) {
    assert(argc == 3);
    char* inputFilename = argv[1];
    char* outputFilename = argv[2];
    decompile(inputFilename, outputFilename);
}
