#pragma once

#include <memory>

enum class NodeType {
    ADD, SUB, MUL, DIV, POW,
    UNARY_MINUS,
    SIN, COS, LOG,
    NUMBER, ID
};

struct Node {
    NodeType nodeType;
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    
    Node(NodeType nodeType, int value=0):
        nodeType(nodeType), value(value), left(nullptr), right(nullptr) {}
};

std::shared_ptr<Node> makeAdd(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto result = std::make_shared<Node>(NodeType::ADD);
    result->left = left;
    result->right = right;
    return result;
}

std::shared_ptr<Node> makeSub(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto result = std::make_shared<Node>(NodeType::SUB);
    result->left = left;
    result->right = right;
    return result;
}

std::shared_ptr<Node> makeMul(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto result = std::make_shared<Node>(NodeType::MUL);
    result->left = left;
    result->right = right;
    return result;
}

std::shared_ptr<Node> makeDiv(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto result = std::make_shared<Node>(NodeType::DIV);
    result->left = left;
    result->right = right;
    return result;
}

std::shared_ptr<Node> makePow(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto result = std::make_shared<Node>(NodeType::POW);
    result->left = left;
    result->right = right;
    return result;
}

std::shared_ptr<Node> makeUnary(std::shared_ptr<Node> node) {
    auto result = std::make_shared<Node>(NodeType::UNARY_MINUS);
    result->left = node;
    return result;
}

std::shared_ptr<Node> makeSin(std::shared_ptr<Node> node) {
    auto result = std::make_shared<Node>(NodeType::SIN);
    result->left = node;
    return result;
}

std::shared_ptr<Node> makeCos(std::shared_ptr<Node> node) {
    auto result = std::make_shared<Node>(NodeType::COS);
    result->left = node;
    return result;
}

std::shared_ptr<Node> makeLog(std::shared_ptr<Node> node) {
    auto result = std::make_shared<Node>(NodeType::LOG);
    result->left = node;
    return result;
}

std::shared_ptr<Node> makeNumber(int value) {
    auto result = std::make_shared<Node>(NodeType::NUMBER);
    result->value = value;
    return result;
}

std::shared_ptr<Node> makeId(int value) {
    auto result = std::make_shared<Node>(NodeType::ID);
    result->value = value;
    return result;
}
