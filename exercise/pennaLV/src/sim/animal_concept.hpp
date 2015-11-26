/** ****************************************************************************
 * 
 * \file
 * \brief Animal Concept Definition
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * 
 ******************************************************************************/

#ifndef SIM_ANIMALCONCEPT_HEADER
#define SIM_ANIMALCONCEPT_HEADER

#include <sim_typedef.hpp>

#include <memory>
#include <type_traits>

// documented in simulation.hpp
namespace sim {

/// \class
template<typename CA>
class animal_concept;

/// \cond IMPLEMENTATION_DETAIL_DOC
template<typename CA>
class animal_concept_base {  // polymorphic base class

    public:
    using count_array = CA;
    
    virtual ~animal_concept_base() {}


    virtual bool progress( count_array const & N_max
                         , count_array const & N_t) = 0;
    virtual bool adult() const = 0;
    virtual animal_concept<count_array> make_child() = 0;
    virtual void print(std::ostream &) const = 0;
    virtual count_type index() const = 0;
};

template <typename T, typename CA>
class animal_concept_impl : public animal_concept_base<CA> {  // concept holder class

    public:

    animal_concept_impl(T && t) : t_(std::move(t)) {}
    

    inline bool progress( CA const & N_max
                        , CA const & N_t) override {
        return t_.progress(N_max, N_t);
    }
    inline bool adult() const override { return t_.adult(); }
    inline animal_concept<CA> make_child() override {
        return animal_concept<CA>(std::move(t_.make_child()));
    }
    inline void print(std::ostream & os) const override {
        os << t_;
    }
    inline count_type index() const override { return T::index; }

    private:

    T t_;

};
/// \endcond

/**\brief This wrapper takes anything that fulfills the animal-concept ().
 * \tparam CA  is a count array type that has a array-like behaviour.
 *         the exact implementation is not needed by the wrapper and is thus an
 *         implementation-detail of an animal-library.
 * \details
#### Declaration of animal concept

Let:
 - T be a model that fulfills the animal concept
 - t an instance of T
 - uint_conv a type that can be converted implicitly to an uint

Valid Expressions:

~~~{.cpp}
    T::count_array x; // needs to be a array-like 
                      // type that can be accessed []
    T::count_array y;
    x[1];

    T t(T::random_age()); // constructor with random age
    T const ct(T::random_age());
    bool survived = t.progress(x, y);

    bool is_adult =  tc.adult();
    animal_concept c(tc.make_child());
    tc.print(); // prints the animal

    uint32_t idx = T::index; // returns the index
                             // where the animal is in x
    std::string name = T::name;
~~~
 */
template<typename CA>
class animal_concept {  // wrapper class

    public:
    /**\brief disabled copy-constructor
     * \details the parameter is the animal_concept that is copied from
     */
    animal_concept(animal_concept const &) = delete;
    /**\brief move-constructor
     * \details the parameter is the animal_concept that is moved from
     */
    animal_concept(animal_concept &&) = default;
    
    /**\brief Generalized constructor that takes anything that fulfills the animal-concept as a universal reference.
     * \tparam T  the type of the incomming instance
     * \tparam DUMMY  used for SFINAE. Since this constructor is a better match 
     *         than the copy-constructor (if we enable it one day) for an lvalue, we 
     *         disable this template for the case we want the copy-constructor to handle.
     *         (it matches better since an <tt>animal_concept &</tt> must be converted 
     *         to <tt>animal_concept const &</tt> for the copy-constructor)
     * 
     */
    template <typename T, typename DUMMY = std::enable_if_t<!std::is_same<T, animal_concept<CA>>::value, int>>
    animal_concept(T && t):
        p(new animal_concept_impl<std::remove_reference_t<T>, CA>(std::forward<T>(t))) {}
    /**\brief this function ages the animal
     * \param N_max  holds the carrying capacity factors. 
     *        The exact implementation is left to the animal-library.
     * \param N_t  holds the current count of animals for each species.
     *        The exact implementation is left to the animal-library.
     * \return \c true if the animal survived, \c false otherwise.
     */
    inline bool progress( CA const & N_max
                        , CA const & N_t) {
        return p->progress(N_max, N_t);
    }
    
    /**\brief checks if an animal is adult
     * \return \c true if the animal is old enough to generate offspring, \c false otherwise.
     */
    inline bool adult() const { return p->adult(); }
    /**\brief creates a child by asexual reproduction
     * \returns a new animal_concept which holds the child
     */
    inline animal_concept make_child() { return p->make_child(); }
    /**\brief just forwards print to the animal.
     * \param os  std::cout or any std::ostream instance
     */
    inline void print(std::ostream & os) const {
        p->print(os);
    }
    /**\brief position in count array for a species (e.g. in \c N_max in progress)
     * \return the index of an animal in the CA count array.
     */
    inline count_type index() const { return p->index(); }

    private:

    std::unique_ptr<animal_concept_base<CA>> p;

};

// We don't outsource the above classes with template methods => this would be
// the only function in the cpp, so let's be reasonable here and skip the cpp.
/**\brief wraps the animal print function
 * \param os  std::cout or any std::ostream instance
 * \param arg  an animal_concept instance
 * \return the ostream reference to \c os
 */
template<typename CA>
std::ostream & operator<<(std::ostream & os, animal_concept<CA> const & arg) {
    arg.print(os);
    return os;
}

}

#endif // SIM_ANIMALCONCEPT_HEADER
