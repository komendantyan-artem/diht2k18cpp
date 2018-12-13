#pragma once

#include <map>
#include <set>
#include <string>
#include "commands.h"

const std::map<int, std::string> codeToName{
    {PUSH, "PUSH"},
    {PUSHRAX, "PUSHRAX"},
    {PUSHRBX, "PUSHRBX"},
    {PUSHRCX, "PUSHRCX"},
    {PUSHRAM, "PUSHRAM"},
    {POP, "POP"},
    {POPRAX, "POPRAX"},
    {POPRBX, "POPRBX"},
    {POPRCX, "POPRCX"},
    {POPRAM, "POPRAM"},
    {ADD, "ADD"},
    {SUB, "SUB"},
    {MUL, "MUL"},
    {DIV, "DIV"},
    {SQRT, "SQRT"},
    {IN, "IN"},
    {OUT, "OUT"},
    {LABEL, "LABEL"},
    {JUMP, "JUMP"},
    {JE, "JE"},
    {JL, "JL"}
};

const std::map<std::string, int> nameToCode{
    {"PUSH", PUSH},
    {"PUSHRAX", PUSHRAX},
    {"PUSHRBX", PUSHRBX},
    {"PUSHRCX", PUSHRCX},
    {"PUSHRAM", PUSHRAM},
    {"POP", POP},
    {"POPRAX", POPRAX},
    {"POPRBX", POPRBX},
    {"POPRCX", POPRCX},
    {"POPRAM", POPRAM},
    {"ADD", ADD},
    {"SUB", SUB},
    {"MUL", MUL},
    {"DIV", DIV},
    {"SQRT", SQRT},
    {"IN", IN},
    {"OUT", OUT},
    {"LABEL", LABEL},
    {"JUMP", JUMP},
    {"JE", JE},
    {"JL", JL}
};

const std::set<int> isJump{
    JUMP, JE, JL
};

const std::set<int> hasArgument{
    PUSH, PUSHRAM,
    POPRAM,
    LABEL,
    JUMP, JE, JL
};

void compile(const std::string& inputFilename, const std::string& outputFilename);

void decompile(const std::string& inputFilename, const std::string& outputFilename);
