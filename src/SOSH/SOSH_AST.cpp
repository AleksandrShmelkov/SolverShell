#include "SOSH_AST.h"

SOSH_Token NumberNode::evaluate() const { return SOSH_Token(Token_t::SOSH_DOUBLE, std::to_string(value)); }

SOSH_Token BinaryOperatorNode::evaluate() const {
    double leftValue = left->evaluate().GetValue<double>();
    double rightValue = right->evaluate().GetValue<double>();
    double result;

    switch (op) {
        case '+':
            result = leftValue + rightValue;
            break;
        case '-':
            result = leftValue - rightValue;
            break;
        case '*':
            result = leftValue * rightValue;
            break;
        case '/':
            if (rightValue == 0)
                throw std::runtime_error("Division by zero");
            result = leftValue / rightValue;
            break;
        default:
            throw std::runtime_error("Invalid operator");
    };
    return SOSH_Token(Token_t::SOSH_DOUBLE, std::to_string(result));
};

SOSH_Token ASTShellFunctionNode::evaluate() const {
    if (function == nullptr) {
        std::cout << function_name << ": function not found." << std::endl;
        return SOSH_Token(Token_t::SOSH_UNDEFINED, "");
    } else {
        return function->call<20>(arguments); // Вызов функции
    };
};
