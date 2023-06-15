#include "API/sshell_api.h"
#include "Equation.h"
#include <set>
#include <unordered_set>

constexpr Token_t TInt = Token_t::SOSH_INT;
constexpr Token_t TDouble = Token_t::SOSH_DOUBLE;
constexpr Token_t TString = Token_t::SOSH_STRING;

int sum(int x, double y, std::string z) {
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

void test_sum_TokenArgs(){
    SOSH_Function SOSH_Function_sum("sum", sum);
    SOSH_Function_sum.AddReturn(TInt);
    SOSH_Function_sum.AddArgs(TInt);
    SOSH_Function_sum.AddArgs(TDouble);
    SOSH_Function_sum.AddArgs(TString);

    SOSH_Function_Base& SOSH_Function_Base_sum = SOSH_Function_sum;
    SOSH_Token t1(TInt, "5");
    SOSH_Token t2(TDouble, "3.4");
    SOSH_Token t3(TString, "hell");
    SOSH_Token result = SOSH_Function_Base_sum.apply(t1, t2, t3);
    std::cout << "Result type: " << typeid(result).name() << std::endl;
    std::cout << "Result: " << result.GetValue() << std::endl;
};

void test_add_TokenArgs(){
    SOSH_Function SOSH_Function_sum("add", add);
    SOSH_Function_sum.AddReturn(TInt);
    SOSH_Function_sum.AddArgs(TInt);
    SOSH_Function_sum.AddArgs(TInt);

    SOSH_Function_Base& SOSH_Function_Base_sum = SOSH_Function_sum;
    SOSH_Token t1(TInt, "5");
    SOSH_Token t2(TInt, "6");
    SOSH_Token result = SOSH_Function_Base_sum.apply(t1, t2);
    std::cout << "Result type: " << typeid(result).name() << std::endl;
    std::cout << "Result: " << result.GetValue() << std::endl << std::endl;
};

void test_print_TokenArgs(){
    SOSH_Function SOSH_Function_sum("print", print);
    SOSH_Function_Base& SOSH_Function_Base_sum = SOSH_Function_sum;
    SOSH_Token result = SOSH_Function_Base_sum.apply();
    std::cout << "Result type: " << typeid(result).name() << std::endl;
    std::cout << "Result: " << result.GetValue() << std::endl << std::endl;
};

void test_pars(){
    SOSH_Function SOSH_Function_sum("sum", sum);
    SOSH_Function_sum.AddReturn(TInt);
    SOSH_Function_sum.AddArgs(TInt);
    SOSH_Function_sum.AddArgs(TDouble);
    SOSH_Function_sum.AddArgs(TString);
    SOSH_Function_Base& SOSH_Function_Base_sum = SOSH_Function_sum;

    SOSH_Shell BaseEqsCounter("BaseEqsCounter");
    BaseEqsCounter.AddFunction(SOSH_Function_Base_sum);

    std::string input = "sum 3 5.6 Hello";
    SOSH_Parser pars;
    std::vector<SOSH_Token> tokens = pars.Tokenize(input);

    SOSH_Token result = SOSH_Function_Base_sum.call(tokens);
    std::cout << "Result: " << result.GetValue() << std::endl << std::endl;
};

void Equation_func(int a, int b, int c){
    Equation EQ = Equation();
    EQ.EQ_AddEquation(a, b, c);
    EQ.EQ_CalcRoots();
    EQ.EQ_PrintRoots();
};

void Equation_line_func(int a, int b){
    Equation EQ = Equation();
    EQ.EQ_AddEquation(a, b);
    EQ.EQ_CalcRoots();
    EQ.EQ_PrintRoots();
};

void test_Equation(){
    //Equation_func(1, -8, 16);

    SOSH_Function SOSH_Equation_func("equation", Equation_func);
    SOSH_Equation_func.AddArgs(TInt);
    SOSH_Equation_func.AddArgs(TInt);
    SOSH_Equation_func.AddArgs(TInt);
    SOSH_Function_Base& SOSH_Equation_Base_func = SOSH_Equation_func;

    SOSH_Shell BaseEqsCounter("BaseEqsCounter");
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_func);
    auto BaseEqsCounter_func = BaseEqsCounter.FindFunction("equation");

    SOSH_Parser pars;
    std::cout << "\nsosh> ";
    std::string input = "equation 1 -8 16";
    //getline(std::cin, input);
    std::vector<SOSH_Token> tokens = pars.Tokenize(input);

    std::cout << std::endl;
    BaseEqsCounter_func->call<3>(tokens);
    std::cout << std::endl;

    //getline(std::cin, input);

    /*std::tuple<SOSH_Token> t1 = SOSH_Token(TInt, "5");
    std::tuple<SOSH_Token> t2 = SOSH_Token(TInt, "6");
    auto tt = std::tuple_cat(t1, t2);
    auto buff = tt;
    
    std::tuple<SOSH_Token> t3 = SOSH_Token(TInt, "7");
    delete tt;
    auto tt = std::tuple_cat(buff, t3);
    delete buff;
    auto buff = tt;*/
};

int main() {
    //system("chcp 65001");

    /*
    std::cout << "\n ***  test_sum_int_double  ***" << std::endl << std::endl;
    test_sum_int_double();

    std::cout << "\n ***  test_print  ***" << std::endl << std::endl;
    test_print();

    std::cout << "\n ***  test_add  ***" << std::endl << std::endl;
    test_add();

    std::cout << "\n ***  test_SOSH_Function2_Base_Create  ***" << std::endl << std::endl;
    test_SOSH_Function2_Base_Create();

    std::cout << "\n ***  test_sum_TokenArgs  ***" << std::endl << std::endl;
    test_sum_TokenArgs();

    std::cout << "\n ***  test_add_TokenArgs  ***" << std::endl << std::endl;
    test_add_TokenArgs();

    std::cout << "\n ***  test_print_TokenArgs  ***" << std::endl << std::endl;
    test_print_TokenArgs();

    std::cout << "\n ***  test_pars  ***" << std::endl << std::endl;
    test_pars();
    */

    //std::cout << "\n ***  test_Equation  ***" << std::endl << std::endl;
    test_Equation();

};
