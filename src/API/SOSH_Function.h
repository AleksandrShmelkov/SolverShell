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
    //SOSH_Token token_return;
    std::vector<SOSH_Token> tokens_args;
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
        //token_return = token;
    };

    void DeclareArgs(SOSH_Token token){
        tokens_args.push_back(token);
    };

    R apply(Args&&... args){
        return func(std::forward<Args>(args)...);
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









/*
template <class data_type>
class copy_on_write
{
public:
    copy_on_write(data_type* data)
        : m_data(data) {
    }
    data_type const* operator -> () const {
        return m_data.get();
    }
    data_type* operator -> () {
        if (!m_data.unique())
            m_data.reset(new data_type(*m_data));
        return m_data.get();
    }
private:
    std::shared_ptr<data_type> m_data;
};

class object {
public:
    object() = default;
    template <class T>
    void set(T data){
        m_data = data;
    };
    auto get(){
        return m_data;
    };
protected:
    class data;
private:
    copy_on_write<data> m_data;
};*/


/*
class SOSH_Function3_Base {
protected:
    std::string name;
    std::optional<std::type_index> r_type;
public:
    virtual ~SOSH_Function3_Base() = default;

    template<typename R>
    static SOSH_Function3_Base* Create(std::string name, R* func){
        return new SOSH_Function3<R>(name, func);
    };

    std::string GetName(){
        return name;
    };

    std::string GetReturnType(){
        return r_type.value().name();
    };

    template<typename R, typename... Args>
    auto apply(Args&&... args){
        typedef R (*typereturn)(Args...) ;
        auto func = dynamic_cast<SOSH_Function3<R>*>(this);

        //std::tuple<Args...> test(std::forward<Args>(args)...);
        //std::cout << "SOSH_Function3_Base test: " << typeid(test).name() << std::endl;
        //std::cout << "SOSH_Function3_Base func: " << typeid(func).name() << std::endl;

        //if( func == nullptr ) { throw std::runtime_error("casting failed"); };
        
        return func->apply(std::forward<Args>(args)...);
        //return 0;
        //return static_cast<SOSH_Function3<R>&>(*this).apply_impl(std::forward<Args>(args)...);
    };
};

template<typename R>
class SOSH_Function3;

template<typename R, typename... Args>
class SOSH_Function3<R(Args...)> : public SOSH_Function3_Base {
private:
    typedef R(*Func)(Args...);
    Func func;
public:
    SOSH_Function3(std::string s, Func f) : func(f) {
        this->name = s;
        this->r_type = typeid(R);
    };
    
    SOSH_Function3(const SOSH_Function3& other) : func(other.func) { // copy constructor 
        this->name = other.name;
        this->r_type = other.r_type;
    };

    SOSH_Function3(SOSH_Function3&& other) noexcept : func(std::move(other.func)) { // move constructor  
        this->name = std::move(other.name);
        this->r_type = std::move(other.r_type);
    };

    auto apply(Args... args) {
        std::cout << "Vhod" << std::endl;
        std::tuple<Args...> test(args...);
        std::cout << "SOSH_Function3 test: " << typeid(test).name() << std::endl;
        std::cout << "SOSH_Function3 func: " << typeid(func).name() << std::endl;
        return func(args...);
    };
};
*/


//  ------------------------------------------------

/*
template<typename R>
class SOSH_Function3 : public SOSH_Function3_Base {
private:
    typedef R* Func;
    Func func;
public:
    SOSH_Function3(std::string s, Func f) : func(f) {
        this->name = s;
        this->r_type = typeid(R);
    };
    
    SOSH_Function3(const SOSH_Function3& other) : func(other.func) { // copy constructor 
        this->name = other.name;
        this->r_type = other.r_type;
    };

    SOSH_Function3(SOSH_Function3&& other) noexcept : func(std::move(other.func)) { // move constructor  
        this->name = std::move(other.name);
        this->r_type = std::move(other.r_type);
    };

    template<typename... Args>
    auto apply(Args&&... args) {
        std::cout << "Vhod" << std::endl;
        std::tuple<Args...> test(std::forward<Args>(args)...);
        std::cout << "SOSH_Function3 test: " << typeid(test).name() << std::endl;
        std::cout << "SOSH_Function3 func: " << typeid(func).name() << std::endl;
        //return func(std::forward<Args>(args)...);
        return 0;
    };
};*/

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