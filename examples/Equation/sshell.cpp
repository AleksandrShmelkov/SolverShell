#include "API/sshell_api.h"
#include "Equation.h"
#include <locale>

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
    //system("chcp 65001");
    setlocale(LC_ALL, "Russian");
    // Настраиваем кодировку ввода-вывода консоли
    //SetConsoleCP(65001);
    //SetConsoleOutputCP(65001);

    // Создание объектов функций
    SOSH_Function SOSH_Equation_add_equ("зарегистрировать_коэффициенты", Equation_func); // register_coefficients
    SOSH_Equation_add_equ.AddArgs(TInt);
    SOSH_Equation_add_equ.AddArgs(TInt);
    SOSH_Equation_add_equ.AddArgs(TInt);
    SOSH_Function_Base& SOSH_Equation_Base_add_equ = SOSH_Equation_add_equ;

    SOSH_Function SOSH_Equation_add_line_equ("зарегистрировать_линейные_коэффициенты", Equation_line_func); // register_linear_coefficients
    SOSH_Equation_add_line_equ.AddArgs(TInt);
    SOSH_Equation_add_line_equ.AddArgs(TInt);
    SOSH_Function_Base& SOSH_Equation_Base_add_line_equ = SOSH_Equation_add_line_equ;

    SOSH_Function SOSH_Equation_calc_roots("вычислить_корни", Equation_calc_roots); // compute_roots
    SOSH_Function_Base& SOSH_Equation_Base_calc_roots = SOSH_Equation_calc_roots;

    SOSH_Function SOSH_Equation_print_roots("отобразить_корни", Equation_print_roots); // display_roots
    SOSH_Function_Base& SOSH_Equation_Base_print_roots = SOSH_Equation_print_roots;

    // Добавление объектов функций в шелл
    SOSH_Shell BaseEqsCounter("BaseEqsCounter");
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_add_equ);
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_add_line_equ);
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_calc_roots);
    BaseEqsCounter.AddFunction(SOSH_Equation_Base_print_roots);
    
    // Парсинг командной строки и выполнение функций
    SOSH_Parser pars;
    std::string input = "equ 1 -8 16";
    while (true) {
        std::cout << "\nsosh> ";
        getline(std::cin, input);
        if ((input == "exit") || (input == "Exit")) { break; };
        if ((input == "help") || (input == "Help")) {
            std::vector<std::reference_wrapper<SOSH_Function_Base>> funcs_pool = BaseEqsCounter.ListFunction();
            for (int i = 0; i < funcs_pool.size(); i++) {
                std::cout << "func - " << funcs_pool[i].get().GetName() << " (" << funcs_pool[i].get().GetTypeArgs() << ")" << std::endl;
            };
            continue;
        };
        
        std::cout << "123 " << input << std::endl << std::endl;
        std::vector<SOSH_Token> tokens = pars.Tokenize(input);
        std::cout << "456 " << input << std::endl << std::endl;

        auto BaseEqsCounter_func = BaseEqsCounter.FindFunction(tokens[0].GetValue());
        if (BaseEqsCounter_func == nullptr) {
            std::cout << tokens[0].GetValue() << ": function not found." << std::endl;
        } else {
            BaseEqsCounter_func->call<3>(tokens);
        };
    };

    return 0;
};
