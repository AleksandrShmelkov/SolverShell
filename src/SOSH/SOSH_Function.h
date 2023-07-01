#ifndef SOSH_FUNCTION_H
#define SOSH_FUNCTION_H

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <typeindex>
#include <optional>
#include <cstdarg>
#include <sstream>

#include "SOSH_Token.h"


/**
 * @file SOSH_Function.h
 * @brief Объявление класса SOSH_Function_Base
 * @brief Объявление класса SOSH_Function
 */

/**
 * @class SOSH_Function_Base
 * @brief Базовый класс для функций, вызываемых в интерпретаторе SOSH.
 */
class SOSH_Function_Base {
public:
    virtual ~SOSH_Function_Base() = default;

    /**
     * @brief Метод для получения имени функции.
     * @return Имя функции.
     */
    std::string GetName() {
        return name;
    };

    /**
     * @brief Метод для получения описания функции.
     * @return Описание функции.
     */
    std::string GetDescription() {
        return description;
    };

    /**
     * @brief Метод для получения типов аргументов функции.
     * @return Строка, содержащая типы аргументов.
     */
    std::string GetTypeArgs() {
        std::string str_type_args = "";
        for (int i = 0; i < type_args.size(); i++) {
            str_type_args = str_type_args + token_names[static_cast<int>(type_args[i])] + ", ";
        };
        if (str_type_args != "") { str_type_args = str_type_args.substr(0, str_type_args.size()-2); };
        return str_type_args;
    };    

    /**
     * @brief Метод, который применяет функцию к аргументам и проверяет их типы.
     * 
     * Принимает переменное число аргументов типа SOSH_Token и вызывает метод applyWrapper()
     * с передачей аргументов для выполнения действий, определенных в наследниках класса.
     * Если типы аргументов соответствуют ожидаемым типам, вызывается метод applyWrapper(),
     * иначе выводится сообщение об ошибке и возвращается объект типа SOSH_Token
     * с типом SOSH_UNDEFINED.
     * 
     * @tparam Token Типы аргументов.
     * @param args Аргументы функции.
     * @return Результат выполнения функции.
     */
    template<typename... Token>
    auto apply(Token&&... args) {
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

    /**
     * @brief Метод, который обрабатывает вызов функции с переданными аргументами и вызывает соответствующую функцию apply.
     * 
     * Если передано один или более аргументов, вызывается функция apply_impl().
     * Если аргументов нет, вызывается функция apply() без аргументов.
     * 
     * @tparam max_n Максимальное число аргументов.
     * @param tokens Вектор объектов типа SOSH_Token, представляющих аргументы функции.
     * @return Результат выполнения функции.
     */
    template <size_t max_n = 20>
    auto call(std::vector<SOSH_Token> tokens) {
        if (max_n > 0) {
            if (tokens.size() > 1) {
                return call_impl<max_n>(tokens, 2, tokens[1]); 
            } else {
                return apply(); 
            };
        } else {
            std::cout << "Error: The maximum number of arguments cannot be less than or equal to zero. No function was called." << std::endl;
            return SOSH_Token(Token_t::SOSH_UNDEFINED, "");
        };
    };
	
	/**
     * @brief Метод, который обрабатывает вызов функции с переменным числом аргументов.
     * 
     * Если число аргументов меньше максимального, вызывается функция call_impl(),
     * иначе выводится сообщение об ошибке.
     * 
     * @tparam max_n Максимальное число аргументов.
     * @tparam Token Типы аргументов.
     * @param tokens Вектор объектов типа SOSH_Token, представляющих аргументы функции.
     * @param curr Текущий индекс аргумента.
     * @param args Аргументы функции.
     * @return Результат выполнения функции.
     */
    template <size_t max_n, typename... Token>
    auto call_impl(std::vector<SOSH_Token>& tokens, int curr, Token&&... args) { 
        if constexpr (max_n > 0) {
            if (curr < tokens.size()) {
                return call_impl<max_n-1>(tokens, curr+1, std::forward<Token>(args)..., tokens[curr]);
            } else {
                return apply(std::forward<Token>(args)...);
            };
        } else {
            std::cout << "Error: Maximum number of arguments exceeded. No function was called." << std::endl;
            return SOSH_Token(Token_t::SOSH_UNDEFINED, "");
        };
    };

    /**
     * @brief Абстрактный виртуальный метод, который вызывается для выполнения действий, определенных в наследниках класса.
     * 
     * Принимает переменное число аргументов и использует их для выполнения действий,
     * определенных в наследниках класса.
     * 
     * @param count Количество аргументов.
     * @param ... Аргументы функции.
     * @return Результат выполнения функции.
     */
    virtual SOSH_Token applyWrapper(int count, ...) = 0;
protected:
    std::string name; // имя функции
    std::string description; // описание функции
    Token_t type_return; // тип возвращаемого значения
    std::vector<Token_t> type_args; // список типов аргументов
};

/**
 * @brief Преобразует набор типов аргументов в тип SOSH_Token&.
 * @tparam Args Параметры шаблона.
 */
template <typename Args> struct ToType_ { using type = SOSH_Token&; };

/**
 * @brief Шаблонная алиас-обертка для преобразования набора типов аргументов в тип SOSH_Token&.
 * @tparam Args Параметры шаблона.
 */
template <typename... Args> using ToType = typename ToType_<Args...>::type;

/**
 * @brief Класс SOSH_Function представляет конкретную функцию, которая может быть вызвана в интерпретаторе.
 * 
 * Этот класс наследуется от класса SOSH_Function_Base и содержит поля и методы для работы с функциями.
 */
template<class R, class... Args>
class SOSH_Function : public SOSH_Function_Base {
public:
	typedef R (*Func)(Args...); // указатель на функцию

