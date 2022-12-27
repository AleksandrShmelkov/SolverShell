#include "gtest/gtest.h"
#include "sshell_api.h"

TEST(SOSH_Test, test1) {
    SOSH_Manager Manager;
    Manager.DeclareShell("Shell1");
    //ASSERT_THAT(Manager.ListShell(), ElementsAre("Shell1"));
    EXPECT_EQ(Manager.FindShell("Shell1").get(), "Shell1");
}
