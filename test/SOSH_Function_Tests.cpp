#include "gtest/gtest.h"
#include "API/sshell_api.h"

double sum(double x, double y){
    return x + y;
}

TEST(SOSH_Function, AddFunction) {
    SOSH_Manager manager;
    manager.CreateShell("shell1");
    SOSH_Shell shell1 = manager.FindShell("shell1");
    SOSH_Function func("summ", sum);
    EXPECT_TRUE(shell1.AddFunction(func));
}

TEST(SOSH_Function, Run) {
    SOSH_Function func("summ", sum);
    EXPECT_TRUE(func.Run(7, 3) == 10);
}

TEST(SOSH_Function, Name) {
    SOSH_Function Func1;
    //SOSH_Function Func2("summ");
    //EXPECT_TRUE(Func1.get() == "");
    //EXPECT_TRUE(Func2.get() == "summ");
}
