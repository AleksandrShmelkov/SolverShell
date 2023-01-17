#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Manager_Test, test1) {
    SOSH_Manager Manager;
    Manager.DeclareShell("Shell");
    EXPECT_EQ(Manager.FindShell("Shell").get(), "Shell");
    //ASSERT_THAT(Manager.ListShell(), ElementsAre("Shell"));
}

TEST(SOSH_Manager_Test, test2) {
    SOSH_Manager Manager;
    Manager.DeclareShell("Shell");
    EXPECT_TRUE(Manager.FindShell("Shell").get() != "");
}

TEST(SOSH_Manager_Test, test3) {
    SOSH_Manager Manager;
    EXPECT_TRUE(Manager.DeclareShell("Shell"));
    SOSH_Shell Shell = Manager.FindShell("Shell");
    EXPECT_TRUE(Shell.DeclareFunction("summ"));
    EXPECT_EQ(Shell.FindFunction("summ").get(), "summ");
}

