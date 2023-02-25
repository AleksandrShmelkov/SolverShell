#include "API/sshell_api.h"

double sum(double x, double y){
    return x + y;
}

void prt(double u) {
    std::cout << "fsgdf" << std::endl;
}

int main() {
    SOSH_Parser pars;
    std::vector<SOSH_Token> out;
    out = pars.Tokenize("sum qwer 4.667 8");

    SOSH_Token token(Token_t::SOSH_DOUBLE, "1.1");
    double one = token.Value<double>();
    std::cout << std::to_string(one) << std::endl;
    std::string two = token.Value();
    
    /*
    double t = SafeCall(sum, 5, 16);
    std::cout << std::to_string(t) << std::endl;
    SafeCall(prt, t);
    */
   double x=5,y=6;

   //SOSH_Function2 f2("fee", sum);
   //f2.SafeCall(x,y);
   SOSH_Function2 f2("dvvd",sum);
   double z = f2.apply(x, y);
   std::cout << std::to_string(z) << std::endl;

   SOSH_Function2 f3("gdfg",prt);
   f3.apply(x);

   //SOSH_Function2 f4;

   //void* krt = sum();
   //apply(sum, x, y);

   //std::cout << std::to_string(apply(sum, x, y)) << std::endl;

   //SOSH_Function3 ff("dvvd", sum);
   //double z = ff.apply(x, y);

   std::vector<std::any> va;
   va.emplace_back(&f2);
};
