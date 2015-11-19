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
#include "all_bots.hpp"
#include "print_helper.hpp"

int main() {
    
    // used to seed the actual rng
    std::mt19937 rng_seed(time(NULL));
    //~ std::mt19937 rng_seed(0);
    
    // players
    std::vector<bot_wrap> bot_pool = get_player();
    
    // solution
    score_type score;
    
    // verbose level:
    // 0 = only show statistics (recomended in this code)
    // 1 = show statistics after each game (fast)
    // 2 = show step by step game moves
    int v = 0;
    
    // the first two chars of the botname specify the team
    // if friend_battle is true, bots from same team battle against each other
    bool friend_battle = true;
    
    // specify if a bot fights also against a copy of itself
    // if friend_battle is false, this variable does not matter
    bool self_battle = false;
    
    // amount of games per size and 1vs1 encounter
    int games = 200;
    
    for(uint32_t i = 0; i < bot_pool.size(); ++i) {
        std::cout << i+1 << "/" << bot_pool.size() << std::endl;
        for(uint32_t j = i; j < bot_pool.size(); ++j) {
            std::string pi = bot_pool[i].name();
            std::string pj = bot_pool[j].name();
            if(not self_battle and i==j) {
                score[pi][pj] = 0;
                continue;
            }
            if(not friend_battle and same_team(pi, pj)) {
                score[pi][pj] = 0;
                score[pj][pi] = 0;
                continue;
            }
            
            std::cout << "(   /   ): " << pi << " vs " << pj << std::endl;
            
            // put the two bots in a vector
            std::vector<bot_wrap> bots;
            bots.push_back(bot_pool[i]);
            bots.push_back(bot_pool[j]);
            
            board b(bots, v);
    
            // we will test your thunder_struct on different board sizes (up to 100)
            std::cout << "size: ";
            for(uint size = 10; size < 81; size+= 10) {
                std::cout << size << " ";
                std::cout.flush();
                
                // if no player lost after max_turns ==> draw
                int max_turns = size*size + 20*size;
    
                for(int g = 0; g < games; ++g) {
                    // engine used in this game
                    std::mt19937 eng(rng_seed());
                    
                    b.setup(size, max_turns, eng);
                    
                    while(not b.winner())
                        b.turn(eng);
                    
                    b.sort_alphabetical();
                    b.print_report();
                }
            }
            std::cout << std::endl << renter; // jump one line up
            
            auto res = b.get_score();
            
            if(i == j) {
                // if we fought our own copy, average the scores
                score[res[0].first][res[1].first] = (res[0].second + res[1].second) / 2;
            } else {
                score[res[0].first][res[1].first] = res[0].second;
                score[res[1].first][res[0].first] = res[1].second;
            }
            
            int i_score = score[pi][pj];
            int j_score = score[pj][pi];
            std::string i_col = col(pi, pj, score);
            std::string j_col = col(pj, pi, score);
            
            // print results of encounter
            std::cout << renter << "(" << i_col << i_score << ncol << "/" 
                      << j_col << j_score << ncol << "): "
                      << i_col << pi << ncol << " vs " << j_col <<  pj
                      << ncol << std::endl;
        }
    }
    
    //=================== print matrix & collect data ===================
    std::vector<std::pair<std::string, int>> win;
    
    size_t name_crop = (79 / (bot_pool.size()+1)) - 1;  // terminal width 80
    size_t name_len = 32;
    
    std::cout << games << " games each on size 10-100 arena:" << std::endl;
    
    //------------------- print first row with enemy-names -------------------
    print_seperator(score.size(), name_crop);
    std::cout << "|" << std::setw(name_crop+1) << "vs=>|";
    for(auto const & row: score)
        std::cout << std::setw(name_crop) << shorten(row.first, name_crop) << "|";
    std::cout << std::endl;
    
    //------------------- print for each bot a row & sum score -------------------
    for(auto const & row: score) {
        // collect score
        int collect = 0;
        int count = 0;
        for(auto const & p: row.second) {
            collect += p.second;
            count += (p.second != 0);
        }
        win.push_back(std::make_pair(row.first, collect / count));
        
        // print row
        print_seperator(score.size(), name_crop);
        std::cout << "|" << std::setw(name_crop) << shorten(row.first, name_crop) << "|";
        for(auto const & p: row.second)
            std::cout << col(row.first, p.first, score) << std::setw(name_crop) << p.second << ncol << "|";
        std::cout << std::endl;
    }
    print_seperator(score.size(), name_crop);
    
    //=================== print winner order ===================
    sort(win.begin(), win.end(), [](auto const & a, auto const & b){ return a.second > b.second; });
    std::cout << std::endl << "Position:" << std::endl;
    for(uint32_t i = 0; i < win.size(); ++i) {
        std::cout << std::setw(2) << i+1 << std::setw(name_len + 1) << shorten(win[i].first, name_len) 
                  << std::setw(5) << win[i].second << std::endl;
    }
    
    return 0;
}
