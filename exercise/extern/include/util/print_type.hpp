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

inline std::string demangle(std::string const & str) {
    int status;
    char * demangled = abi::__cxa_demangle(str.c_str(), 0, 0, &status);
    std::string out = (status==0) ? std::string(demangled) : str;
    free(demangled);
    return out;
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

#define PRINT_TYPE_IMPL(T, name)            \
std::cout << "the type \033[1;31m" << name  \
          << "\033[0m is \033[1;32m"        \
          << type<T>::print() << "\033[0m"; //

#define PRINT_TYPE_OF(expr)                                                                  \
std::cout << "the expression \033[1;31m" << #expr                                            \
          << "\033[0m is an \033[1;33m" << valueness(expr) << "\033[0m with type \033[1;32m" \
          << type<decltype(expr)>::print() << "\033[0m";                                     //

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


