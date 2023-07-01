//#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "SOSH/SOSH_Token.h"

TEST(SOSH_TokenTest, GetValue_IntType) {
    SOSH_Token token(Token_t::SOSH_INT, "42");
    int value = token.GetValue<int>();
    EXPECT_EQ(42, value);
}

TEST(SOSH_TokenTest, GetValue_StringType) {
    SOSH_Token token(Token_t::SOSH_STRING, "Hello");
    std::string value = token.GetValue<std::string>();
    EXPECT_EQ("Hello", value);
}

TEST(SOSH_TokenTest, GetValue_DefaultType) {
    SOSH_Token token(Token_t::SOSH_FLOAT, "3.14");
    float value = token.GetValue<float>();
    EXPECT_FLOAT_EQ(3.14f, value);
}

TEST(SOSH_TokenTest, EditValue) {
    SOSH_Token token(Token_t::SOSH_IDENTIFIER, "var");
    token.EditValue("variable");
    std::string lexeme = token.GetValue<std::string>();
    EXPECT_EQ("variable", lexeme);
}

TEST(SOSH_TokenTest, GetType) {
    SOSH_Token token(Token_t::SOSH_KEYWORD);
    Token_t type = token.GetType();
    EXPECT_EQ(Token_t::SOSH_KEYWORD, type);
}

TEST(SOSH_TokenTest, GetValue_CharType) {
    SOSH_Token token(Token_t::SOSH_CHAR, "A");
    char value = token.GetValue<char>();
    EXPECT_EQ('A', value);
}
