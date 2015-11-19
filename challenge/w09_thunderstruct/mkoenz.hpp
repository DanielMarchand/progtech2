// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2015 11:58:24 CET
// File:    mkoenz.hpp

#ifndef MKOENZ_HEADER
#define MKOENZ_HEADER

#include <array>
#include <random>
#include <stdexcept>

#include "global.hpp"

//=================== common functionalities ===================
struct common_bot {
    bool enemy_found(std::array<field_type, dir::N> const & read
                   , field_type const & self) {
        return trace_found(read, self, 0);
    }
    bool trace_found(std::array<field_type, dir::N> const & read
                   , field_type const & self
                   , int const & age = -1) {
        // -1 means that it returns as soon as a trace is found
        if(age == -1) {
            for(uint i = 0; i < dir::N; ++i)
                if(read[i].player != self.player and read[i].player != no_player)
                    return true;
        } else {
            // return true if a trace of maximal "age" is found
            for(uint i = 0; i < dir::N; ++i)
                if((read[i].cnt >= self.cnt + 1 - age and read[i].player < self.player) or
                   (read[i].cnt >= self.cnt - age     and read[i].player > self.player))
                    return true;
        }
        return false;
    }
    int scent_age(std::array<field_type, dir::N> const & read
                , field_type const & self
                , dir::type const & move) {
        return self.cnt - (read[move].cnt - (read[move].player < self.player));
    }
    dir::type kill_move(std::array<field_type, dir::N> const & read
                      , field_type const & self) {
        for(uint i = 0; i < dir::N; ++i)
            if((read[i].cnt > self.cnt and read[i].player < self.player) or
               (read[i].cnt == self.cnt and read[i].player > self.player))
                return i;
        throw std::runtime_error("cannot kill any enemy!");
        return -1;
    }
    dir::type random_move(std::mt19937 & eng) {
        return eng() % dir::N;
    }
};

//=================== tracks a trace ===================
struct tracker_bot: public common_bot {
    dir::type move(int const &
                 , std::array<field_type, dir::N> const & read
                 , field_type const & self
                 , std::mt19937 & eng) {
        
        if(not trace_found(read, self))
            return random_move(eng);
        
        
        int max = -1;
        int next_move; // yes, it's uninitialized
        for(int i = 0; i < dir::N; ++i)
            if(read[i].player != self.player 
               and read[i].player != no_player 
               and read[i].cnt > max) {
                max = read[i].cnt;
                next_move = i;
            }
        
        return next_move;
    }
    std::string name() const {
        return "MK tracker";
    }
};

//=================== tracks a trace (kills spider) ===================
struct dodge_tracker_bot: public common_bot {
    dir::type move(int const &
                 , std::array<field_type, dir::N> const & read
                 , field_type const & self
                 , std::mt19937 & eng) {
        
        if(enemy_found(read, self))
            return kill_move(read, self);
        
        if(not trace_found(read, self))
            return random_move(eng);
        
        
        int max = -1;
        int next_move; // yes, it's uninitialized
        for(int i = 0; i < dir::N; ++i)
            if(read[i].player != self.player 
               and read[i].player != no_player 
               and read[i].cnt > max) {
                max = read[i].cnt;
                next_move = i;
            }
        
        if(scent_age(read, self, next_move) <= 2) {
            if(scent_age(read, self, (next_move + 1) % dir::N) > 2)
                return (next_move + 1) % dir::N;
            else
                return (next_move + dir::N - 1) % dir::N;
        }
        
        return next_move;
    }
    std::string name() const {
        return "MK dodge tracker";
    }
};

//=================== spins a hex-web and kills trackers ===================
struct spider_bot: public common_bot {
    dir::type move(int const & size
                 , std::array<field_type, dir::N> const & read
                 , field_type const & self
                 , std::mt19937 &) {    

        if(enemy_found(read, self))
            return kill_move(read, self);
        
        int stage = int(self.cnt / (2*size-5))%6;
        int future_stage = int((self.cnt+4) / (2*size-5))%6;
        
        switch(stage) {
            case(0):
                if(future_stage != stage) // move two further s.h. hexagon path doesnt close
                    return dir::left;
                else
                    if(self.cnt % 2)
                        return dir::up_left;
                    else
                        return dir::down_left;
                break;
            case(1):
                if(self.cnt % 2)
                    return dir::down_right;
                else
                    return dir::left;
                break;
            case(2):
                if(self.cnt % 2)
                    return dir::down_left;
                else
                    return dir::right;
                break;
            case(3):
                if(self.cnt % 2)
                    return dir::up_right;
                else
                    return dir::down_right;
                break;
            case(4):
                if(self.cnt % 2)
                    return dir::right;
                else
                    return dir::up_left;
                break;
            default:
                if(self.cnt % 2)
                    return dir::left;
                else
                    return dir::up_right;
                break;
                
        }
    }
    std::string name() const {
        return "MK spider";
    }
};

//=================== more defensive spider ===================
struct weaver_bot: public common_bot {
    dir::type move(int const & size
                 , std::array<field_type, dir::N> const & read
                 , field_type const & self
                 , std::mt19937 &) {

        if(enemy_found(read, self))
            return kill_move(read, self);
        
        // move two down
        if((self.cnt) % (2*size) == 0)
            return dir::down_left;
        if((self.cnt) % (2*size) == 1)
            return dir::down_left;
        
        // then do the spider move
        if(self.cnt % 2)
            return dir::up_left;
        else
            return dir::down_left;
    }
    std::string name() const {
        return "MK weaver";
    }
};

//=================== camper in all flavors ===================
template<dir::type D>
struct camper_bot: public common_bot {
    dir::type move(int const &
                 , std::array<field_type, dir::N> const & read
                 , field_type const & self
                 , std::mt19937 &) {
        
        if(enemy_found(read, self))
            return kill_move(read, self);
        
        if(D == dir::N) { // camper with triangle moves
            if(self.cnt % 3 == 0)
                return dir::right;
            if(self.cnt % 3 == 1)
                return dir::up_left;
            else
                return dir::down_left;
        } else { // camper "left-right" or other direction
            if(self.cnt % 2 == 0)
                return D;
            else
                return (D + dir::N/2) % dir::N;
        }
        
    }
    std::string name() const {
        std::vector<std::string> dirname(dir::N+1);
        dirname[dir::left] = "left";
        dirname[dir::right] = "right";
        dirname[dir::down_left] = "down_left";
        dirname[dir::down_right] = "down_right";
        dirname[dir::up_left] = "up_left";
        dirname[dir::up_right] = "up_right";
        dirname[dir::N] = "triangle";
        
        return "MK " + dirname[D] + " camper";
    }
};

#endif //MKOENZ_HEADER
