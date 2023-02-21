#include "gtest/gtest.h"
#include "API/sshell_api.h"

double shell_sum(double x, double y){
    return x + y;
}

TEST(SOSH_Shell, AddFunction) {
    SOSH_Shell shell("shell");
    SOSH_Function sum("sum", shell_sum);
    EXPECT_TRUE(shell.AddFunction(sum));
}

TEST(SOSH_Shell, FindFunction) {
    SOSH_Shell shell("shell");
    SOSH_Function sum("sum", shell_sum);
    shell.AddFunction(sum);
    EXPECT_EQ(shell.FindFunction("sum").GetName(), "sum");
}

TEST(SOSH_Shell, ListFunction) {
    SOSH_Shell shell("shell");
    SOSH_Function sum("sum", shell_sum);
    shell.AddFunction(sum);
    EXPECT_EQ(shell.ListFunction().at(0).GetName(), "sum");
}

TEST(SOSH_Shell, GetName) {
    SOSH_Shell shell("shell");
    EXPECT_EQ(shell.GetName(), "shell");
}
