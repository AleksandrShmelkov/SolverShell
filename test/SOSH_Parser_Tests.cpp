#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Parser, Tokenize) {
    SOSH_Parser pars;
    std::vector<SOSH_Token> out;
    out = pars.Tokenize("sum qwer 4.667 8");

    EXPECT_EQ(out[0].Type(), Token_t::SOSH_FUNCTION_NAME);
    EXPECT_EQ(out[1].Type(), Token_t::SOSH_STRING);
    EXPECT_EQ(out[2].Type(), Token_t::SOSH_DOUBLE);
    EXPECT_EQ(out[3].Type(), Token_t::SOSH_INT);

    EXPECT_EQ(out[0].Value<std::string>(), "sum");
    EXPECT_EQ(out[1].Value<std::string>(), "qwer");
    EXPECT_EQ(out[2].Value<double>(), 4.667);
    EXPECT_EQ(out[3].Value<int>(), 8);
}
