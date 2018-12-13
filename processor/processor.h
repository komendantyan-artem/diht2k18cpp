#pragma once

#include <map>
#include <string>
#include <functional>
#include "processor_state.h"
#include "commands_implementation.h"

using CommandExecutor = std::function<void(int, ProcessorState*)>;

const std::map<int, CommandExecutor> commandExecutors{
    {PUSH, executePush},
    {PUSHRAX, executePushRax},
    {PUSHRBX, executePushRbx},
    {PUSHRCX, executePushRcx},
    {PUSHRAM, executePushRam},
    {POP, executePop},
    {POPRAX, executePopRax},
    {POPRBX, executePopRbx},
    {POPRCX, executePopRcx},
    {POPRAM, executePopRam},
    {ADD, executeAdd},
    {SUB, executeSub},
    {MUL, executeMul},
    {DIV, executeDiv},
    {SQRT, executeSqrt},
    {IN, executeIn},
    {OUT, executeOut},
    {LABEL, executeLabel},
    {JUMP, executeJump},
    {JE, executeJE},
    {JL, executeJL}
};

void execute(const std::string& inputFilename);
