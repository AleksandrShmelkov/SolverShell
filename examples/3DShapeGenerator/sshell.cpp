#include "API/sshell_api.h"
#include "api.h"

constexpr Token_t TInt = Token_t::SOSH_INT;
constexpr Token_t TDouble = Token_t::SOSH_DOUBLE;
constexpr Token_t TString = Token_t::SOSH_STRING;

std::string ShapeParam(std::string type_name, int param1, double param2) {
    ShapeType type;
    if (type_name == "Cylinder") {
        type = ShapeType::Cylinder;
    } else if (type_name == "Sphere") {
        type = ShapeType::Sphere;
    } else if (type_name == "Plane") {
        type = ShapeType::Plane;
    };
    //file_name = file_name+".csv";
    //const char* char_file_name = file_name.c_str();
    return CreateShapes({ type, param1, param2 });
};

int main() {
    system("chcp 65001");

    //ShapeType_func("torus.csv", "Cylinder", 10, 0);

    // Создание объектов функций
    SOSH_Function SOSH_Equation_create_shapes("create_shapes", ShapeParam);
    SOSH_Equation_create_shapes.AddReturn(TString);
    SOSH_Equation_create_shapes.AddArgs(TString);
    SOSH_Equation_create_shapes.AddArgs(TInt);
    SOSH_Equation_create_shapes.AddArgs(TDouble);
    SOSH_Function_Base& SOSH_Equation_Base_create_shapes = SOSH_Equation_create_shapes;

    // Добавление объектов функций в шелл
    SOSH_Shell ShapeGenerator("ShapeGenerator");
    ShapeGenerator.AddFunction(SOSH_Equation_Base_create_shapes);
    
    // Парсинг командной строки и выполнение функций
    SOSH_Parser pars;
    std::string input = "equ 1 -8 16";
    std::string result = "";
    while (true) {
        std::cout << "\nsosh> ";
        getline(std::cin, input);
        if ((input == "exit") || (input == "Exit")) { break; };
        if ((input == "help") || (input == "Help")) {
            std::vector<std::reference_wrapper<SOSH_Function_Base>> funcs_pool = ShapeGenerator.ListFunction();
            for (int i = 0; i < funcs_pool.size(); i++) {
                std::cout << "func - " << funcs_pool[i].get().GetName() << " (" << funcs_pool[i].get().GetTypeArgs() << ")" << std::endl;
            };
            continue;
        };
        
        std::vector<SOSH_Token> tokens = pars.Tokenize(input);

        auto ShapeGenerator_func = ShapeGenerator.FindFunction(tokens[0].GetValue());
        if (ShapeGenerator_func == nullptr) {
            std::cout << tokens[0].GetValue() << ": function not found." << std::endl;
        } else {
            result = ShapeGenerator_func->call<5>(tokens).GetValue();
        };
    };

    return 0;
};
