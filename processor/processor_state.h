#pragma once

#include <vector>
#include <stack>

struct ProcessorState {
    static const unsigned ramSize = 1000;

    ProcessorState(unsigned codeSize): codeSize(codeSize), ram(ramSize) {}

    const unsigned codeSize;
    std::stack<int> stack;
    std::vector<int> ram;
    int rax{0};
    int rbx{0};
    int rcx{0};
    unsigned ip{0};
};
