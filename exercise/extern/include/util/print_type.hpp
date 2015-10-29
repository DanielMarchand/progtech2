/*******************************************************************************
 *
 * Prints Type and as well as ref-ness / const-ness / volatile-ness
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <typeinfo>
#include <cxxabi.h>
#include <type_traits>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>

inline std::string demangle(std::string const & str) {
    int status;
    std::unique_ptr<char, void(*)(void*)>
      dmgl(abi::__cxa_demangle(str.c_str(), 0, 0, &status), std::free);
    return (status==0) ? dmgl.get() : str;
}

template<typename T>
struct type {
    static std::string print() {
        std::stringstream ss;
        ss << demangle(typeid(T).name());
        ss << std::endl;
        return ss.str();
    }
};

#define SPECIALISATION_PRINT_TYPE(cvr)              \
template<typename T>                                \
struct type<T cvr> {                                \
    static std::string print() {                    \
        std::stringstream ss;                       \
        ss << demangle(typeid(T).name());           \
        ss << " " << #cvr << std::endl;             \
        return ss.str();                            \
    }                                               \
};                                                  //

// by-value
SPECIALISATION_PRINT_TYPE(const)
SPECIALISATION_PRINT_TYPE(volatile)
SPECIALISATION_PRINT_TYPE(const volatile)

// lvalue ref
SPECIALISATION_PRINT_TYPE(&)
SPECIALISATION_PRINT_TYPE(const &)
SPECIALISATION_PRINT_TYPE(volatile &)
SPECIALISATION_PRINT_TYPE(const volatile &)

// rvalue ref
SPECIALISATION_PRINT_TYPE(&&)
SPECIALISATION_PRINT_TYPE(const &&)
SPECIALISATION_PRINT_TYPE(volatile &&)
SPECIALISATION_PRINT_TYPE(const volatile &&)

#undef SPECIALISATION_PRINT_TYPE

template<typename T>
struct valueness_impl {
    static std::string print() {
        return "r-value";
    }
};
template<typename T>
struct valueness_impl<T&> {
    static std::string print() {
        return "l-value";
    }
};

template<typename T>
std::string valueness(T &&) {
    return valueness_impl<T>::print();
}

const static std::map<const std::string, const std::string> col = {
    {"black", "\033[0m"}, {"red", "\033[1;31m"},
    {"green", "\033[0;32m"}, {"yellow", "\033[0;33m" }
};

#define PRINT_TYPE_IMPL(T, name)                                               \
std::cout << "the type " << col.at("red") << name                              \
          << col.at("black") << " is " << col.at("yellow")                     \
          << type<T>::print() << col.at("black");                             //

#define PRINT_TYPE_OF(expr)                                                    \
std::cout << "the expression " << col.at("red") << #expr                       \
          << col.at("black") << " is an " << col.at("yellow") << valueness(expr)\
          << col.at("black") << " with type "<< col.at("green")                \
          << type<decltype(expr)>::print() << col.at("black");                //

template<typename T, typename... Args>
struct type_recursion {
    static void print(std::string const & name, int const & nr = 0) {
        std::stringstream ss;
        ss << name << "[" << nr << "]";
        PRINT_TYPE_IMPL(T, ss.str())
        type_recursion<Args...>::print(name, nr + 1);
    }
};
template<typename T>
struct type_recursion<T> {
    static void print(std::string const & name, int const & nr = 0) {
        if(nr) {
            std::stringstream ss;
            ss << name << "[" << nr << "]";
            PRINT_TYPE_IMPL(T, ss.str())
        } else
            PRINT_TYPE_IMPL(T, name)
    }
};

#define PRINT_TYPE(ArgsPack)\
type_recursion<ArgsPack>::print(#ArgsPack);


