#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Manager, AddShell) {
    SOSH_Manager manager;
    SOSH_Shell shell("shell");
    EXPECT_TRUE(manager.AddShell(shell));
}

TEST(SOSH_Manager, FindShell) {
    SOSH_Manager manager;
    SOSH_Shell shell("shell");
    manager.AddShell(shell);
    EXPECT_EQ(manager.FindShell("shell").GetName(), "shell");
    //ASSERT_THAT(manager.ListShell(), ElementsAre("Shell"));
}

TEST(SOSH_Manager, ListShell) {
    SOSH_Manager manager;
    SOSH_Shell shell("shell");
    manager.AddShell(shell);
    EXPECT_EQ(manager.ListShell().at(0).GetName(), "shell");
}

