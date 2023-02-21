#include "gtest/gtest.h"
#include "API/sshell_api.h"

double function_sum(double x, double y){
    return x + y;
}

TEST(SOSH_Function, EditFunction) {
    SOSH_Function func("sum", function_sum);
    EXPECT_TRUE(func.EditFunction("sum", function_sum));
}

TEST(SOSH_Function, Run) {
    SOSH_Function func("sum", function_sum);
    EXPECT_TRUE(func.Run(7, 3) == 10);
}

TEST(SOSH_Function, GetName) {
    SOSH_Function func("sum", function_sum);
    EXPECT_TRUE(func.GetName() == "sum");
}
