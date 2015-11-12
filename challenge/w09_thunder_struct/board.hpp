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
#include <algorithm>

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
struct bot_data {
    bot_wrap bot;
    field_struct * pos;
    bool alive;
    double win;
    double draw;
    std::string color;
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
        , int const & v): data_()
                        , b_()
                        , verbose_(v) {
        
        std::vector<std::string> color;
        color.push_back("\033[0;31m");
        color.push_back("\033[0;32m");
        color.push_back("\033[0;35m");
        color.push_back("\033[0;34m");
        color.push_back("\033[0;36m");
        
        for(uint32_t i = 0; i < bot.size(); ++i) {
            bot_data r;
            r.bot = bot_wrap(bot[i]);
            r.pos = nullptr;
            r.alive = true;
            r.win = 0;
            r.draw = 0;
            r.color = color[i%color.size()];
            data_.push_back(r);
        }
        total_games_ = 0; // total
    }
    
    void setup(int const & size, int const & maxiter, std::mt19937 & eng) {
        iter_ = 0;
        cturn_ = data_.size() - 1;
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
                b_[i][j].val.player = no_player;
            }
        }
        
        // set bots in equal distance on the diagonal (may be changed...)
        double M = data_.size();
        
        sort_alphabetical();
        shuffle(data_.begin(), data_.end(), eng);
        
        for(uint32_t i = 0; i < data_.size(); ++i) {
            auto pos = int(i * N / M);
            data_[i].pos = &get(pos, eng() % N);
            data_[i].pos->val.player = i;
            data_[i].alive = true;
        }
    }
    // modifying methods
    void sort_alphabetical() {
        sort(data_.begin()
           , data_.end()
           , [](auto const & a, auto const & b){ return a.bot.name() < b.bot.name(); });
    }
    field_struct & get(int const & i, int const & j) {
        return b_[i][j];
    }
    void turn(std::mt19937 & eng) {
        cturn_ = (cturn_+1)%data_.size();
        
        if(cturn_ == 0)
            iter_ += 1;
        
        if(not data_[cturn_].alive)
            return;
        
        auto nbr = data_[cturn_].pos->nbr();
        auto self = data_[cturn_].pos->val;
        
        
        auto dir = data_[cturn_].bot.move(N, nbr, self, eng);
        data_[cturn_].pos = data_[cturn_].pos->ptr[dir];
        data_[cturn_].pos->val.cnt = iter_;
        data_[cturn_].pos->val.player = cturn_;
        
        // check if it beat another
        for(int i = 0; i < int(data_.size()); ++i) { // dont do that
            if(i != cturn_ and data_[i].alive) {
                if(data_[i].pos  == data_[cturn_].pos)
                    data_[i].alive = false;
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
            for(uint32_t i = 0; i < data_.size(); ++i) {
                data_[i].draw += data_[i].alive; // for those that survived
            }
            ++total_games_;
            return true;
        }
        
        int alive = 0;
        
        for(uint32_t i = 0; i < data_.size(); ++i)
            alive += data_[i].alive;
        
        if(alive == 1) {
            ++data_[cturn_].win;
            ++total_games_;
            return true;
        }
        
        return false;
    }
    
    //=================== print functions ===================
    std::string print_name(bot_data const & bd) const {
        return bd.color + bd.bot.name() + "\033[0m";
    }
    void print_report(int const & games) const {
        if(verbose_ == 0)
            return;
        
        std::cout << "Games played: " << games << std::endl;
        for(uint32_t i = 0; i < data_.size(); ++i) {
            std::cout << std::setw(10) << print_name(data_[i])
                      << ": " << 100 * data_[i].win / double(total_games_) << "% (draw: " 
                      << 100 * data_[i].draw / double(total_games_) << "%)"<< std::endl;
            
        }
        usleep(80);
        if(verbose_ >= 2)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        else
            std::cout << "\033[2J\033[100A";
    }
    void print_score() const {
        for(uint32_t i = 0; i < data_.size(); ++i)
            std::cout << "Score for " << print_name(data_[i]) << " = " << score(data_[i].win, data_[i].draw, total_games_) << " / 1000" << std::endl;
    
    }
    void print_board() const {
        
        auto col = [&](field_type const & val){
            std::string res = "";
            if(val.player == no_player)
                res = "\033[0m";
            else
                res = data_[val.player].color;
            if(val.player != no_player and val.cnt == (iter_-(cturn_<val.player)))
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
    int total_games_;
    
    std::vector<bot_data> data_;
    std::vector<std::vector<field_struct>> b_;
    
    int iter_;
    int maxiter_;
    int cturn_;
    
    int verbose_;
};


#endif //BOARD_HEADER
