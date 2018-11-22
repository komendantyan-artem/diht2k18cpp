#pragma once

#include "tree.h"   

// don't validate tree

std::shared_ptr<Node> differentiate(std::shared_ptr<Node> node, int variable) {
    if (!node) {
        return nullptr;
    }
    switch (node->nodeType) {
        case NodeType::ADD:
            return makeAdd(
                differentiate(node->left, variable),
                differentiate(node->right, variable)
            );
        case NodeType::SUB:
            return makeSub(
                differentiate(node->left, variable),
                differentiate(node->right, variable)
            );
        case NodeType::MUL:
            return makeAdd(
                makeMul(differentiate(node->left, variable), node->right),
                makeMul(node->left, differentiate(node->right, variable))
            );
        case NodeType::DIV:
            return makeDiv(
                makeSub(
                    makeMul(differentiate(node->left, variable), node->right),
                    makeMul(node->left, differentiate(node->right, variable))
                ),
                makePow(node->right, makeNumber(2))
            );
        case NodeType::POW:
            return makeMul(
                differentiate(
                    makeMul(
                        node->right,
                        makeLog(node->left)
                    ),
                    variable
                ),
                node
            );
        case NodeType::UNARY_MINUS:
            return makeUnary(differentiate(node->left, variable));
        case NodeType::SIN:
            return makeMul(
                differentiate(node->left, variable),
                makeCos(node->left)
            );
        case NodeType::COS:
            return makeMul(
                differentiate(node->left, variable),
                makeUnary(makeSin(node->left))
            );
        case NodeType::LOG:
            return makeDiv(
                differentiate(node->left, variable),
                node->left
            );
        case NodeType::NUMBER:
            return makeNumber(0);
        case NodeType::ID:
            return makeNumber(node->value == variable ? 1: 0);
    }
    return node;
}
