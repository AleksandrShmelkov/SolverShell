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
#include <unordered_map>
#include <memory>
#include <map>
#include <typeindex>
#include <optional>
#include <cstdarg>
#include <array>
#include <cassert>

#include "API/SOSH_Token.h"

template <typename... Ts, std::size_t... Is>
auto tuple_reverse_helper(const std::tuple<Ts...>& tpl, std::index_sequence<Is...>) {
    return std::make_tuple(std::get<sizeof...(Ts) - Is - 1>(tpl)...);
};

template <typename... Ts>
auto tuple_reverse(const std::tuple<Ts...>& tpl) {
    return tuple_reverse_helper(tpl, std::make_index_sequence<sizeof...(Ts)>{});
};

template <typename... Ts, typename... Us>
auto tuple_convert(const std::tuple<Ts...>& tpl, const std::tuple<Us...>& tpl_template) {
    static_assert(sizeof...(Ts) == sizeof...(Us), "Tuple sizes must match");
    return std::apply([](auto&&... args) {
        return std::make_tuple(static_cast<std::conditional_t<std::is_same_v<Ts, Us>, Ts, Us>>(args)...);
    }, tpl);
};

template <typename Args> struct ToType_ { using type = Args; };
template <typename... Args> using ToType = typename ToType_<Args...>::type;

class SOSH_Function2_Base {
protected:
    std::string name;
    std::optional<std::type_index> type;
    std::optional<std::type_index> r_type;
public:
    virtual ~SOSH_Function2_Base() = default;
    template<typename R, typename... Args>
    static SOSH_Function2_Base* Create(std::string name, R (*func)(Args...)){
        return new SOSH_Function2<R, Args...>(name, func);
    };
    std::string GetName(){
        return name;
    };
    std::string GetType(){
        return type.value().name();
    };
    std::string GetReturnType(){
        return r_type.value().name();
    };
    template<typename R, typename... Args>
    auto apply(Args&&... args){
        std::tuple<Args...> arg_tuple(std::forward<Args>(args)...);
        std::string args_type_controller = typeid(arg_tuple).name();
        R result;
        std::string return_type_controller = typeid(&result).name();
        //std::cout << "args2: " << args_type_controller << std::endl;
        //std::string result = applyWrapper(return_type_controller, args_type_controller, (sizeof...(args))+1, std::forward<Args>(args)..., &result);
        std::string info = applyWrapper(return_type_controller, args_type_controller, 2, arg_tuple, &result);
        return result;
    };
    virtual std::string applyWrapper(std::string &return_type_controller, std::string &args_type_controller, int count, ...) = 0;
};

template<class R, class... Args>
class SOSH_Function2 : public SOSH_Function2_Base {
private:
    typedef R (*Func)(Args...);
    Func func;
    std::tuple<ToType<Args>...> args;
    std::vector<SOSH_Token> tokens;
public:
    SOSH_Function2(std::string s, Func f) : func(f), args(std::tuple<ToType<Args>...>{}) {
        this->name = s;
        this->type = typeid(R(Args...));
        this->r_type = typeid(R);
    };
    SOSH_Function2(const SOSH_Function2& other) : func(std::move(other.func)), args(other.args) { // copy constructor 
        this->name = other.name;
        this->type = other.type;
        this->r_type = other.r_type;
    };
    SOSH_Function2(SOSH_Function2&& other) noexcept : func(std::move(other.func)), args(std::move(other.args)) { // move constructor  
        this->name = std::move(other.name);
        this->type = std::move(other.type);
        this->r_type = std::move(other.r_type);
    };
    void AddToken(SOSH_Token token){
        tokens.push_back(token);
    };
    R apply(Args&&... args){
        return func(std::forward<Args>(args)...);
    };
    R apply(std::tuple<Args...> args_tuple){
        return std::apply(func, std::move(args_tuple));
    };
    std::string applyWrapper(std::string &return_type_controller, std::string &args_type_controller, int count, ...) override {
        //std::cout << "return_type_controller: " << return_type_controller << std::endl;
        //std::cout << "R*: " << typeid(R*).name() << std::endl;
        //std::cout << "args_type_controller: " << args_type_controller << std::endl;
        //std::cout << "args: " << typeid(args).name() << std::endl;
        //std::cout << "args: " << (args_type_controller != typeid(args).name()) << std::endl;
        va_list ptr_type_controller;
        va_start(ptr_type_controller, count);
        //std::tuple<ToType<Args>...> args_tuple(std::forward<Args>(va_arg(ptr_type_controller, Args))...);
        if ((args_type_controller != typeid(args).name()) || (return_type_controller != typeid(R*).name())){
            return "Несоответствие типов.";
        };
        std::tuple<ToType<Args>...> args_tuple = va_arg(ptr_type_controller, std::tuple<ToType<Args>...>);
        //std::cout << "args_tuple: " << typeid(args_tuple).name() << std::endl;
        auto result = va_arg(ptr_type_controller, R*);
        va_end(ptr_type_controller);

        //auto args_tuple_reverse = tuple_reverse(args_tuple);
        if constexpr (std::is_void_v<R>) {
            apply(args_tuple);
            return "0";
        } else {
            auto res = apply(args_tuple);
            *result = res;
            return "0";
        };

        //std::tuple<int, double, std::string> tp2(1, 2.0, std::string("c"));
        //std::tuple<float, int, std::string> tpl_template(0.0f, 0, std::string(""));
        //auto tpl_converted = tuple_convert(tp2, tpl_template);

        //std::tuple<int, double, char> tpl(1, 2.0, 'c');
        //auto tpl_reversed = tuple_reverse(tpl);
    };
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

// SOSH_function.h .cpp в нем классы функций и аргументов

#endif //SOSH_FUNCTION_H