#ifndef SOSH_FUNCTION_H
#define SOSH_FUNCTION_H

#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <tuple>
#include <functional>
#include <vector>
#include <any>
#include <type_traits>
#include <typeinfo>
#include <utility>

/*
template<class Function>
class SOSH_Function {
private:
    std::string name;
    Function&& func;
public:
    SOSH_Function() = default;
    SOSH_Function(std::string s, Function&& f) :name(s), func(f) {};
    template<class... Args> 
    auto apply(Args&&... args){
        return func(std::forward<Args>(args)...);
    }
    bool EditFunction(std::string &s, Function&& f){
        name = s;
        func = f;
        return true;
    };
    std::string GetName(){
        return name;
    };
};
*/

template<class Function>
class SOSH_Function2 {
private:
    std::string name;
    Function&& func;
public:
    SOSH_Function2(std::string s, Function&& f) :name(s), func(f) {};
    template<class... Args> 
    auto apply(Args&&... args){
        return func(std::forward<Args>(args)...);
    }
};

class SOSH_Function {
private:
    std::string name;
    double (*link)(double,double); // void*
    std::string arg;
public:
    SOSH_Function() = default;
    SOSH_Function(const std::string &s, double (*l)(double,double)) :name(s), link(l) {};
    bool EditFunction(const std::string &s, double (*l)(double,double));
    double Run(double i, double j);
    std::string GetName();
};

/*
class SOSH_Function_Base {
public:
    virtual ~SOSH_Function_Base() {}
    template<class... Args> 
    auto apply(Args&&... args){
        return func(std::forward<Args>(args)...);
    }
}; //: public SOSH_Function_Base 
*/

/*
class SOSH_Function6 {
public:
    //SOSH_Function2() = default;
    SOSH_Function2(std::string s, Function&& f) :name(s), func(f) {};
private:
    std::string name;
    //double (*link)(double,double); // void*
    //T link;
    //std::string arg;
    //Func func;
    //void* link;
    std::function<decltype(prt)> f_display_31337 = prt;
};
*/

/*
template<typename S>
struct Signature;

template<typename R, typename ...Args>
struct Signature<R ( * )(Args...)> {
    using RetType = R;

    using Arguments = std::tuple<Args...>;
};

template<typename Func>
void test(Func f) {
    using Sig = Signature<Func>;
    Sig s; //Error: Sig<Func> - undefined struct
}
*/

/*
class FunctionWrapper {
public:
    template <typename Func, typename... Args>
    FunctionWrapper(Func func, Args&&... args)
        : func_(std::bind(func, std::forward<Args>(args)...)) {}

    void operator()() {
        func_();
    }

private:
    std::function<void()> func_;
};
*/

/*
template <typename ReturnType, typename... Args>
class FunctionWrapper {
public:
    FunctionWrapper(std::function<ReturnType(Args...)> func, Args... args)
        : func_(func), args_(std::make_tuple(args...)) {}

    ReturnType operator()() {
        return callFunc(typename std::make_index_sequence<sizeof...(Args)>{});
    }

private:
    template <std::size_t... Is>
    ReturnType callFunc(std::index_sequence<Is...>) {
        return func_(std::get<Is>(args_)...);
    }

    std::function<ReturnType(Args...)> func_;
    std::tuple<Args...> args_;
};
*/

/*
class SOSH_Function3 {
private:
    std::string name;
    //double (*link)(double,double); // void*
    //T link;
    //std::string arg;
    //Func func;
    //void* link;
    void* func;
public:
    SOSH_Function3() = default;
    SOSH_Function3(std::string s, void* f) :name(s), func(f) {};
    template<class Function, class... Args> 
    inline auto apply(Args&&... args){
        //Function&& func2 = *(Function*)func;
        //return func2(std::forward<Args>(args)...);
    }
};
*/

/*
template<class Func, class... Args>
typename std::result_of<Func(Args&&...)>::type 
SafeCall(Func func, Args&&... args) {
    try {
        return func(std::forward<Args>(args)...);
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    };
};
*/

/*
template<class Function, class... Args> 
inline auto apply(Function&& f, Args&&... args) -> decltype(f(std::forward<Args>(args)...))
{
    typedef decltype(f(std::forward<Args>(args)...)) ReturnType;
    return f(std::forward<Args>(args)...);
    //your code; you can use the above typedef.
}
*/

// SOSH_function.h .cpp в нем классы фунции и аргументов

#endif //SOSH_FUNCTION_H