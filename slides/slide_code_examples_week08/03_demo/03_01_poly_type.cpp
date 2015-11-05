// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    04.11.2015 13:43:23 CET
// File:    03_01_poly_type.cpp

/*
 * I didn't review this code since 2011, it does many things
 * the "old" way, so don't take this as a good example code
 * it should only demonstrate what's possible
*/

//=================== includes ===================
#include "../presentation.hpp"

#include <sstream>      // for istringstream
#include <stdexcept>    // throw errors!
#include <memory>       // for the shared_ptr

//=================== the poly type ===================
//------------------- something similar to boost any -------------------
class any_base {
public:
    virtual void * get() = 0;
};
template<typename T>
class any_der: public any_base {
public:
    any_der(T const & t): t_(t) {}
    void * get() {
        return (void *)(&t_);
    }
private:
    T t_;
};

//------------------- runtime checks -------------------
template<typename T>
bool convertable_to(const std::string& str) {
    std::istringstream iss(str);
    T obj;
    iss >> std::ws >> obj >> std::ws;

    if(!iss.eof())
        return false;

    return true; 
}
template< typename T >
inline T convert(const std::string& str) {
    std::istringstream iss(str);
    T obj;

    iss >> std::ws >> obj >> std::ws;

    if(!iss.eof())
        throw std::runtime_error("not convertable!");
    
    return obj; 
}
//------------------- compiletime checks -------------------
template<typename T, typename U>
struct is_convertable {
    static char check(U const &);
    static double check(...);
    static T t;
    enum{value = (sizeof(char) == sizeof(check(t)))};
};
//------------------- poly_type -------------------
class poly_type {
    //------------------- init -------------------
    template<typename T, typename U, bool convertable>
    struct init {
        init<T, U, convertable>(T const & t, poly_type * b) {
            b->type = typeid(U).name();
            b->any = std::shared_ptr<any_base>(new any_der<U>(t));
        }
    };
    template<typename T, typename U>
    struct init<T, U, false> {
        init<T, U, false>(T const &, poly_type *) {
        }
    };
    template<typename T>
    void set(T const & t) {
        any.reset();
        
        init<T, double, is_convertable<T, double>::value>(t, this);
        init<T, std::string, is_convertable<T, std::string>::value>(t, this);
        
        if(!any) {
            std::stringstream ss;
            ss << "cannot convert type " << typeid(T).name() << " to double or std::string";
            throw std::runtime_error(ss.str());
        }
    }
public:
    //------------------- ctors -------------------
    template<typename T>
    poly_type(T const & t) {
        set(t);
    }
    //use new only in the constructor of a shared_pointer!
    //The shared_pointer will manage the lifetime of the object
    //no memory leaks / deletes needed
    poly_type(): any(new any_der<double>(0)), type(typeid(double).name()) {
    }
    poly_type(poly_type const & c): any(c.any), type(c.type) {
    }
    template<typename T>
    void operator=(T const & t) {
        set(t);
    }
    //------------------- cast-ops -------------------
    operator double() const {
        if(typeid(double).name() != type) {
            throw std::runtime_error("wrong conversion to double");
        }
        return *(double const *)(any->get());
    }
    operator std::string() const {
        if(typeid(std::string).name() != type) {
            throw std::runtime_error("wrong conversion to std::string");
        }
        
        return *(std::string const *)(any->get());
    } 
    //------------------- print -------------------
    void print(std::ostream & os = std::cout) const {
        if(type == typeid(double).name())
            os << double(*this);
        else if(type == typeid(std::string).name())
            os << std::string(*this);
        else
            os<< "chameleon is empty";
    };
private:
    std::shared_ptr<any_base> any;
    std::string type;
};
// print the poly_type
std::ostream & operator<<(std::ostream & os, poly_type const & b) {
    b.print(os);
    return os;
}

//=================== main ===================
int main() {
    
    // create poly_types
    poly_type x;
    poly_type y;
    
    x = 3.14;
    y = "some_text";
    
    PNW_RED(y)
    PN_BLUE(x)
    
    // assign to numbers
    double number = x;
    std::string string(y);
    
    PNW_YELLOW(number)
    PN_YELLOW(string)
    
    // change poly_type
    x = "changed_to_string";
    y = 42;
    
    PNW_BLUE(y)
    PN_RED(x)
    
    // poly_type throws an exception if it cannot be converted
    //~ CNWW_RED(number = x)
    
    return 0;
}
