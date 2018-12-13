#pragma once

#include "commands.h"
#include "processor_state.h"
#include <cassert>
#include <cmath>
#include <iostream>

static void popTwice(ProcessorState* state, int* first, int* second) {
    assert(state->stack.size() >= 2);
    assert(first != second);
    *second = state->stack.top();
    state->stack.pop();
    *first = state->stack.top();
    state->stack.pop();
}

void executePush(int arg, ProcessorState* state) {
    state->stack.push(arg);
    state->ip += 2 * sizeof(int);
}

void executePushRax(int arg, ProcessorState* state) {
    state->stack.push(state->rax);
    state->ip += 2 * sizeof(int);
}

void executePushRbx(int arg, ProcessorState* state) {
    state->stack.push(state->rbx);
    state->ip += 2 * sizeof(int);
}

void executePushRcx(int arg, ProcessorState* state) {
    state->stack.push(state->rcx);
    state->ip += 2 * sizeof(int);
}

void executePushRam(int arg, ProcessorState* state) {
    assert(0 <= arg && arg < static_cast<int>(state->ram.size()));
    state->stack.push(state->ram[arg]);
    state->ip += 2 * sizeof(int);
}

void executePop(int arg, ProcessorState* state) {
    assert(!state->stack.empty());
    state->stack.pop();
    state->ip += 2 * sizeof(int);
}

void executePopRax(int arg, ProcessorState* state) {
    assert(!state->stack.empty());
    state->rax = state->stack.top();
    state->stack.pop();
    state->ip += 2 * sizeof(int);
}

void executePopRbx(int arg, ProcessorState* state) {
    assert(!state->stack.empty());
    state->rbx = state->stack.top();
    state->stack.pop();
    state->ip += 2 * sizeof(int);
}

void executePopRcx(int arg, ProcessorState* state) {
    assert(!state->stack.empty());
    state->rcx = state->stack.top();
    state->stack.pop();
    state->ip += 2 * sizeof(int);
}

void executePopRam(int arg, ProcessorState* state) {
    assert(0 <= arg && arg < static_cast<int>(state->ram.size()));
    assert(!state->stack.empty());
    state->ram[arg] = state->stack.top();
    state->stack.pop();
    state->ip += 2 * sizeof(int);
}

void executeAdd(int arg, ProcessorState* state) {
    int first = 0, second = 0;
    popTwice(state, &first, &second);
    state->stack.push(first + second);
    state->ip += 2 * sizeof(int);
}

void executeSub(int arg, ProcessorState* state) {
    int first = 0, second = 0;
    popTwice(state, &first, &second);
    state->stack.push(first - second);
    state->ip += 2 * sizeof(int);
}

void executeMul(int arg, ProcessorState* state) {
    int first = 0, second = 0;
    popTwice(state, &first, &second);
    state->stack.push(first * second);
    state->ip += 2 * sizeof(int);
}

void executeDiv(int arg, ProcessorState* state) {
    int first = 0, second = 0;
    popTwice(state, &first, &second);
    assert(second != 0);
    state->stack.push(first / second);
    state->ip += 2 * sizeof(int);
}

void executeSqrt(int arg, ProcessorState* state) {
    assert(!state->stack.empty());
    int value = state->stack.top();
    state->stack.pop();
    assert(value >= 0);
    state->stack.push(static_cast<int>(sqrt(value)));
    state->ip += 2 * sizeof(int);
}

void executeIn(int arg, ProcessorState* state) {
    int value = 0;
    assert(std::cin >> value);
    state->stack.push(value);
    state->ip += 2 * sizeof(int);
}

void executeOut(int arg, ProcessorState* state) {
    assert(!state->stack.empty());
    std::cout << state->stack.top() << std::endl;
    state->ip += 2 * sizeof(int);
}

void executeLabel(int arg, ProcessorState* state) {
    state->ip += 2 * sizeof(int);
}

void executeJump(int arg, ProcessorState* state) {
    assert(0 <= arg && arg < static_cast<int>(state->codeSize));
    assert(arg % (2 * sizeof(int)) == 0);
    state->ip = arg;
}

void executeJE(int arg, ProcessorState* state) {
    assert(0 <= arg && arg < static_cast<int>(state->codeSize));
    assert(arg % (2 * sizeof(int)) == 0);
    int first = 0, second = 0;
    popTwice(state, &first, &second);
    if (first == second) {
        state->ip = arg;
    } else {
        state->ip += 2 * sizeof(int);
    }
}

void executeJL(int arg, ProcessorState* state) {
    assert(0 <= arg && arg < static_cast<int>(state->codeSize));
    assert(arg % (2 * sizeof(int)) == 0);
    int first = 0, second = 0;
    popTwice(state, &first, &second);
    if (first < second) {
        state->ip = arg;
    } else {
        state->ip += 2 * sizeof(int);
    }
}
