#include "gtest/gtest.h"
#include "API/sshell_api.h"

TEST(SOSH_Shell_Test, test1) {
    SOSH_Shell Shell;
    Shell.DeclareFunction("summ");
    ASSERT_TRUE(Shell.FindFunction("summ").get() != "");
    EXPECT_EQ(Shell.ListFunction().at(0).get(), "summ");
}

TEST(SOSH_Shell_Test, test2) {
    SOSH_Manager Manager;
    EXPECT_TRUE(Manager.DeclareShell("Shell"));
    SOSH_Shell Shell = Manager.FindShell("Shell");
    EXPECT_TRUE(Shell.DeclareFunction("summ"));
    EXPECT_EQ(Shell.FindFunction("summ").get(), "summ");
}

