#pragma once

enum Command {
    PUSH,
    PUSHRAX,
    PUSHRBX,
    PUSHRCX,
    PUSHRAM,
    
    POP,
    POPRAX,
    POPRBX,
    POPRCX,
    POPRAM,
    
    ADD,
    SUB,
    MUL,
    DIV,
    SQRT,
    
    IN,
    OUT,
    
    LABEL,
    
    JUMP,
    JE,
    JL
};
