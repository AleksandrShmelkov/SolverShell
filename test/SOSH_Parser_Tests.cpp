#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Parser, Tokenize) {
    SOSH_Parser pars;
    std::vector<SOSH_Token> out;
    out = pars.Tokenize("sum qwer 4.667 8");

    /*EXPECT_EQ(out[0].TestToken(), "SOSH_FUNCTION_NAME");
    EXPECT_EQ(out[1].TestToken(), "SOSH_STRING");
    EXPECT_EQ(out[2].TestToken(), "SOSH_DOUBLE");
    EXPECT_EQ(out[3].TestToken(), "SOSH_INT");

    EXPECT_EQ(out[0].TestValue(), "sum");
    EXPECT_EQ(out[1].TestValue(), "qwer");
    EXPECT_EQ(out[2].TestValue(), "4.667");
    EXPECT_EQ(out[3].TestValue(), "8");*/
}