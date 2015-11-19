/*******************************************************************************
 * 
 * Bot Concept Wrapper
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#ifndef BOT_CONCEPT_WRAPPER_HEADER
#define BOT_CONCEPT_WRAPPER_HEADER

#include <memory>
#include <random>

#include "global.hpp"

//=================== concept ===================
struct bot_wrap_base {
    virtual dir::type move(int const & size
                         , std::array<field_type, dir::N> const & read
                         , field_type const & self
                         , std::mt19937 & eng) = 0;
    virtual std::string name() const = 0;
};

template<typename T>
struct bot_wrap_der: public bot_wrap_base {
    bot_wrap_der(T const & t): b(t) {}
    dir::type move(int const & size
                 , std::array<field_type, dir::N> const & read
                 , field_type const & self
                 , std::mt19937 & eng) override {
        return b.move(size, read, self, eng);
    }
    std::string name() const override {
        return b.name();
    }
    
    T b;
};

struct bot_wrap {
    bot_wrap(): ptr() {}
    template<typename T>
    bot_wrap(T const & t): ptr(new bot_wrap_der<T>(t)) {}
    dir::type move(int const & size
                 , std::array<field_type, dir::N> const & read
                 , field_type const & self
                 , std::mt19937 & eng) {
        return ptr->move(size, read, self, eng);
    }
    std::string name() const {
        return ptr->name();
    }
    
    std::shared_ptr<bot_wrap_base> ptr;
};

#endif //BOT_CONCEPT_WRAPPER_HEADER
