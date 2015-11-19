// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2015 14:48:09 CET
// File:    print_helper.hpp

#ifndef PRINT_HELPER_HEADER
#define PRINT_HELPER_HEADER

#include <map>

//=================== logic helper ===================
using score_type = std::map<std::string, std::map<std::string, int>>;

bool same_team(std::string const & n1, std::string const & n2) {
    if(n1[0] == n2[0] and n1[1] == n2[1])
        return true;
    return false;
}

//=================== print helper ===================
std::string const ncol = "\033[0m";
std::string const renter = "\033[1A\x1B[2K";
std::string col( std::string const & p1
               , std::string const & enemy
               , score_type & score){
    int p_score = score[p1][enemy];
    int e_score = score[enemy][p1];
    
    if(e_score > p_score)
        return "\033[1;31m";
    if(e_score == p_score)
        return "\033[1;33m";
    else
        return "\033[1;32m";
}

std::string shorten(std::string s, uint32_t const & M) {
    if(s.size() > M)
        s.erase(M, s.size());
    return s;
}
    
void print_seperator(int const & size, int const & name_crop) {
    std::cout << "+" << std::string(name_crop, '-') << "+";
    for(int i = 0; i < size; ++i)
        std::cout << std::string(name_crop, '-') << "+";
    std::cout << std::endl;
}

#endif //PRINT_HELPER_HEADER
