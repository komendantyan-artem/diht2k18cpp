#pragma once

//------------------------------------------------------------------------------
// Formal grammar of language
//
// program    ::= expression '\0'
// expression ::= product{[+-]product}*
// product    ::= power{[*/]power}*
// power      ::= primary | primary^power
// primary    ::= (expression) | -primary | number | id | sin(E) | cos(E) | ln(E)
// number     ::= [0-9]+
// id         ::= [a-z]
//
// Spaces are forbidden
// a+b+c == (a+b)+c
// a*b*c == (a*b)*c
// a^b^c == a^(b^c) 
//------------------------------------------------------------------------------

#include <string>
#include <exception>
#include "tree.h"

class ParserException: public std::exception {
};

class Parser {
public:
    
    Parser(const std::string& text):
        text(text), pointer(0) {}
        
    std::shared_ptr<Node> parse();
    
private:

    void throwIf(bool condition) {
        if (condition) {
            throw ParserException();
        }
    }

    std::shared_ptr<Node> parseExpression();
    std::shared_ptr<Node> parseProduct();
    std::shared_ptr<Node> parsePower();
    std::shared_ptr<Node> parsePrimary();
    std::shared_ptr<Node> parseNumber();

    const std::string& text;
    size_t pointer;
};

