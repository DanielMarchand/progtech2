/*******************************************************************************
 * 
 * Thunder-Struct Arena
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>
#include "board.hpp"
#include "thunder_struct.hpp"

int main() {
    
    // used to seed the actual rng
    std::mt19937 rng_seed(time(NULL));
    
    // players
    std::vector<bot_wrap> bots;
    
    // two players
    bots.push_back(dumb_bot());
    bots.push_back(random_bot());
    
    // verbose level:
    // 0 = only show statistics
    // 1 = show statistics after each game (fast)
    // 2 = show step by step game moves
    int v = 2;
    
    int games = 10000;
    // we will test your thunder_struct on different board sizes (up to 100)
    int size = 8;
    // if no player lost after max_turns ==> draw
    int max_turns = 1000;
    
    board b(bots, v);
    
    for(int i = 0; i < games; ++i) {
        // engine used in this game
        std::mt19937 eng(rng_seed());
        
        b.setup(size, max_turns);
        
        while(not b.winner())
            b.turn(eng);
        
        b.print_report(i+1);
    }
    
    std::cout << "arena-size " << size << std::endl;
    b.print_score();

    return 0;
}
