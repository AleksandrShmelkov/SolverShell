//#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "SOSH/SOSH_Function.h"

// Mock function for testing
int Add(int a, int b) {
    return a + b;
}

/*// Test fixture for SOSH_Function
class SOSH_FunctionTest : public Test {
protected:
    void SetUp() override {
        // Create a SOSH_Function instance with the Add function
        function = std::make_unique<SOSH_Function<int, int, int>>("Add", &Add, "Add two integers");
        function->AddReturn(Token_t::SOSH_INT);
        function->AddArgs(Token_t::SOSH_INT);
        function->AddArgs(Token_t::SOSH_INT);
    }

    std::unique_ptr<SOSH_Function<int, int, int>> function;
};

TEST_F(SOSH_FunctionTest, GetName) {
    std::string name = function->GetName();
    EXPECT_EQ("Add", name);
}

TEST_F(SOSH_FunctionTest, GetDescription) {
    std::string description = function->GetDescription();
    EXPECT_EQ("Add two integers", description);
}

TEST_F(SOSH_FunctionTest, GetTypeArgs) {
    std::string typeArgs = function->GetTypeArgs();
    EXPECT_EQ("SOSH_INT, SOSH_INT", typeArgs);
}

TEST_F(SOSH_FunctionTest, CallWithValidArguments) {
    std::vector<SOSH_Token> tokens;
    tokens.push_back(SOSH_Token(Token_t::SOSH_INT, "3"));
    tokens.push_back(SOSH_Token(Token_t::SOSH_INT, "4"));

    SOSH_Token result = function->call<2>(tokens);
    EXPECT_EQ(Token_t::SOSH_INT, result.GetType());
    EXPECT_EQ("7", result.GetValue<std::string>());
}

TEST_F(SOSH_FunctionTest, CallWithInvalidArguments) {
    std::vector<SOSH_Token> tokens;
    tokens.push_back(SOSH_Token(Token_t::SOSH_INT, "3"));
    tokens.push_back(SOSH_Token(Token_t::SOSH_FLOAT, "4.5"));

    SOSH_Token result = function->call<2>(tokens);
    EXPECT_EQ(Token_t::SOSH_UNDEFINED, result.GetType());
}*/
