#include "API/sshell_api.h"

/*
double sum(double x, double y){
    return x + y;
}

void prt() {
    std::cout << "Thank you." << std::endl;
}

int add(int a, int b) {
    return a + b;
}

double multiply(double a, double b) {
    return a * b;
}

int subtract(int x, int y) {
    return x - y;
}

int subtract2(int x, int y, int z) {
    return x - y + z;
}

void foo(int a, float b, const char* c) {
    std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;
}

void print_num(int i)
{
    std::cout << i << '\n';
}
*/

/*
template<typename Func>
class MyClass {
public:
    MyClass(Func func) : func_(std::move(func)) {}

    template<typename... Args>
    void call_func(Args&&... args) {
        std::invoke(func_, std::forward<Args>(args)...);
    }

private:
    Func func_;
};
*/

/*
template <typename F>
auto get_arg_types(F* f) {
    using func_type = std::decay_t<F>;
    using args_type = std::tuple<typename std::decay_t<decltype(&func_type::operator())>::argument_type...>;
    return args_type{};
}*/

//void foo(int x, double y, char z) {}


double sum(double x, double y){
    return x + y;
}

void print() {
    std::cout << "you." << std::endl;
}

int main() {
    // Класс SOSH_Function2 объявлен в файле src/API/SOSH_Function.h

    // Обьявление экземпляра класса с функцией сумирующей double числа
    SOSH_Function2 f2("sum", sum);
    double z = f2.apply(4, 5);
    std::cout << std::to_string(z) << std::endl;

   // Создание и запись в контейнер эксзепляра класса с функцией sum
    std::vector<std::any> container;
    container.emplace_back(&f2);
    auto obj = std::any_cast<SOSH_Function2<decltype(sum)>*>(container[0]);
    double z2 = obj->apply(78, 5);
    std::cout << std::to_string(z2) << std::endl;


    // Обьявление экземпляра класса с функцией выводящая сообщение в терминал
    SOSH_Function2 f3("print", print);
    f3.apply();

    // Запись в контейнер эксзепляра класса с функцией print
    container.emplace_back(&f3);
    auto obj2 = std::any_cast<SOSH_Function2<decltype(print)>*>(container[1]);
    obj2->apply();



    /*
    std::function geget = sum;
    std::vector<std::any> container35;
    container35.emplace_back(geget);
    auto obj35 = std::any_cast<std::function<double (double, double)>>(container35[0]);
    */

    /*
    auto lambda1 = [](int x) { std::cout << "lambda1: " << x * x << std::endl; };
    auto lambda2 = [](double x) { std::cout << "lambda2: " << x * x << std::endl; };

    std::vector<std::any> container;
    container.emplace_back(MyClass<std::function<void(int)>>{lambda1});
    container.emplace_back(MyClass<std::function<void(double)>>{lambda2});

    for (const auto& elem : container) {
        if (elem.type() == typeid(MyClass<std::function<void(int)>>)) {
            auto obj = std::any_cast<MyClass<std::function<void(int)>>>(elem);
            obj.call_func(5);
        } else if (elem.type() == typeid(MyClass<std::function<void(double)>>)) {
            auto obj = std::any_cast<MyClass<std::function<void(double)>>>(elem);
            obj.call_func(3.14);
        }
    }
    */

    /*
    SOSH_Parser pars;
    std::vector<SOSH_Token> out;
    out = pars.Tokenize("sum qwer 4.667 8");

    SOSH_Token token(Token_t::SOSH_DOUBLE, "1.1");
    double one = token.Value<double>();
    std::cout << std::to_string(one) << std::endl;
    std::string two = token.Value();
    */
    
    /*
    double t = SafeCall(sum, 5, 16);
    std::cout << std::to_string(t) << std::endl;
    SafeCall(prt, t);
    */

   /*
   double x=5,y=6;

   //SOSH_Function2 f2("fee", sum);
   //f2.SafeCall(x,y);
   SOSH_Function2 f2("dvvd",sum);
   double z = f2.apply(x, y);
   std::cout << std::to_string(z) << std::endl;

   SOSH_Function2 f3("gdfg",prt);
   f3.apply();

   */

   //SOSH_Function2* arr = new SOSH_Function2("sum", sum);
   //std::vector<SOSH_Function2<decltype(sum)>> functions;

   //functions.push_back(f2);
   //functions.push_back(f3);

   //SOSH_Function2 f4;

   //void* krt = sum();
   //apply(sum, x, y);

   //std::cout << std::to_string(apply(sum, x, y)) << std::endl;

   //SOSH_Function3 ff("dvvd", sum);
   //double z = ff.apply(x, y);

   //std::vector<std::shared_ptr<SOSH_Function2>> tytdghdg;

   //std::vector<std::any> v;
   //v.push_back(&f2);
   //auto& t = v[0].type();
   //std::any_cast<std::function<double(double,double)>>(v[0]);
   //std::cout << std::to_string(t) << std::endl;

   //using Sig = Signature<decltype(prt)>;
    //Sig s; //ok

    //std::any df = std::function<decltype(prt)>;

    //std::any faa = f2;

    /*
    std::function<decltype(sum)> square = sum;
    std::cout << square(44,22) << std::endl << std::endl;
    std::any a = square;
    std::cout << std::any_cast<std::function<decltype(sum)>>(a)(5,6) << std::endl;

    std::function wfrfr = sum;
    std::cout << std::to_string(wfrfr(8, 7)) << std::endl;

    std::function<decltype(prt)> f_display_31337 = prt;
    f_display_31337();

    */

    //std::cout << std::to_string(f_display_31337(2,3)) << std::endl;
   //auto t = std::make_tuple(f3);

   // создание вектора экземпляров класса SOSH_Function2
    //std::vector<SOSH_Function2<decltype(add)>> functions;

    // добавление экземпляров класса в вектор
    //functions.push_back(SOSH_Function2<decltype(add)>("addition", [](int x, int y){ return x + y; }));
    //functions.push_back(SOSH_Function2<decltype(subtract)>("subtraction", [](int x, int y){ return x - y; }));
    //functions.push_back(SOSH_Function2<decltype(subtract2)>("subtraction2", subtract2));
    // вызов метода apply на каждом экземпляре класса в векторе

    //FunctionWrapper<int, int, int> addWrapper(add, 1, 2);

    //std::cout << std::to_string(addWrapper.apply(3, 4)) << std::endl;
    /*
    FunctionWrapper wrapper(foo, 42, 3.14f, "hello");
    wrapper();

    FunctionWrapper wrapper2(add, 2, 3);
    int fg = wrapper2();
    std::cout << std::to_string(fg) << std::endl;
    */
    /*
   SOSH_Function2<int(int, int)> func1("add", add);
    SOSH_Function2<int(int, int)> func2("subtract", subtract);

    // Create an array of SOSH_Function_Base*
    SOSH_Function_Base* functions[] = { &func1, &func2 };
    */
    /*
   SOSH_Function2 func1("add", add);
    SOSH_Function2 func2("subtract", subtract);

    // Create an array of pointers to SOSH_Function_Base
    SOSH_Function_Base* functions[] = { &func1, &func2 };

    functions[0]->apply(2,3);
    */

};
