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
    std::optional<SOSH_Token> token_return;
    std::vector<SOSH_Token> tokens_args;
public:
    virtual ~SOSH_Function2_Base() = default;

    template<class R, class... Args>
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
        std::tuple<Args&...> ref_tuple = std::apply([](auto&... args){ return std::make_tuple(std::ref(args)...); }, arg_tuple);

        std::vector<std::string> args_type_controller;
        args_type_controller.reserve(sizeof...(Args));
        std::apply([&args_type_controller](auto&&... elems){
            (args_type_controller.emplace_back(typeid(elems).name()), ...);
        }, arg_tuple);
        //std::vector<bool> ref_vector = {std::is_reference<Args>::value...};
        std::string return_type_controller = typeid(R*).name();
        if constexpr (std::is_void_v<R>) {
            std::string info = applyWrapper(return_type_controller, args_type_controller, sizeof...(args), ref_tuple);
        } else {
            R result;
            std::string info = applyWrapper(return_type_controller, args_type_controller, sizeof...(args), ref_tuple, &result);
            return result;
        };
    };

    template<typename R, typename... Args>
    auto apply2(Args&&... args){
        auto func = dynamic_cast<SOSH_Function2<R, Args...> *>(this);
        if( func == nullptr ) { throw std::runtime_error("casting failed"); };
        return func->apply(std::forward<Args>(args)...);
    };

    virtual std::string applyWrapper(std::string &return_type_controller, std::vector<std::string> &args_base_type_controller, int count, ...) = 0;
};

template<class R, class... Args>
class SOSH_Function2 : public SOSH_Function2_Base {
private:
    typedef R (*Func)(Args...);
    Func func;
    std::tuple<Args...> args;
public:
    SOSH_Function2(std::string s, Func f) : func(f), args(std::tuple<Args...>{}) {
        this->name = s;
        this->type = typeid(R(Args...));
        this->r_type = typeid(R);
    };

    SOSH_Function2(const SOSH_Function2& other) : func(other.func), args(other.args) { // copy constructor 
        this->name = other.name;
        this->type = other.type;
        this->r_type = other.r_type;
    };

    SOSH_Function2(SOSH_Function2&& other) noexcept : func(std::move(other.func)), args(std::move(other.args)) { // move constructor  
        this->name = std::move(other.name);
        this->type = std::move(other.type);
        this->r_type = std::move(other.r_type);
    };

    void DeclareReturn(SOSH_Token token){
        this->token_return = token;
    };

    void DeclareArgs(SOSH_Token token){
        this->tokens_args.push_back(token);
    };

    R apply(Args&&... args){
        return func(std::forward<Args>(args)...);
        //return func(std::forward<SOSH_Token>(args.Value())...);
    };

    R apply(std::tuple<Args...> args_tuple){
        return std::apply(func, std::move(args_tuple));
    };

    std::string applyWrapper(std::string &return_type_controller, std::vector<std::string> &args_base_type_controller, int count, ...) override {
        std::vector<std::string> args_type_controller;
        args_type_controller.reserve(sizeof...(Args));
        std::apply([&args_type_controller](auto&&... elems){
            (args_type_controller.emplace_back(typeid(elems).name()), ...);
        }, args);
        
        if (return_type_controller != typeid(R*).name()) { return "Несоответствие возвращаемого типа."; };
        if (args_base_type_controller.size() != args_type_controller.size()) { return "Несоответствие количества аргументов."; };
        for (std::size_t i = 0; i < args_base_type_controller.size(); ++i) {
            if (args_base_type_controller[i] != args_type_controller[i]) {
                return "Несоответствие аргумента №"+std::to_string(i)+".";
            };
        };
        
        va_list ptr_type_controller;
        va_start(ptr_type_controller, count);
        std::tuple<Args&...> args_tuple = va_arg(ptr_type_controller, std::tuple<Args&...>);
        //using conditional_tuple = std::tuple<std::conditional_t<std::is_rvalue_reference_v<Args>, Args&, Args>...>;
        //conditional_tuple args_tuple = va_arg(ptr_type_controller, conditional_tuple);
        if constexpr (std::is_void_v<R>) {
            apply(args_tuple);
            return "ok void";
        } else {
            auto res = apply(args_tuple);
            auto result = va_arg(ptr_type_controller, R*);
            *result = res;
            return "ok return";
        };
        va_end(ptr_type_controller);

        //std::tuple<int, double, std::string> tp2(1, 2.0, std::string("c"));
        //std::tuple<float, int, std::string> tpl_template(0.0f, 0, std::string(""));
        //auto tpl_converted = tuple_convert(tp2, tpl_template);

        //std::tuple<int, double, char> tpl(1, 2.0, 'c');
        //auto tpl_reversed = tuple_reverse(tpl);
    };
};











