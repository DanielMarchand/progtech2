/*******************************************************************************
 *
 * Prints Type and as well as ref-ness / const-ness / volatile-ness
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#include <typeinfo>
#include <execinfo.h>
#include <cxxabi.h>
#include <type_traits>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>

inline std::string demangle(std::string const & str, int & status) {
    std::unique_ptr<char, void(*)(void*)>
      dmgl(abi::__cxa_demangle(str.c_str(), 0, 0, &status), std::free);
    return (status==0) ? dmgl.get() : str;
}

template<typename T>
struct type {
    static std::string print() {
        std::stringstream ss;
        int status;
        ss << demangle(typeid(T).name(), status);
        ss << std::endl;
        return ss.str();
    }
};

#define SPECIALISATION_PRINT_TYPE(cvr)                                         \
template<typename T>                                                           \
struct type<T cvr> {                                                           \
    static std::string print() {                                               \
        std::stringstream ss;                                                  \
        int status;                                                            \
        ss << demangle(typeid(T).name(), status);                              \
        ss << " " << #cvr << std::endl;                                        \
        return ss.str();                                                       \
    }                                                                          \
};                                                                            //

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

namespace detail {
    #ifdef __APPLE__
    inline std::string mangled_part(const std::string str) {
        std::stringstream ss(str);
        std::string res;
        ss >> res; ss >> res; ss >> res; ss >> res;
        return res;
    }

    #else
    inline std::string mangled_part(const std::string str) {
        std::string::size_type pos = str.find("(") + 1;
        if(str.find("+", pos) == std::string::npos) return "";
        return str.substr(pos, str.find("+", pos) - pos);
    }
    #endif
}

std::string fct_sig() {

    void * stack[2];
    uint r = backtrace(stack, 2);
    char ** symbols = backtrace_symbols(stack, r);
    if(!symbols) return "Error: No symbols";

    std::string mangled = detail::mangled_part(std::string(symbols[1]));
    free(symbols);
    if(mangled == "")
        std::cerr << "Error: No dynamic symbol (you probably didn't compile with -rdynamic)"
                  << std::endl;

    int status = 0;
    std::string demangled = demangle(mangled, status);
    switch (status) {
      case -1:
        std::cerr << " Error: Could not allocate memory!" << std::endl;
        break;
      case -3:
        std::cerr << " Error: Invalid argument to demangle()" << std::endl;
        break;
      case -2:  // invalid name under the C++ ABI mangling rules
        demangled = mangled;
        // fallthrough
      default:
        return demangled;
    }

    return "";
}

