/*******************************************************************************
 * 
 * Thunder-Struct Arena
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#include <iostream>
#include </home/msk/Programmieren/eth/frescolino/fsc/DebugPrinter.hpp>
#include "board.hpp"
#include "thunder_struct.hpp"
#include "mkoenz.hpp"
#include "all_bots.hpp"

int main() {
    
    // used to seed the actual rng
    //~ std::mt19937 rng_seed(time(NULL));
    std::mt19937 rng_seed(0);
    
    // players
    std::vector<bot_wrap> bots;
    
    // defaults
    //~ bots.push_back(random_bot());
    //~ bots.push_back(dumb_bot());

    
    bots.push_back(tri_bot());  //flofrei
    bots.push_back(quad_bot()); //flofrei
    
    bots.push_back(godzilla_bot()); //fraschs
    
    bots.push_back(ultimate_camper());  //greschd
    bots.push_back(wandering_camper()); //greschd
    
    bots.push_back(krummenf_shy());    //krummenf
    bots.push_back(krummenf_hunter()); //krummenf
    
    bots.push_back(annihilator_bot());     //untergam
    bots.push_back(metaannihilator_bot()); //untergam
    

    //~ bots.push_back(dodge_tracker_bot()); //mkoenz
    //~ bots.push_back(spider_bot());        //mkoenz
    
    // verbose level:
    // 0 = only show statistics
    // 1 = show statistics after each game (fast)
    // 2 = show step by step game moves
    int v = 1;
    
    // amount of games played
    int games = 1000;
    
    // we will test your thunder_struct on different board sizes (up to 100)
    int size = 80;
    
    // if no player lost after max_turns ==> draw
    int max_turns = size*size + 20*size;
    
    board b(bots, v);
    
    for(int i = 0; i < games; ++i) {
        //~ if(i == 67)
            //~ b.set_verbose(2);
        // engine used in this game
        std::mt19937 eng(rng_seed());
        
        b.setup(size, max_turns, eng);
        
        while(not b.winner())
            b.turn(eng);
        
        b.sort_score();
        b.print_report();
    }
    
    b.sort_score();
    b.print_score();
    
    b.sort_kills();
    b.print_kills();

    return 0;
}
