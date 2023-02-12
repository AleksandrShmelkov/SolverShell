#include "gtest/gtest.h"
#include "API/sshell_api.h"

const double precision = 1e-7;
//using SOSH_INTTT = Token_t::SOSH_INT;

TEST(SOSH_Token, SOSH_FUNCTION_NAME) {
    SOSH_Token token(Token_t::SOSH_FUNCTION_NAME, "sum");
    EXPECT_EQ("sum", token.Value()); 
    EXPECT_EQ(Token_t::SOSH_FUNCTION_NAME, token.Type());
}

TEST(SOSH_Token, SOSH_INT) {
    SOSH_Token token(Token_t::SOSH_INT, "1");
    EXPECT_EQ("1", token.StringValue()); 
    EXPECT_EQ(Token_t::SOSH_INT, token.Type());
    //EXPECT_NEAR( 1., token.Value(), precision);
}

TEST(SOSH_Token, SOSH_INT_T) {
    SOSH_Token token(Token_t::SOSH_INT, "1");
    EXPECT_EQ(1, token.Value<int>()); // MAX_INT при ошибке или 0
    EXPECT_EQ(Token_t::SOSH_INT, token.Type());
    //EXPECT_NEAR( 1., token.Value(), precision);
}

TEST(SOSH_Token, SOSH_DOUBLE) {
    SOSH_Token token(Token_t::SOSH_DOUBLE, "1.1");
    EXPECT_EQ("1.1", token.Value()); 
    EXPECT_EQ(Token_t::SOSH_DOUBLE, token.Type());
}

TEST(SOSH_Token, SOSH_STRING) {
    SOSH_Token token(Token_t::SOSH_STRING, "qwerty");
    EXPECT_EQ("qwerty", token.Value()); 
    EXPECT_EQ(Token_t::SOSH_STRING, token.Type());
}

TEST(SOSH_Token, SOSH_UNDEFINED) {
    SOSH_Token token(Token_t::SOSH_UNDEFINED, "`");
    EXPECT_EQ("`", token.Value()); 
    EXPECT_EQ(Token_t::SOSH_UNDEFINED, token.Type());
}
