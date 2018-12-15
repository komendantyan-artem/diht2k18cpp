#include "processor.cpp"

int main(int argc, char** argv) {
    assert(argc == 2);
    char* inputFilename = argv[1];
    execute(inputFilename);
}
