// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    01.11.2015 13:19:20 CET
// File:    ctc_mersenne.hpp

#ifndef CTC_MERSENNE_HEADER
#define CTC_MERSENNE_HEADER

namespace ctc {
    class mt19937 {
        uint16_t const N = 624;
        uint16_t const M = 397;
        uint32_t const HI = 0x80000000;
        uint32_t const LO = 0x7fffffff;
    public:
        constexpr mt19937(): y() {
            seed(5489UL);
        }
        constexpr mt19937(uint32_t const & s): y() {
            seed(s);
        }
        constexpr uint32_t operator()() {
            if(index_ >= N)
                refill();
            
            uint32_t e = y[index_++];
            /* Tempering */
            e ^= (e >> 11);
            e ^= (e <<  7) & 0x9d2c5680;
            e ^= (e << 15) & 0xefc60000;
            e ^= (e >> 18);
     
            return e;
        }
        constexpr void refill() {
            int i = 0;
            uint32_t h = 0;
            
            for(i = 0; i < N - M; ++i) {
                h = (y[i] & HI) | (y[i+1] & LO);
                y[i] = y[i+M] ^ (h >> 1) ^ A[h & 1];
            }
            for (; i<N-1; ++i) {
                h = (y[i] & HI) | (y[i+1] & LO);
                y[i] = y[i+(M-N)] ^ (h >> 1) ^ A[h & 1];
            }

            h = (y[N-1] & HI) | (y[0] & LO);
            y[N-1] = y[M-1] ^ (h >> 1) ^ A[h & 1];
            index_ = 0;
        }
        constexpr void init() {
            y[0] = seed_;
            for (uint16_t i = 1; i < N; ++i) {
                y[i] = (1812433253UL * (y[i-1] ^ (y[i-1] >> 30)) + i);
            }
            refill();
        }
        constexpr void seed(uint32_t const & seed) {
            seed_ = seed;
            init();
        }
        constexpr double norm() {
            uint64_t max = 1;
            max <<= 32;
            return double((*this)()) / max;
        }
    private:
        uint32_t seed_ = 5489UL;
        const uint32_t A[2] = {0, 0x9908b0df};
        uint32_t y[624];
        uint16_t index_ = 0;
    };
}//end namespace ctc
#endif //CTC_MERSENNE_HEADER
