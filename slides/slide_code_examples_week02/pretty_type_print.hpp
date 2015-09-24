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

inline std::string demangle(std::string const & str) {
    int status;
    char * demangled = abi::__cxa_demangle(str.c_str(), 0, 0, &status);
    std::string out = (status==0) ? std::string(demangled) : str;
    free(demangled);
    return out;
}

template<typename T>
struct type {
    static void pretty_print() {
        std::cout << demangle(typeid(T).name());
        std::cout << std::endl;
    }
};

#define SPECIALISATION_PRINT_TYPE(cvr)              \
template<typename T>                                \
struct type<T cvr> {                                \
    static void pretty_print() {                    \
        std::cout << demangle(typeid(T).name());    \
        std::cout << " " << #cvr << std::endl;      \
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

#define PRINT_TYPE(expr) std::cout << #expr << "\t=> "; type<expr>::pretty_print();
#define PRINT_TYPE_OF(expr) std::cout << #expr << "\t=> "; type<decltype(expr)>::pretty_print();

