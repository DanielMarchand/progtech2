// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    03.11.2015 10:47:08 CET
// File:    presenation.hpp

#ifndef PRESENATION_HEADER
#define PRESENATION_HEADER

#include "pres_print_type.hpp"
#include <limits>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <sstream>

struct present_class {

    // structors
    present_class(): depth(0)
                   , indent(2)
                   , indent_start(2)
                   , newlines(1)
                    {}
    
    // modifying methods
    void exname(std::string const & name, std::string const & col = rescol) {
        if(depth > 0 and last_depth != depth)
            std::cout << std::endl;
        
        colstack.push_back(col);
        std::cout << get_indent() <<col << name << rescol;
        last_depth = depth;
        ++depth;
    }
    template<typename T>
    void exres(T t) {
        std::string col = colstack.back();
        colstack.pop_back();
        --depth;
        if(depth == last_depth)
            std::cout << " = ";
        else {
            std::cout << get_indent() << col << "└" << rescol << " = ";
        }
        
        std::stringstream ss;
        ss << col << t << rescol << std::endl;
        to_print = ss.str();
        
    }
    void exprint() {
        std::cout << to_print;
        if(depth == 0)
            std::cout << get_newlines();
    }
    
    // const methods
    
    void empty_callname(std::string const & col = rescol) {
        if(depth > 0 and last_depth != depth)
            std::cout << std::endl;
        colstack.push_back(col);
        last_depth = depth;
        ++depth;
    }
    void callname(std::string const & name, std::string const & col = rescol) {
        std::cout << get_indent() <<col << name << rescol << ": ";
        empty_callname(col);
    }
    void callprint() {
        --depth;
        colstack.pop_back();
        
        if(depth == 0)
            std::cout << get_newlines();
    }
    
    template<typename T>
    void print(T const & t, std::string const & col = rescol) {
        if(depth > 0)
            if(last_depth == depth) {
                std::cout << get_indent() << col << t << rescol << std::endl;
            }
            else {
                std::cout << std::endl << get_indent() << col << t << rescol;
            }
        else
            std::cout << get_indent() << col << t << rescol << std::endl << get_newlines();
    }
    void clrscr() const {
        std::cout << "\033[2J\033[100A" << get_newlines();
    }
    
    std::string get_newlines() const {
        return std::string(newlines, '\n');
    }
    
    std::string get_indent() const {
        std::stringstream ss;
        
        ss << std::string(indent_start, ' ');
        for(uint32_t i = 0; i < depth; ++i) {
            ss << colstack[i] << "│" << std::string(indent - 1, ' ');
        }
        
        return ss.str();
    }
    
    //=================== sig ===================
    struct sig_observer_class {
        inline sig_observer_class(present_class & pres, std::string sig) : pres(pres) {
            uint32_t space = 80 - 4 - pres.depth * pres.indent - 2 * pres.indent_start;
            if(pres.current_sig != sig) {
                pres.current_sig = sig;
                if(sig.size() > space) {
                    sig.erase(space);
                    sig += " ...";
                }
                pres.exname(sig);
                ok = true;
            } else
                ok = false;
        }
        inline ~sig_observer_class() {
            if(ok) {
                pres.colstack.pop_back();
                
                if(pres.depth == pres.last_depth+1) {
                    std::cout << std::endl;
                }
                --pres.depth;
            }
        }
        bool ok;
        present_class & pres;
    };
    
    
    
//~ private:
    uint32_t depth;
    uint32_t last_depth;
    uint32_t indent;
    uint32_t indent_start;
    uint32_t newlines;
    static std::string const rescol;
    
    std::string to_print;
    std::string current_sig;
    std::vector<std::string> colstack;
} pres;

std::string const present_class::rescol = "\033[0m";


//========= some macros for nicer presentation (not essential) =========
//use as litte macros as possible in c++ (most stuff can be solved without)
//I just use them here to keep the unimportant stuff away from the main code
#define NEW_LINE() std::cout << std::endl;
#define WAIT() std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#define CLRSCR() pres.clrscr();

#define NORMAL "\033[0m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define MAGENTA "\033[1;35m"

