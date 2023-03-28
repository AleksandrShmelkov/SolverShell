#include "API/sshell_api.h"

int sum(int x, double y, std::string z) {
    std::cout << "x = " << x << " y = " << y << " z = " << z << "\n";
    return x + y;
};

void print() {
    std::cout << "Message" << std::endl;
};

void test_sum_int_double(){
    SOSH_Function2 SOSH_Function2_sum("sum", sum);
    double result = SOSH_Function2_sum.apply(4,5,"QWERTY");
    std::cout << "Result: " << result << std::endl << std::endl;

    SOSH_Function2_Base& SOSH_Function2_Base_sum = SOSH_Function2_sum;
    double result2 = SOSH_Function2_Base_sum.apply<int>(4,5.0,std::string("QWERTY"));
    std::cout << "Result: " << result2 << std::endl;
};

void test_SOSH_Function2_Base_Create(){
    auto SOSH_Function2_sum = SOSH_Function2_Base::Create("sum", sum);
};

void test_AddToken(){
    SOSH_Function2 SOSH_Function2_sum("sum", sum);
    SOSH_Token token1(Token_t::SOSH_FUNCTION_NAME, "sum");
    SOSH_Token token2(Token_t::SOSH_INT, "4");
    SOSH_Token token3(Token_t::SOSH_DOUBLE, "5.0");
    SOSH_Token token4(Token_t::SOSH_STRING, "QWERTY");
    SOSH_Function2_sum.AddToken(token1);
    SOSH_Function2_sum.AddToken(token2);
    SOSH_Function2_sum.AddToken(token3);
    SOSH_Function2_sum.AddToken(token4);
};

int main() {
    system("chcp 65001");

    test_sum_int_double();
    test_SOSH_Function2_Base_Create();
    test_AddToken();
};
