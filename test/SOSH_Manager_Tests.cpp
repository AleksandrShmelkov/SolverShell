#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Manager, CreateShell) {
    SOSH_Manager Manager;
    Manager.CreateShell("Shell");
    EXPECT_EQ(Manager.FindShell("Shell").Get(), "Shell");
    //ASSERT_THAT(Manager.ListShell(), ElementsAre("Shell"));
}

TEST(SOSH_Manager, FindShell) {
    SOSH_Manager Manager;
    EXPECT_TRUE(Manager.CreateShell("Shell"));
    SOSH_Shell Shell = Manager.FindShell("Shell");
    //EXPECT_TRUE(Shell.AddFunction("sum"));
    //EXPECT_EQ(Shell.FindFunction("sum").get(), "sum"); // ?
}

