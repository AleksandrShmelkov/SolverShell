#include "gtest/gtest.h"
#include "SOSH/SOSH_AST.h"

TEST(NumberNodeTest, Evaluate) {
    NumberNode node(5.0);
    SOSH_Token result = node.evaluate();
    ASSERT_EQ(result.type, SOSH_TokenType::NUMBER);
    ASSERT_DOUBLE_EQ(result.numberValue, 5.0);
}

TEST(BinaryOperatorNodeTest, Evaluate) {
    NumberNode leftNode(3.0);
    NumberNode rightNode(2.0);
    BinaryOperatorNode node('+', &leftNode, &rightNode);
    SOSH_Token result = node.evaluate();
    ASSERT_EQ(result.type, SOSH_TokenType::NUMBER);
    ASSERT_DOUBLE_EQ(result.numberValue, 5.0);
}
