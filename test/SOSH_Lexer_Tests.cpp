#include <gtest/gtest.h>
#include "SOSH/SOSH_Lexer.h"

TEST(LexerTest, TokenizeWhitespace) {
    std::string code = "   \t\n";
    Lexer lexer(code);
    std::vector<SOSH_Token> tokens = lexer.tokenize();
    EXPECT_EQ(tokens.size(), 0);
}

TEST(LexerTest, TokenizeIdentifier) {
    std::string code = "variable_name";
    Lexer lexer(code);
    std::vector<SOSH_Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].getType(), Token_t::SOSH_IDENTIFIER);
    EXPECT_EQ(tokens[0].getLexeme(), code);
}

TEST(LexerTest, TokenizeNumber) {
    std::string code = "123.45";
    Lexer lexer(code);
    std::vector<SOSH_Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].getType(), Token_t::SOSH_FLOAT);
    EXPECT_EQ(tokens[0].getLexeme(), code);
}

TEST(LexerTest, TokenizeString) {
    std::string code = "\"Hello, world!\"";
    Lexer lexer(code);
    std::vector<SOSH_Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].getType(), Token_t::SOSH_STRING);
    EXPECT_EQ(tokens[0].getLexeme(), code);
}

TEST(LexerTest, TokenizeCharacter) {
    std::string code = "'A'";
    Lexer lexer(code);
    std::vector<SOSH_Token> tokens = lexer.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].getType(), Token_t::SOSH_CHAR);
    EXPECT_EQ(tokens[0].getLexeme(), code);
}
