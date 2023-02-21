#include "gtest/gtest.h"
#include "API/sshell_api.h"

const double precision = 1e-7;
//using SOSH_INTTT = Token_t::SOSH_INT;

TEST(SOSH_Token, SOSH_FUNCTION_NAME) {
    SOSH_Token token(Token_t::SOSH_FUNCTION_NAME, "sum");
    EXPECT_EQ("sum", token.Value<std::string>()); 
    EXPECT_EQ(Token_t::SOSH_FUNCTION_NAME, token.Type());
}

TEST(SOSH_Token, SOSH_INT) {
    SOSH_Token token(Token_t::SOSH_INT, "1");
    EXPECT_EQ(1, token.Value<int>());
    EXPECT_EQ(Token_t::SOSH_INT, token.Type());
    EXPECT_NEAR(1., token.Value<int>(), precision);
}

TEST(SOSH_Token, SOSH_DOUBLE) {
    SOSH_Token token(Token_t::SOSH_DOUBLE, "1.1");
    EXPECT_EQ(1.1, token.Value<double>());
    EXPECT_EQ(Token_t::SOSH_DOUBLE, token.Type());
    EXPECT_NEAR(1.1, token.Value<double>(), precision);
}

TEST(SOSH_Token, SOSH_DOUBLE_T) {
    SOSH_Token token(Token_t::SOSH_DOUBLE, "1.1");
    EXPECT_EQ("1.1", token.Value<std::string>());
    EXPECT_EQ(Token_t::SOSH_DOUBLE, token.Type());
    EXPECT_NEAR(1.1, token.Value<double>(), precision);
}

TEST(SOSH_Token, SOSH_STRING) {
    SOSH_Token token(Token_t::SOSH_STRING, "qwerty");
    EXPECT_EQ("qwerty", token.Value<std::string>());
    EXPECT_EQ(Token_t::SOSH_STRING, token.Type());
}

TEST(SOSH_Token, SOSH_STRING_T) {
    SOSH_Token token(Token_t::SOSH_INT, "2");
    EXPECT_EQ("2", token.Value());
    EXPECT_EQ(Token_t::SOSH_INT, token.Type());
}

TEST(SOSH_Token, SOSH_UNDEFINED) {
    SOSH_Token token(Token_t::SOSH_UNDEFINED, "`");
    EXPECT_EQ("`", token.Value<std::string>()); 
    EXPECT_EQ(Token_t::SOSH_UNDEFINED, token.Type());
}
