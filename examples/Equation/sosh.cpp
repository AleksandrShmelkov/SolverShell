#include "SOSH/API.h"
#include "Equation.h"

constexpr Token_t TInt = Token_t::SOSH_INT;
constexpr Token_t TDouble = Token_t::SOSH_DOUBLE;
constexpr Token_t TString = Token_t::SOSH_STRING;
Equation EQ = Equation();

void Equation_func(int a, int b, int c){
    EQ.EQ_AddEquation(a, b, c);
};

void Equation_line_func(int a, int b){
    EQ.EQ_AddEquation(a, b);
};

void Equation_calc_roots(){
    EQ.EQ_CalcRoots();
};

void Equation_print_roots(){
    EQ.EQ_PrintRoots();
};

int main() {
    //std::system("chcp 65001");
    std::system("chcp 1251");

    // Создание объектов функций
    SOSH_Function SOSH_Equation_add_equ("register_coefficients", Equation_func); //  рег_коэфф
    SOSH_Equation_add_equ.AddArgs(TInt);
    SOSH_Equation_add_equ.AddArgs(TInt);
    SOSH_Equation_add_equ.AddArgs(TInt);
    SOSH_Function_Base& SOSH_Equation_Base_add_equ = SOSH_Equation_add_equ;

    SOSH_Function SOSH_Equation_add_line_equ("register_linear_coefficients", Equation_line_func); //  рег_коэфф_лин
    SOSH_Equation_add_line_equ.AddArgs(TInt);
    SOSH_Equation_add_line_equ.AddArgs(TInt);
    SOSH_Function_Base& SOSH_Equation_Base_add_line_equ = SOSH_Equation_add_line_equ;

    SOSH_Function SOSH_Equation_calc_roots("compute_roots", Equation_calc_roots); //  вычислить_корни
    SOSH_Function_Base& SOSH_Equation_Base_calc_roots = SOSH_Equation_calc_roots;

    SOSH_Function SOSH_Equation_print_roots("display_roots", Equation_print_roots); //  отобразить_корни
    SOSH_Function_Base& SOSH_Equation_Base_print_roots = SOSH_Equation_print_roots;

    // Добавление объектов функций в шелл
    SOSH_Shell BaseEqsCounter("BaseEqsCounter");
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_add_equ);
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_add_line_equ);
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_calc_roots);
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_print_roots);
    
    // Парсинг командной строки и выполнение функций
    std::string input = "equ 1 -8 16";
    SOSH_Token result(Token_t::SOSH_UNDEFINED, "Empty.");
    while (true) {
        std::cout << "\nsosh> ";
        getline(std::cin, input);
        if ((input == "exit") || (input == "Exit")) { break; };
        if ((input == "help") || (input == "Help")) {
            std::vector<std::reference_wrapper<SOSH_Function_Base>> funcs_pool = BaseEqsCounter.ListFunction();
            for (int i = 0; i < funcs_pool.size(); i++) {
                std::cout << "func - " << funcs_pool[i].get().GetName() << " (" << funcs_pool[i].get().GetTypeArgs() << ")" << std::endl;
            };
            std::cout << "func - print ()"  << std::endl;
            continue;
        };
        if ((input == "print") || (input == "Print")) { 
            std::cout << "Result: " << result.GetValue() << std::endl;
            continue;
        };

        result = Interpreter::evaluate(input, BaseEqsCounter);
    };

    return 0;
};
