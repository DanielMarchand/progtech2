// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    21.10.2015 10:58:26 CEST
// File:    05_forward.cpp

#include <memory>
#include <vector>
#include <iostream>

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

// modifications only allowed within namespace challenge
namespace challenge {
    using std::forward; // remove this line, implement it yourself!
    // don't use anything from another namespace here (especially std::)

}//end namespace challenge

class database {
public:
    database() {
        data_.reserve(10);
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
    db.add(a); // should print "copy-ctor"
    
    std::cout << "B" << std::endl;
    db.add(std::move(c)); // should print "move-ctor"
    
    std::cout << "C" << std::endl;
    constexpr int d = challenge::forward<int>(20);
    db.add(challenge::forward<myint>(myint(d))); // should print "ctor" and "move-ctor"
    // forward is redundant here, but a necessary
    // hint for you to implement forward correctly
    
    return 0;
}

