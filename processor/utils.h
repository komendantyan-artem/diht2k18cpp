#pragma once

#include <vector>
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>

void writeIntInplace(std::vector<char>& bytes, unsigned pointer, int value) {
    for (unsigned i = 0; i < sizeof(int); ++i) {
        bytes[pointer + i] = (reinterpret_cast<char*>(&value))[i];
    }
}

void writeInt(std::vector<char>& bytes, int value) {
    unsigned pointer = bytes.size();
    bytes.resize(pointer + sizeof(int));
    writeIntInplace(bytes, pointer, value);
}

int readInt(std::vector<char>& bytes, unsigned pointer) {
    assert(pointer + sizeof(int) <= bytes.size());
    int value = 0;
    for (unsigned i = 0; i < sizeof(int); ++i) {
        (reinterpret_cast<char*>(&value))[i] = bytes[pointer + i];
    }
    return value;
}

template<class T>
void readFile(const std::string& filename, T& buffer) {
    assert(buffer.empty());
    std::ifstream fin(filename);
    assert(fin.is_open());
    
    fin.seekg(0, std::ios::end);
    buffer.reserve(fin.tellg());
    fin.seekg(0, std::ios::beg);
    buffer.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
}

template<class T>
void writeFile(const std::string& filename, const T& buffer) {
    std::ofstream fout(filename);
    assert(fout.is_open());
    fout.write(buffer.data(), buffer.size());
}
