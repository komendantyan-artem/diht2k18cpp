#pragma once

#include "compiler.h"
#include "utils.h"
#include <sstream>

void compile(const std::string& inputFilename, const std::string& outputFilename) {
    std::string inputBuffer;
    readFile(inputFilename, inputBuffer);
    std::stringstream stream(inputBuffer);
    
    std::vector<char> outputBuffer;
    std::map<int, int> labels;
    for (std::string name; stream >> name;) {
        assert(nameToCode.count(name));
        int code = nameToCode.at(name);
        int arg = 0;
        if (hasArgument.count(code)) {
            assert(stream >> arg);
        }
        if (code == LABEL) {
            assert(!labels.count(arg));
            labels[arg] = static_cast<int>(outputBuffer.size());
        }
        writeInt(outputBuffer, code);
        writeInt(outputBuffer, arg);
    }
    
    for (unsigned pointer = 0; pointer < outputBuffer.size(); pointer += 2 * sizeof(int)) {
        int code = readInt(outputBuffer, pointer);
        int arg = readInt(outputBuffer, pointer + sizeof(int));
        if (isJump.count(code) || code == LABEL) {
            assert(labels.count(arg));
            writeIntInplace(outputBuffer, pointer + sizeof(int), labels.at(arg));
        }
    }
    
    writeFile(outputFilename, outputBuffer);
}

void decompile(const std::string& inputFilename, const std::string& outputFilename) {
    std::vector<char> inputBuffer;
    readFile(inputFilename, inputBuffer);
    assert(inputBuffer.size() % (2 * sizeof(int)) == 0);
    
    std::stringstream stream;
    for (unsigned pointer = 0; pointer < inputBuffer.size(); pointer += 2 * sizeof(int)) {
        int code = readInt(inputBuffer, pointer);
        int arg = readInt(inputBuffer, pointer + sizeof(int));
        assert(codeToName.count(code));
        stream << codeToName.at(code);
        if (hasArgument.count(code)) {
            stream << ' ' << arg;
        }
        stream << '\n';
    }
    
    writeFile(outputFilename, stream.str());
}
