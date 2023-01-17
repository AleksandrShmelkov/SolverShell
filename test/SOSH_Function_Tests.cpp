#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Function_Test, test1) {
    SOSH_Function Func1;
    SOSH_Function Func2("summ");
    EXPECT_TRUE(Func1.get() == "");
    EXPECT_TRUE(Func2.get() == "summ");
}
