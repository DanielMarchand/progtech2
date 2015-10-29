// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.10.2015 10:58:26 CEST
// File:    05_forward.cpp

#include <memory>
#include <vector>
#include <iostream>

#include "base_der.hpp"

struct myint {
    myint(int const & a): x(std::make_unique<int>(a)) {
        std::cout << "ctor" << std::endl;
    }
    myint(myint const & rhs): x(std::make_unique<int>(*rhs.x)) {
        std::cout << "copy-ctor" << std::endl;
    }
    myint(myint && rhs): x(std::move(rhs.x)) { // shared_ptr is move-ctorable
        std::cout << "move-ctor" << std::endl;
    }
    
    std::unique_ptr<int> x;
};

namespace challenge {
    //=================== is lvalue_ref ===================
    template<typename T>
    struct is_lvalue_reference {
        static bool const value = false;
    };
    template<typename T>
    struct is_lvalue_reference<T&> {
        static bool const value = true;
    };
    
    //=================== remove reference ===================
    template<typename T>
    struct remove_referece {
        using type = T;
    };
    template<typename T>
    struct remove_referece<T &> {
        using type = T;
    };
    template<typename T>
    struct remove_referece<T &&> {
        using type = T;
    };
    
    template<typename T>
    using remove_reference_t = typename remove_referece<T>::type;
    
    //=================== forward ===================
    template<typename T>
    constexpr T && forward(remove_reference_t<T> & t) noexcept {
        return static_cast<T &&>(t);
    }

    template<typename T>
    constexpr T && forward(remove_reference_t<T> && t) noexcept {
        // we could create a nice compiletime error with this line
        static_assert(!is_lvalue_reference<T>::value, 
            "template argument substituting T is an lvalue reference type");
        return static_cast<T &&>(t);
    }
}//end namespace challenge

class database {
public:
    database() {
        data_.reserve(10); // we dont want to see the resize operations
    }
    template<typename T>
    void add(T && t) {
        data_.push_back(challenge::forward<T>(t));
    }
private:
    std::vector<myint> data_;
};

int main() {
    myint a(10);           // prints "ctor"
    myint b(a);            // prints "copy-ctor"
    myint c(std::move(b)); // prints "move-ctor"
    
    std::cout << "database" << std::endl;
    
    database db;
    
    std::cout << "A" << std::endl;
    // should print "copy-ctor"
    db.add(a);
    
    std::cout << "B" << std::endl;
    // should print "move-ctor"
    db.add(std::move(c)); 
    
    std::cout << "C" << std::endl;
    // should print "ctor" and "move-ctor"
    constexpr int d = challenge::forward<int>(20);
    db.add(challenge::forward<myint>(myint(d)));
    // forward is redundant here, but a necessary
    // hint for you to implmement forward correctly
    
    #include "diehard.hpp"
    
    
    return 0;
}

