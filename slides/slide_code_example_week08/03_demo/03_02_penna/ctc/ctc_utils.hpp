// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    24.09.2015 13:29:36 CEST
// File:    meta_tpl_utils.hpp

#ifndef META_TPL_UTILS_HEADER
#define META_TPL_UTILS_HEADER

namespace ctc {
    template<typename T, uint32_t N>
    class array {
    public:
        using size_type = uint32_t;
        using value_type = T;
        constexpr array(): data_() {
        }
        constexpr array(array const & rhs) {
            for(size_type i = 0; i < N; ++i)
                data_[i] = rhs[i];
        }
        constexpr value_type operator[](size_type const & idx) const {
            return data_[idx];
        }
        constexpr value_type & operator[](size_type const & idx) {
            return data_[idx];
        }
        constexpr size_type size() const {
            return N;
        }
    private:
        value_type data_[N];
    };
    
    template<typename T, uint64_t N>
    class static_vector {
    public:
        using size_type = uint64_t;
        using value_type = T;
        // structors
        constexpr static_vector(size_type const & size = 0): size_(size) {
            
        }
        constexpr static_vector(static_vector const & rhs): size_(rhs.size_) {
            for(size_type i = 0; i < size(); ++i)
                array_[i] = rhs[i];
        }
        // modifying methods
        constexpr value_type & operator[](size_type const & idx) {
            return array_[idx];
        }
        constexpr void push_back(value_type const & in) {
            array_[size_] = in;
            ++size_;
        }
        constexpr value_type & back() {
            return array_[size_-1];
        }
        // const methods
        constexpr value_type operator[](size_type const & idx) const {
            return array_[idx];
        }
        constexpr size_type size() const {
            return size_;
        }
    private:
        size_type size_;
        array<T, N> array_;
    };
    
    
    template<typename T, typename U>
    struct pair {
        typedef T first_type;
        typedef U second_type;
        
        //------------------- ctors -------------------
        constexpr pair(): first(), second() {
        }
        constexpr pair(T const & f, U const & s): first(f), second(s) {
        }
        constexpr pair(pair const & rhs): first(rhs.first), second(rhs.second) {
        }
        
        //------------------- data -------------------
        first_type first;
        second_type second;
    };
    
    template<typename T, typename U>
    constexpr pair<T, U> make_pair(T const & t, U const & u) {
        return pair<T, U>(t, u);
    }
}//end namespace ctc

#endif //META_TPL_UTILS_HEADER
