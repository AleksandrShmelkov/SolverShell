#ifndef SOSH_FUNCTION_H
#define SOSH_FUNCTION_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <any>

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

template<class Function>
class SOSH_Function2 {
private:
    std::string name;
    //double (*link)(double,double); // void*
    //T link;
    //std::string arg;
    //Func func;
    //void* link;
    Function&& func;
public:
    SOSH_Function2() = default;
    SOSH_Function2(std::string s, Function&& f) :name(s), func(f) {};
    template<class... Args> 
    auto apply(Args&&... args){
        return func(std::forward<Args>(args)...);
    }
};

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