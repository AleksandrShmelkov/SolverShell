#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Token, EditValue) {
    SOSH_Token token;
    token.EditValue("sum");
    EXPECT_EQ(token.TestValue(), "sum");
}

TEST(SOSH_Token, EditToken) {
    SOSH_Token token;
    token.EditToken(Token_e::SOSH_FUNCTION_NAME);
    EXPECT_EQ(token.TestToken(), "SOSH_FUNCTION_NAME");
}
