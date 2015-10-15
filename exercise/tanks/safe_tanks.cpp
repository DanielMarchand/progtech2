/*******************************************************************************
 * 
 * Tank Battle Simulation
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <list>
#include <memory>    // for the smart-ptr
#include <random>
#include <iostream>
#include <algorithm> // for find

class Tank {
    public:
    Tank(const int & nr) : nr(nr), target() {
        //~ double * p = new double[1000000];  // heavy object to demonstrate mem-leak
        //~ std::cout << &p;
        //~ delete[] p;
    }
    ~Tank() {
        std::cout << "Tank " << nr << " was destroyed." << std::endl;
    }
    void shoot(std::list<std::shared_ptr<Tank>> & battlefield) {
        if(not target.expired()) {
            auto t = target.lock();
            std::cout << " " << nr << " -> " << t->nr << " fire!" << std::endl;
            t->HP-=DPS;
            if(t->HP <= 0) {
                auto pos = std::find(battlefield.begin(), battlefield.end(), t);
                battlefield.erase(pos); // delete the pointer
            }
        } else {
            std::cout << " target already destroyed" << std::endl;
        }
    }

    int nr;
    //~ int DPS = 333; // used to show mem-leak
    int DPS = 500;
    int HP = 1000;
    std::weak_ptr<Tank> target;
};

int main() {

    uint32_t init_count = 5;
    std::list<std::shared_ptr<Tank>> battlefield;

    for(uint32_t i = 0; i < init_count; ++i) {
        battlefield.push_back(std::make_shared<Tank>(i)); // vs std::shared_ptr<Tank>(new Tank) in func(<-, new Other)
    }

    std::default_random_engine engine(0);

    int round = 0;
    while( battlefield.size() > 1) {
        // add one new tanks
        battlefield.push_back(std::make_shared<Tank>(round+init_count));
        
        std::cout << "--- Round " << round++ << " (" << battlefield.size() << " tanks) ---" << std::endl;
        
        // aiming process
        std::uniform_int_distribution<int> distr(1, battlefield.size()-1);  // don't select self
        for(auto it = battlefield.begin(); it != battlefield.end(); ++it) {
            std::cout << (*it)->nr << " aiming." << std::endl;
            
            auto self_pos = std::distance(battlefield.begin(), it);
            auto target_pos = (self_pos + distr(engine)) % battlefield.size();
            
            auto target = battlefield.begin();
            std::advance(target, target_pos);
            (*it)->target = *target;
        }

        // shooting process
        for(auto & tank: battlefield) {
            std::cout << tank->nr << " ready." << std::endl;
            tank->shoot(battlefield);
        }
    }
    std::cout << "_______________________________________________" << std::endl
              << "Peace in our time." << std::endl;

    return 0;
}

