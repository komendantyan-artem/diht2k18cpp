#pragma once

#include "tree.h"
#include <string>
#include <cassert>

static int getPriority(NodeType nodeType) {
    switch (nodeType) {
        case NodeType::UNARY_MINUS: return 5;
        case NodeType::POW: return 4;
        case NodeType::MUL: return 3;
        case NodeType::ADD: return 2;
        case NodeType::SUB: return 2;
        default: return 1;
    }
}

// don't validate tree

std::string treeToString(std::shared_ptr<Node> node, int parentPriority=0) {
    if (!node) {
        return "";
    }
    auto left = treeToString(node->left, getPriority(node->nodeType));
    auto right = treeToString(node->right, getPriority(node->nodeType));
    std::string result;
    std::string binaryOp;
    switch (node->nodeType) {
        case NodeType::ADD:
            result = left + "+" + right;
            if (getPriority(node->nodeType) < parentPriority) {
                result = "\\left(" + result + "\\right)";
            }
            break;
        case NodeType::SUB:
            result = left + "-" + right;
            if (getPriority(node->nodeType) < parentPriority) {
                result = "\\left(" + result + "\\right)";
            }
            break;
        case NodeType::MUL:
            result = left + "\\cdot " + right;
            if (getPriority(node->nodeType) < parentPriority) {
                result = "\\left(" + result + "\\right)";
            }
            break;
        case NodeType::POW:
            result = left + "^" + right;
            if (getPriority(node->nodeType) < parentPriority) {
                result = "\\left(" + result + "\\right)";
            }
            break;
        case NodeType::DIV:
            result = "\\frac{" + left + "}{" + right + "}";
            break;
        case NodeType::UNARY_MINUS:
            result = "-" + left;
            break;
        case NodeType::SIN:
            result = "\\sin \\left(" + left + "\\right)";
            break;
        case NodeType::COS:
            result = "\\cos \\left(" + left + "\\right)";
            break;
        case NodeType::LOG:
            result = "\\ln \\left(" + left + "\\right)";
            break;
        case NodeType::NUMBER:
            result = std::to_string(node->value);
            break;
        case NodeType::ID:
            result.push_back(node->value);
            break;
        default:
            assert(0);
    }
    return result;
}