	/**
     * @brief Конструктор класса SOSH_Function.
     * 
     * @param s Имя функции.
     * @param f Указатель на функцию.
     * @param d Описание функции (по умолчанию пустая строка).
     */
    SOSH_Function(std::string s, Func f, std::string d = "") : func(f) {
        this->name = s;
        this->description = d;
    };
	
	/**
     * @brief Конструктор копирования класса SOSH_Function.
     * 
     * @param other Другой объект класса SOSH_Function.
     */
    SOSH_Function(const SOSH_Function& other) : func(other.func) {
        this->name = other.name;
        this->description = other.description;
    };
	
	/**
     * @brief Конструктор перемещения класса SOSH_Function.
     * 
     * @param other Другой объект класса SOSH_Function.
     */
    SOSH_Function(SOSH_Function&& other) noexcept : func(std::move(other.func)) { 
        this->name = std::move(other.name);
        this->description = std::move(other.description);
    };

    /**
     * @brief Метод, который устанавливает тип возвращаемого значения для функции.
     * 
     * @param type Тип возвращаемого значения.
     */
    void AddReturn(Token_t type){
        this->type_return = type;
    };

    /**
     * @brief Метод, который добавляет тип ожидаемого аргумента для функции.
     * 
     * @param type Тип ожидаемого аргумента.
     */
    void AddArgs(Token_t type){
        this->type_args.push_back(type);
    };

    /**
     * @brief Метод, который вызывает функцию с передачей ей аргументов переменной длины.
     * 
     * @tparam Args2 Типы аргументов функции.
     * @param args Аргументы функции.
     * @return R Результат выполнения функции.
     */
    template<class... Args2>
    R apply(Args2&&... args){
        return func(std::forward<Args2>(args)...);
    };

    /**
     * @brief Метод, который вызывает функцию с передачей ей кортежа аргументов.
     * 
     * @param args_tuple Кортеж аргументов функции.
     * @return R Результат выполнения функции.
     */
    R apply(std::tuple<Args...> args_tuple){
        return std::apply(func, std::move(args_tuple));
    };

    /**
     * @brief Метод, который используется для конвертирования кортежей аргументов и возвращаемого значения и вызова функции.
     * 
     * @param count Количество аргументов.
     * @param ... Указатель на список аргументов переменной длины.
     * @return SOSH_Token Результат выполнения функции в виде токена.
     */
    SOSH_Token applyWrapper(int count, ...) override {   
        va_list ptr;
        va_start(ptr, count);
        auto args_tuple = va_arg(ptr, ArgsToToken);
        va_end(ptr);

        std::tuple<Args...> true_tuple = std::apply([](auto&... args){ 
            return std::make_tuple(std::forward<Args>(args.template GetValue<Args>())...); 
        }, args_tuple);

        if constexpr (std::is_void_v<R>) {
            apply(true_tuple);
            SOSH_Token res_token(Token_t::SOSH_VOID, "");
            return res_token;
        } else {
            auto res = apply(true_tuple);
            std::stringstream ss;
            ss << res;
            std::string str_variable = ss.str();
            SOSH_Token res_token(this->type_return, str_variable);
            return res_token;
        };
    };

private:
    Func func; // указатель на функцию
    using ArgsToToken = std::tuple<ToType<Args>...>; // список типов аргументов 
};

/**
 * @brief Функция для смены местами элементов кортежа.
 * 
 * @tparam Ts Типы элементов кортежа.
 * @tparam Is Последовательность индексов элементов кортежа.
 * @param tpl Исходный кортеж.
 * @param std::index_sequence<Is...> Последовательность индексов элементов кортежа.
 * @return auto Новый кортеж с элементами, поменянными местами.
 */
template <typename... Ts, std::size_t... Is>
auto tuple_reverse_helper(const std::tuple<Ts...>& tpl, std::index_sequence<Is...>) {
    return std::make_tuple(std::get<sizeof...(Ts) - Is - 1>(tpl)...);
};

/**
 * @brief Функция для смены местами элементов кортежа.
 * 
 * @tparam Ts Типы элементов кортежа.
 * @param tpl Исходный кортеж.
 * @return auto Новый кортеж с элементами, поменянными местами.
 */
template <typename... Ts>
auto tuple_reverse(const std::tuple<Ts...>& tpl) {
    return tuple_reverse_helper(tpl, std::make_index_sequence<sizeof...(Ts)>{});
};

/**
 * @brief Функция для конвертирования одного кортежа в другой с сохранением указанных типов данных.
 * 
 * @tparam Ts Типы элементов исходного кортежа.
 * @tparam Us Типы элементов целевого кортежа.
 * @param tpl Исходный кортеж.
 * @param tpl_template Целевой кортеж с указанными типами данных.
 * @return auto Новый кортеж с элементами, сконвертированными в указанные типы данных.
 */
template <typename... Ts, typename... Us>
auto tuple_convert(const std::tuple<Ts...>& tpl, const std::tuple<Us...>& tpl_template) {
    static_assert(sizeof...(Ts) == sizeof...(Us), "Tuple sizes must match");
    return std::apply([](auto&&... args) {
        return std::make_tuple(static_cast<std::conditional_t<std::is_same_v<Ts, Us>, Ts, Us>>(args)...);
    }, tpl);
};

#endif //SOSH_FUNCTION_H
