/*******************************************************************************
 * 
 * Thunder-Struct Board
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 * 
 ******************************************************************************/

#ifndef BOARD_HEADER
#define BOARD_HEADER

#include <map>
#include <ctime>

#include <random>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "bot_concept_wrapper.hpp"


//=================== a single field ===================
struct field_struct {
    field_struct() {}
    
    std::array<field_type, dir::N> nbr() const {
        std::array<field_type, dir::N> res;
        for(int dir = 0; dir < dir::N; ++dir)
            res[dir] = ptr[dir]->val;
        return res;
    }
    
    field_type val;
    std::array<field_struct *, dir::N> ptr;
    
};

//=================== board-logic ===================
int score(double const & win, double const & tie, double const & total) {
    return (3 * win + tie) / (3 * total) * 1000;
}
//------------------- board -------------------
class board {
public:
    // structors
    
    board(std::vector<bot_wrap> const & bot
        , int const & v): bot_(bot)
                        , bot_pos_(bot_.size(), nullptr)
                        , alive_(bot_.size(), true)
                        , b_()
                        , verbose_(v) {
        for(uint32_t i = 0; i < bot_.size(); ++i) {
            ratio_[i] = 0;  // for wins
            ratio_[-i-1] = 0; // for draws
        }
        total_games_ = 0; // total
    }
    
    void setup(int const & size, int const & maxiter) {
        iter_ = 0;
        cturn_ = bot_.size() - 1;
        N = size;
        b_.resize(N, std::vector<field_struct>(N));
        maxiter_ = maxiter;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                b_[i][j].ptr[dir::left] = &b_[i][(j-1+N)%N];
                b_[i][j].ptr[dir::right]= &b_[i][(j+1)%N];
                
                if(i%2==0) {
                    b_[i][j].ptr[dir::up_right]    = &b_[(i-1+N)%N][j];
                    b_[i][j].ptr[dir::up_left]     = &b_[(i-1+N)%N][(j-1+N)%N];
                    b_[i][j].ptr[dir::down_right]  = &b_[(i+1)%N][j];
                    b_[i][j].ptr[dir::down_left]   = &b_[(i+1)%N][(j-1+N)%N];
                } else {
                    b_[i][j].ptr[dir::up_right]    = &b_[(i-1+N)%N][(j+1)%N];
                    b_[i][j].ptr[dir::up_left]     = &b_[(i-1+N)%N][j];
                    b_[i][j].ptr[dir::down_right]  = &b_[(i+1)%N][(j+1)%N];
                    b_[i][j].ptr[dir::down_left]   = &b_[(i+1)%N][j];
                }
                b_[i][j].val.cnt = 0;
                b_[i][j].val.player = -1;
            }
        }
        
        // set bots in equal distance on the diagonal (may be changed...)
        double M = bot_.size();
        
        for(uint32_t i = 0; i < bot_.size(); ++i) {
            auto pos = int(i * N / M);
            bot_pos_[i] = &get(pos, pos);
            alive_[i] = true;
        }
    }
    // modifying methods
    field_struct & get(int const & i, int const & j) {
        return b_[i][j];
    }
    void turn(std::mt19937 & eng) {
        cturn_ = (cturn_+1)%bot_.size();
        
        if(cturn_ == 0)
            iter_ += 1;
        
        if(not alive_[cturn_])
            return;
        
        auto nbr = bot_pos_[cturn_]->nbr();
        auto self = bot_pos_[cturn_]->val;
        
        
        auto dir = bot_[cturn_].move(N, nbr, self, eng);
        bot_pos_[cturn_] = bot_pos_[cturn_]->ptr[dir];
        bot_pos_[cturn_]->val.cnt = iter_;
        bot_pos_[cturn_]->val.player = cturn_;
        
        // check if it beat another
        for(int i = 0; i < int(bot_.size()); ++i) { // dont do that
            if(i != cturn_ and alive_[i]) {
                if(bot_pos_[i] == bot_pos_[cturn_])
                    alive_[i] = false;
            }
        }
        
        if(verbose_ >= 2) {
            std::cout << "\033[2J\033[100A" << std::endl;
            print_board();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    // const methods
    int winner() {
        // draw
        if(iter_ == maxiter_) {
            for(uint32_t i = 0; i < bot_.size(); ++i) {
                ratio_[-i-1] += alive_[i]; // for those that survived
            }
            ++total_games_;
            return true;
        }
        
        int alive = 0;
        
        for(uint32_t i = 0; i < bot_.size(); ++i)
            alive += alive_[i];
        
        if(alive == 1) {
            ++ratio_[cturn_];
            ++total_games_;
            return true;
        }
        
        return false;
    }
    void print_report(int const & games) const {
        if(verbose_ == 0)
            return;
        
        std::cout << "Games played: " << games << std::endl;
        for(uint32_t i = 0; i < bot_.size(); ++i) {
            std::cout << std::setw(10) << bot_[i].name() 
                      << ": " << 100 * ratio_.at(i) / double(total_games_) << "% (draw: " 
                      << 100 * ratio_.at(-i-1) / double(total_games_) << "%)"<< std::endl;
            
        }
        usleep(80);
        if(verbose_ >= 2)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        else
            std::cout << "\033[2J\033[100A";
    }
    void print_score() const {
        for(uint32_t i = 0; i < bot_.size(); ++i)
            std::cout << "Score for " << bot_[i].name() << " = " << score(ratio_.at(i), ratio_.at(-i-1), total_games_) << " / 1000" << std::endl;
    
    }
    void print_board() const {
        std::vector<std::string> color;
        color.push_back("\033[0;31m");
        color.push_back("\033[0;32m");
        color.push_back("\033[0;35m");
        color.push_back("\033[0;34m");
        color.push_back("\033[0;36m");

        auto col = [&](field_type const & val){
            std::string res = "";
            if(val.player == -1)
                res = "\033[0m";
            else
                res = color[val.player % color.size()];
            
            if(val.cnt == iter_)
                res += "\033[103m";
            if(val.cnt != 0 and val.cnt == iter_-(cturn_<val.player))
                res += "\033[103m";
            
            return res;
        };
        std::string v;
        for(int i = 0; i < N; ++i) {
            if(i%2 == 1)
                std::cout << "  ";
            for(int j = 0; j < N; ++j) {
                auto const & val = b_[i][j].val;
                v = std::to_string(abs(val.cnt));
                std::cout << std::string(4-v.size(), ' ') << col(val) << v << "\033[0m";
            }
            std::cout << std::endl << std::endl;
        }
    }
private:
    int N;
    std::map<int, double> ratio_;
    int total_games_;
    
    std::vector<bot_wrap> bot_;
    std::vector<field_struct*> bot_pos_;
    std::vector<bool> alive_;
    
    std::vector<std::vector<field_struct>> b_;
    
    int iter_;
    int maxiter_;
    int cturn_;
    
    int verbose_;
};


#endif //BOARD_HEADER
