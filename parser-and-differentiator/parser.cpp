#pragma once

#include "parser.h"

std::shared_ptr<Node> Parser::parse() {
    std::shared_ptr<Node> result = parseExpression();
    throwIf(text[pointer] != '\0');
    return result;
}

std::shared_ptr<Node> Parser::parseExpression() {
    auto result = parseProduct();
    while (text[pointer] == '+' || text[pointer] == '-') {
        NodeType nodeType = (text[pointer] == '+') ? NodeType::ADD : NodeType::SUB;
        ++pointer;
        auto right = parseProduct();
        auto new_result = std::make_shared<Node>(nodeType);
        new_result->left = result;
        new_result->right = right;
        result = new_result;
    }
    return result;
}

std::shared_ptr<Node> Parser::parseProduct() {
    auto result = parsePower();
    while (text[pointer] == '*' || text[pointer] == '/') {
        NodeType nodeType = (text[pointer] == '*') ? NodeType::MUL : NodeType::DIV;
        ++pointer;
        auto new_result = std::make_shared<Node>(nodeType);
        new_result->left = result;
        new_result->right = parsePower();;
        result = new_result;
    }
    return result;
}

std::shared_ptr<Node> Parser::parsePower() {
    auto result = parsePrimary();
    if (text[pointer] == '^') {
        ++pointer;
        auto new_result = std::make_shared<Node>(NodeType::POW);
        new_result->left = result;
        new_result->right = parsePower();
        result = new_result;
    }
    return result;
}

std::shared_ptr<Node> Parser::parsePrimary() {
    if (text[pointer] == '(') {
        ++pointer;
        auto result = parseExpression();
        throwIf(text[pointer] != ')');
        ++pointer;
        return result;
    }
    if (text[pointer] == '-') {
        ++pointer;
        auto result = std::make_shared<Node>(NodeType::UNARY_MINUS);
        result->left = parsePrimary();
        return result;
    }
    if (isdigit(text[pointer])) {
        return parseNumber();
    }
    std::string id;
    while (isalpha(text[pointer])) {
        id.push_back(text[pointer]);
        ++pointer;
    }
    if (id.size() == 1) {
        return std::make_shared<Node>(NodeType::ID, id[0]);
    }
    throwIf(id.empty());
    throwIf(id != "sin" && id != "cos" && id != "ln");
    throwIf(text[pointer] != '(');
    ++pointer;
    auto nodeExpression = parseExpression();
    throwIf(text[pointer] != ')');
    ++pointer;
    NodeType resultType = (id == "sin") ? NodeType::SIN :
                          (id == "cos") ? NodeType::COS : NodeType::LOG;
    auto result = std::make_shared<Node>(resultType);
    result->left = nodeExpression;
    return result;
}

std::shared_ptr<Node> Parser::parseNumber() {
    throwIf(!isdigit(text[pointer]));
    int value = 0;
    while (isdigit(text[pointer])) {
        value = value * 10 + (text[pointer] - '0');
        ++pointer;
    }
    return std::make_shared<Node>(NodeType::NUMBER, value);
}