//all the \033... cmd are bash specific. See http://www.cplusplus.com/forum/unices/36461/ for details
#define P_NORMAL(...) pres.print(__VA_ARGS__, NORMAL);
#define PW_NORMAL(...) WAIT() pres.print(__VA_ARGS__, NORMAL);
#define PN_NORMAL(...) pres.exname(#__VA_ARGS__, NORMAL); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_NORMAL(...)      WAIT() pres.exname(#__VA_ARGS__, NORMAL); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_NORMAL(...)     WAIT() pres.exname(#__VA_ARGS__, NORMAL); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CW_NORMAL(...)     WAIT() pres.empty_callname(NORMAL); __VA_ARGS__; pres.callprint();
#define CNW_NORMAL(...)     WAIT() pres.callname(#__VA_ARGS__, NORMAL); __VA_ARGS__; pres.callprint();
#define CNWW_NORMAL(...)     WAIT() pres.callname(#__VA_ARGS__, NORMAL); WAIT() __VA_ARGS__; pres.callprint();

#define P_RED(...) pres.print(__VA_ARGS__, RED);
#define PW_RED(...) WAIT() pres.print(__VA_ARGS__, RED);
#define PN_RED(...) pres.exname(#__VA_ARGS__, RED); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_RED(...)      WAIT() pres.exname(#__VA_ARGS__, RED); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_RED(...)     WAIT() pres.exname(#__VA_ARGS__, RED); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CW_RED(...)     WAIT() pres.empty_callname(RED); __VA_ARGS__; pres.callprint();
#define CNW_RED(...)     WAIT() pres.callname(#__VA_ARGS__, RED); __VA_ARGS__; pres.callprint();
#define CNWW_RED(...)     WAIT() pres.callname(#__VA_ARGS__, RED); WAIT() __VA_ARGS__; pres.callprint();

#define P_BLUE(...) pres.print(__VA_ARGS__, BLUE);
#define PW_BLUE(...) WAIT() pres.print(__VA_ARGS__, BLUE);
#define PN_BLUE(...) pres.exname(#__VA_ARGS__, BLUE); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_BLUE(...)      WAIT() pres.exname(#__VA_ARGS__, BLUE); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_BLUE(...)     WAIT() pres.exname(#__VA_ARGS__, BLUE); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CW_BLUE(...)     WAIT() pres.empty_callname(BLUE); __VA_ARGS__; pres.callprint();
#define CNW_BLUE(...)     WAIT() pres.callname(#__VA_ARGS__, BLUE); __VA_ARGS__; pres.callprint();
#define CNWW_BLUE(...)     WAIT() pres.callname(#__VA_ARGS__, BLUE); WAIT() __VA_ARGS__; pres.callprint();

#define P_CYAN(...) pres.print(__VA_ARGS__, CYAN);
#define PW_CYAN(...) WAIT() pres.print(__VA_ARGS__, CYAN);
#define PN_CYAN(...) pres.exname(#__VA_ARGS__, CYAN); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_CYAN(...)      WAIT() pres.exname(#__VA_ARGS__, CYAN); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_CYAN(...)     WAIT() pres.exname(#__VA_ARGS__, CYAN); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CNW_CYAN(...)     WAIT() pres.callname(#__VA_ARGS__, CYAN); __VA_ARGS__; pres.callprint();
#define CNWW_CYAN(...)     WAIT() pres.callname(#__VA_ARGS__, CYAN); WAIT() __VA_ARGS__; pres.callprint();

#define P_GREEN(...) pres.print(__VA_ARGS__, GREEN);
#define PW_GREEN(...) WAIT() pres.print(__VA_ARGS__, GREEN);
#define PN_GREEN(...) pres.exname(#__VA_ARGS__, GREEN); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_GREEN(...)     WAIT() pres.exname(#__VA_ARGS__, GREEN); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_GREEN(...)     WAIT() pres.exname(#__VA_ARGS__, GREEN); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CW_GREEN(...)     WAIT() pres.empty_callname(GREEN); __VA_ARGS__; pres.callprint();
#define CNW_GREEN(...)     WAIT() pres.callname(#__VA_ARGS__, GREEN); __VA_ARGS__; pres.callprint();
#define CNWW_GREEN(...)     WAIT() pres.callname(#__VA_ARGS__, GREEN); WAIT() __VA_ARGS__; pres.callprint();

