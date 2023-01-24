#include "gtest/gtest.h"
#include "API/sshell_api.h"

double sum(double x, double y){
    return x + y;
}

TEST(SampleFunction, AddFunction) {
    SOSH_Manager manager;
    manager.CreateShell("shell1");
    SOSH_Shell shell1 = manager.FindShell("shell1");
    SOSH_Function func("summ", sum);
    EXPECT_TRUE(shell1.AddFunction(func));
}

TEST(SampleFunction, Run) {
    SOSH_Function func("summ", sum);
    EXPECT_TRUE(func.Run(7, 3) == 10);
}
