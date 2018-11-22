#pragma once

#include "tree.h"

static bool isZero(std::shared_ptr<Node> node) {
    return node != nullptr && node->nodeType == NodeType::NUMBER && node->value == 0;
}

static bool isOne(std::shared_ptr<Node> node) {
    return node != nullptr && node->nodeType == NodeType::NUMBER && node->value == 1;
}

// don't validate tree

std::shared_ptr<Node> simplify(std::shared_ptr<Node> node) {
    if (!node) {
        return nullptr;
    }
    auto temp = std::make_shared<Node>(node->nodeType, node->value);
    temp->left = simplify(node->left);
    temp->right = simplify(node->right);
    node = temp;
    switch (node->nodeType) {
        case NodeType::ADD:
            if (isZero(node->left)) {
                return node->right;
            }
            if (isZero(node->right)) {
                return node->left;
            }
            break;
        case NodeType::SUB:
            if (isZero(node->left)) {
                auto temp = std::make_shared<Node>(NodeType::UNARY_MINUS);
                temp->left = node->right;
                if (temp->left->nodeType == NodeType::NUMBER) {
                    return simplify(temp);
                }
                return temp;
            }
            if (isZero(node->right)) {
                return node->left;
            }
            break;
        case NodeType::MUL:
            if (isZero(node->left) || isZero(node->right)) {
                return makeNumber(0);
            }
            if (isOne(node->left)) {
                return node->right;
            }
            if (isOne(node->right)) {
                return node->left;
            }
            break;
        case NodeType::DIV:
            if (isZero(node->left)) {
                return makeNumber(0);
            }
            if (isOne(node->right)) {
                return node->left;
            }
            break;
        case NodeType::POW:
            if (isZero(node->right)) {
                return makeNumber(1);
            }
            if (isOne(node->right)) {
                return node->left;
            }
            if (isOne(node->left)) {
                return makeNumber(1);
            }
            if (isZero(node->left)) {
                return makeNumber(0);
            }
            break;
        case NodeType::UNARY_MINUS:
            if (node->left->nodeType == NodeType::NUMBER) {
                return std::make_shared<Node>(NodeType::NUMBER, -node->left->value);
            }
            break;
        case NodeType::SIN:
        case NodeType::COS:
        case NodeType::LOG:
        case NodeType::NUMBER:
        case NodeType::ID:
            break;
    }
    return node;
}