class SOSH_Function3_Base {
protected:
    std::string name;
    Token_t type_return;
    std::vector<Token_t> type_args;
public:
    virtual ~SOSH_Function3_Base() = default;

    template<typename... Token>
    auto apply(Token&&... args){
        static_assert((std::is_same_v<SOSH_Token, std::remove_reference_t<Token>> && ...), "All arguments to apply must have type Token_t");
        std::vector<SOSH_Token> token_args = {args...};
        std::tuple<Token...> arg_tuple(std::forward<Token>(args)...);
        std::tuple<Token&...> ref_tuple = std::apply([](auto&... args){ return std::make_tuple(std::ref(args)...); }, arg_tuple);

        if (type_args.size() == token_args.size()) {
            int i = 0;
            for (;i < token_args.size(); i++) {
                if (type_args[i] != token_args[i].GetType()) { break; };
            };

            if (token_args.size() == i) { 
                return applyWrapper(sizeof...(args), ref_tuple);
            } else {
                std::cout << "Inconsistency with the expected type of argument. Expected " 
                    << token_names[static_cast<int>(type_args[i])] << " but received " 
                    << token_names[static_cast<int>(token_args[i].GetType())] << "." << std::endl;
            };
        } else {
            std::cout << "A mismatch in the number of arguments. The number of arguments when the function is called is not the same as the number of its mandatory arguments." << std::endl;
        };
        
        return SOSH_Token(Token_t::SOSH_UNDEFINED, "");
    };

    virtual SOSH_Token applyWrapper(int count, ...) = 0;
};

template <typename Args> struct ToType2_ { using type = SOSH_Token&; };
template <typename... Args> using ToType2 = typename ToType2_<Args...>::type;

template<class R, class... Args>
class SOSH_Function3 : public SOSH_Function3_Base {
private:
    typedef R (*Func)(Args...);
    Func func;
    using ArgsToToken = std::tuple<ToType2<Args>...>;
public:
    SOSH_Function3(std::string s, Func f) : func(f) {
        this->name = s;
    };
    SOSH_Function3(const SOSH_Function3& other) : func(other.func) { // copy constructor 
        this->name = other.name;
    };
    SOSH_Function3(SOSH_Function3&& other) noexcept : func(std::move(other.func)), args(std::move(other.args)) { // move constructor  
        this->name = std::move(other.name);
    };

    void AddReturn(Token_t type){
        this->type_return = type;
    };
    void AddArgs(Token_t type){
        this->type_args.push_back(type);
    };

    template<class... Args2>
    R apply(Args2&&... args){
        return func(std::forward<Args2>(args)...);
    };

    R apply(ArgsToToken args_tuple){
        return std::apply(func, std::forward<Args>(args_tuple.GetValue<Args>())...);
    };

    R apply(std::tuple<Args...> args_tuple){
        return std::apply(func, std::move(args_tuple));
    };

    SOSH_Token applyWrapper(int count, ...) override {   
        va_list ptr;
        va_start(ptr, count);
        auto args_tuple = va_arg(ptr, ArgsToToken);
        va_end(ptr);

        std::tuple<Args...> true_tuple = std::apply([](auto&... args){ 
            return std::make_tuple(std::forward<Args>(args.GetValue<Args>())...); 
        }, args_tuple);

        auto res = std::to_string(apply(true_tuple));
        SOSH_Token res_token(this->type_return, res);
        return res_token;
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