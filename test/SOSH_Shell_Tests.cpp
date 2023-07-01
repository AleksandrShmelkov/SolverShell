#include "gtest/gtest.h"
#include "SOSH/SOSH_Shell.h"
#include "SOSH/SOSH_Function.h"

/*// Тестирование функции AddFunction
TEST(SOSH_ShellTest, AddFunction) {
    SOSH_Shell shell("TestShell");
    SOSH_Function_Base function("TestFunction");
    bool result = shell.AddFunction(function);

    EXPECT_TRUE(result);
}

// Тестирование функции FindFunction
TEST(SOSH_ShellTest, FindFunction) {
    SOSH_Shell shell("TestShell");
    SOSH_Function_Base function("TestFunction");
    shell.AddFunction(function);

    SOSH_Function_Base* result = shell.FindFunction("TestFunction");

    EXPECT_EQ(result, &function);
}

// Тестирование функции ListFunction
TEST(SOSH_ShellTest, ListFunction) {
    SOSH_Shell shell("TestShell");
    SOSH_Function_Base function1("TestFunction1");
    SOSH_Function_Base function2("TestFunction2");
    shell.AddFunction(function1);
    shell.AddFunction(function2);

    std::vector<std::reference_wrapper<SOSH_Function_Base>> result = shell.ListFunction();

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].get().GetName(), "TestFunction1");
    EXPECT_EQ(result[1].get().GetName(), "TestFunction2");
}*/

// Тестирование функции GetName
TEST(SOSH_ShellTest, GetName) {
    SOSH_Shell shell("TestShell");

    std::string result = shell.GetName();

    EXPECT_EQ(result, "TestShell");
}
