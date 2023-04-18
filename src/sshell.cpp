#include "API/sshell_api.h"

int sum(int x, double y, std::string z) {
    std::cout << typeid(z).name() << std::endl;
    std::cout << "x = " << x << " y = " << y << " z = " << z << "\n";
    return x + y;
};

void print() {
    std::cout << "Message" << std::endl;
};

int add(int a, int b) {
    std::cout << "a = " << a << " b = " << b << "\n";
    return a + b;
}

void test_sum_int_double(){
    SOSH_Function2 SOSH_Function2_sum("sum", sum);
    double result = SOSH_Function2_sum.apply(4,5,"QWERTY");
    std::cout << "Result: " << result << std::endl << std::endl;

    SOSH_Function2_Base& SOSH_Function2_Base_sum = SOSH_Function2_sum;
    //SOSH_Function2_Base* SOSH_Function2_Base_sum = &SOSH_Function2_sum;

    int a = 4;
    double b = 5.0;
    std::string c = "QWERTY";

    int result2 = SOSH_Function2_Base_sum.apply<int>(4,5.0,std::string("QWERTY"));
    std::cout << "Result: " << result2 << std::endl << std::endl;

    int result3 = SOSH_Function2_Base_sum.apply<int>(a,b,c);
    std::cout << "Result: " << result3 << std::endl;
};

void test_print(){
    SOSH_Function2 SOSH_Function2_print("print", print);
    SOSH_Function2_print.apply();

    SOSH_Function2_Base& SOSH_Function2_Base_print = SOSH_Function2_print;
    SOSH_Function2_Base_print.apply<void>();
};

void test_add(){
    SOSH_Function2 SOSH_Function2_add("add", add);
    int result = SOSH_Function2_add.apply(1,2);
    std::cout << "Result: " << result << std::endl << std::endl;

    SOSH_Function2_Base& SOSH_Function2_Base_add = SOSH_Function2_add;
    int a = 1;
    int b = 2;
    int result2 = SOSH_Function2_Base_add.apply<int>(1,2);
    std::cout << "Result: " << result2 << std::endl << std::endl;
    int result3 = SOSH_Function2_Base_add.apply<int>(a,b);
    std::cout << "Result: " << result3 << std::endl;
};

void test_SOSH_Function2_Base_Create(){
    auto SOSH_Function2_add = SOSH_Function2_Base::Create("add", add);
    int result = SOSH_Function2_add->apply2<int>(1,2);
    std::cout << "SOSH_Function2_add: " << result << std::endl << std::endl;
    delete SOSH_Function2_add;

    auto func = SOSH_Function2_Base::Create("add", add);
    int result2 = func->apply<int>(1,2);
    std::cout << "func: " << result2 << std::endl;
    delete func;
};

void test_AddToken(){
    SOSH_Function2 SOSH_Function2_sum("sum", sum);
    SOSH_Token token1(Token_t::SOSH_FUNCTION_NAME, "sum");
    SOSH_Token token2(Token_t::SOSH_INT, "4");
    SOSH_Token token3(Token_t::SOSH_DOUBLE, "5.0");
    SOSH_Token token4(Token_t::SOSH_STRING, "QWERTY");
    SOSH_Function2_sum.DeclareReturn(token1);
    SOSH_Function2_sum.DeclareArgs(token2);
    SOSH_Function2_sum.DeclareArgs(token3);
    SOSH_Function2_sum.DeclareArgs(token4);
};
/*
void test_sosh3(){
    SOSH_Function3 SOSH_Function3_sum("sum", sum);
    int result = SOSH_Function3_sum.apply(4,5,"QWERTY");
    std::cout << "Result: " << result << std::endl << std::endl;

    //SOSH_Function3_Base& SOSH_Function3_Base_sum = SOSH_Function3_sum;
    //SOSH_Function3_Base* SOSH_Function3_Base_sum = &SOSH_Function3_sum;
    std::shared_ptr<SOSH_Function3_Base> SOSH_Function3_Base_sum = std::make_shared<decltype(SOSH_Function3_sum)>(SOSH_Function3_sum);

    auto result2 = SOSH_Function3_Base_sum->apply<int>(4,5.0,std::string("QWERTY"));
    std::cout << "Result: " << typeid(result2).name() << std::endl << std::endl;
};
*/

int main() {
    //system("chcp 65001");

    std::cout << "\n ***  test_sum_int_double  ***" << std::endl << std::endl;
    test_sum_int_double();

    std::cout << "\n ***  test_print  ***" << std::endl << std::endl;
    test_print();

    std::cout << "\n ***  test_add  ***" << std::endl << std::endl;
    test_add();

    std::cout << "\n ***  test_SOSH_Function2_Base_Create  ***" << std::endl << std::endl;
    test_SOSH_Function2_Base_Create();

    std::cout << "\n ***  test_AddToken  ***" << std::endl << std::endl;
    test_AddToken();

    //std::cout << "\n ***  test_sosh3  ***" << std::endl << std::endl;
    //test_sosh3();

    std::cout << std::endl;

};
