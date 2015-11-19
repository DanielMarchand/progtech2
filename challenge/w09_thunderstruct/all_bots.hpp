// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2015 09:40:07 CET
// File:    all_bots.hpp

#ifndef ALL_BOTS_HEADER
#define ALL_BOTS_HEADER

#include <array>
#include <random>
#include <stdexcept>

#include "global.hpp"
#include "bot_concept_wrapper.hpp"

#include "students/flofrei.hpp"
#include "students/fraschs.hpp"
#include "students/greschd.hpp"
#include "students/krummenf.hpp"
#include "students/untergam.hpp"

#include "mkoenz.hpp"

std::vector<bot_wrap> get_player() {
    std::vector<bot_wrap> res;
    
    //flofrei
    // kill; triangle circle; sometimes random;
    res.push_back(tri_bot());
    // kill; square circle; sometimes random;
    res.push_back(quad_bot());
    
    //fraschs
    // kill; evade; hexagonal circle; sometime random offset;
    res.push_back(godzilla_bot());
    
    //greschd
    // kill; evade; rl-camper;
    res.push_back(ultimate_camper());
    // kill; evade; same-dir random move;
    res.push_back(wandering_camper());
    
    //krummenf
    // kill; tri-caper; ; sometimes wanders; minmal hunt;
    res.push_back(krummenf_shy());
    // kill; explore; hunt;
    res.push_back(krummenf_hunter());
    
    //untergam
    res.push_back(annihilator_bot());
    res.push_back(metaannihilator_bot());
    
    //mkoenz
    res.push_back(dodge_tracker_bot());
    res.push_back(spider_bot());
    
    return res;
}


#endif //ALL_BOTS_HEADER