#define P_YELLOW(...) pres.print(__VA_ARGS__, YELLOW);
#define PW_YELLOW(...) WAIT() pres.print(__VA_ARGS__, YELLOW);
#define PN_YELLOW(...) pres.exname(#__VA_ARGS__, YELLOW); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_YELLOW(...)     WAIT() pres.exname(#__VA_ARGS__, YELLOW); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_YELLOW(...)     WAIT() pres.exname(#__VA_ARGS__, YELLOW); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CW_YELLOW(...)     WAIT() pres.empty_callname(YELLOW); __VA_ARGS__; pres.callprint();
#define CNW_YELLOW(...)     WAIT() pres.callname(#__VA_ARGS__, YELLOW); __VA_ARGS__; pres.callprint();
#define CNWW_YELLOW(...)     WAIT() pres.callname(#__VA_ARGS__, YELLOW); WAIT() __VA_ARGS__; pres.callprint();

#define P_MAGENTA(...) pres.print(__VA_ARGS__, MAGENTA);
#define PW_MAGENTA(...) WAIT() pres.print(__VA_ARGS__, MAGENTA);
#define PN_MAGENTA(...) pres.exname(#__VA_ARGS__, MAGENTA); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_MAGENTA(...)     WAIT() pres.exname(#__VA_ARGS__, MAGENTA); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_MAGENTA(...)     WAIT() pres.exname(#__VA_ARGS__, MAGENTA); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CW_MAGENTA(...)     WAIT() pres.empty_callname(MAGENTA); __VA_ARGS__; pres.callprint();
#define CNW_MAGENTA(...)     WAIT() pres.callname(#__VA_ARGS__, MAGENTA); __VA_ARGS__; pres.callprint();
#define CNWW_MAGENTA(...)     WAIT() pres.callname(#__VA_ARGS__, MAGENTA); WAIT() __VA_ARGS__; pres.callprint();

#define P_BOOL(...) pres.print(__VA_ARGS__, __VA_ARGS__ ? GREEN : RED);
#define PW_BOOL(...) WAIT() pres.print(__VA_ARGS__, __VA_ARGS__ ? GREEN : RED);
#define PN_BOOL(...) pres.exname(#__VA_ARGS__, __VA_ARGS__ ? GREEN : RED); pres.exres(__VA_ARGS__); pres.exprint();
#define PNW_BOOL(...)     WAIT() pres.exname(#__VA_ARGS__, __VA_ARGS__ ? GREEN : RED); pres.exres(__VA_ARGS__); pres.exprint();
#define PNWW_BOOL(...)     WAIT() pres.exname(#__VA_ARGS__, __VA_ARGS__ ? GREEN : RED); pres.exres(__VA_ARGS__); WAIT() pres.exprint();
#define CW_BOOL(...)     WAIT() pres.empty_callname(__VA_ARGS__ ? GREEN : RED); __VA_ARGS__; pres.callprint();
#define CNW_BOOL(...)     WAIT() pres.callname(#__VA_ARGS__, __VA_ARGS__ ? GREEN : RED); __VA_ARGS__; pres.callprint();
#define CNWW_BOOL(...)     WAIT() pres.callname(#__VA_ARGS__, __VA_ARGS__ ? GREEN : RED); WAIT() __VA_ARGS__; pres.callprint();

#define P_SIG() present_class::sig_observer_class sig_observer(pres, fct_sig());


void set_echo(bool on = true) {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    if(!on)
        term.c_lflag &= ~ECHO;
    else
        term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

namespace detail {
    struct echo_manager {
        echo_manager() {
            set_echo(false);
            CLRSCR()
        }
        ~echo_manager() {
            set_echo(true);
        }
    } manager;
    
}//end namespace detail

#endif //PRESENATION_HEADER
