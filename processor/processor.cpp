#pragma once

#include "processor.h"
#include "utils.h"

void execute(const std::string& inputFilename) {
    std::vector<char> program;
    readFile(inputFilename, program);
    assert(program.size() % (2 * sizeof(int)) == 0);
    
    ProcessorState state(program.size());
    while (state.ip < state.codeSize) {
        int code = readInt(program, state.ip);
        int arg = readInt(program, state.ip + sizeof(int));
        assert(commandExecutors.count(code));
        commandExecutors.at(code)(arg, &state);
    }
}
