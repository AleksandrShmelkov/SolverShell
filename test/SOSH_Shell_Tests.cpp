#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Shell, CreateFunction) {
    SOSH_Shell Shell;
    //Shell.AddFunction("sum");
    //ASSERT_TRUE(Shell.FindFunction("summ").get() != "");
    //EXPECT_EQ(Shell.ListFunction().at(0).get(), "sum");
}

TEST(SOSH_Shell, FindShell) {
    SOSH_Manager Manager;
    EXPECT_TRUE(Manager.CreateShell("Shell"));
    SOSH_Shell Shell = Manager.FindShell("Shell");
    //EXPECT_TRUE(Shell.AddFunction("sum"));
    //EXPECT_EQ(Shell.FindFunction("sum").get(), "sum");
}

