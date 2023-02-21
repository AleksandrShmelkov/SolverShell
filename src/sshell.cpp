#include "API/sshell_api.h"

double sum(double x, double y){
    return x + y;
}

int main() {
    /*SOSH_Manager Manager;
    Manager.CreateShell("Shell1");
    SOSH_Shell Shell1 = Manager.FindShell("Shell1");

    SOSH_Function func("sum", sum);
    Shell1.AddFunction(func);
    SOSH_Function func2 = Shell1.FindFunction("sum");

    double f = 3, k = 7;
    std::cout << func2.Run(f, k) << std::endl;*/


    SOSH_Parser pars;
    std::vector<SOSH_Token> out;
    out = pars.Tokenize("sum qwer 4.667 8");

    SOSH_Token token(Token_t::SOSH_DOUBLE, "1.1");
    double one = token.Value<double>();
    std::cout << std::to_string(one) << std::endl;
    std::string two = token.Value();

    /*
    Shell1.DeclareFunction("summ");
    std::cout << "Get: " << Shell1.FindFunction("summ").get() << std::endl;
    std::vector<SOSH_Function> list;
    list = Shell1.ListFunction();
    std::cout << "List: " << std::endl;
    for (int i = 0; i < list.size(); i++) {
        std::cout << list.at(i).get() << std::endl;
    }
    return 0;
    */
};
