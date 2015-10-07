/*******************************************************************************
 *
 * Counter CRTP
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef COUNTER_CRTP_HEADER
#define COUNTER_CRTP_HEADER

namespace zoo {
    
    template<typename T>
    class counter_crtp {
    public:
        // structors
        counter_crtp() {
            ++T::prop.N_t;
        }
        //~ inline counter_crtp(counter_crtp const &) {
            //~ ++T::prop.N_t;
        //~ }
        ~counter_crtp() {
            --T::prop.N_t;
        }
    };
    
}//end namespace zoo

#endif //COUNTER_CRTP_HEADER
