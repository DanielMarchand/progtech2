/*******************************************************************************
 *
 * Animal Concept Definition
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

/*
Declaration of animal_concept

Object t of type T in namespace tns

Type definitions and enums:

using T::age_type = implementation-defined
using T::mut_type = implementation-defined
enum tns::tag::animal_enum

Free functions:
operator<<(std::ostream&, T::age_type)
operator<<(std::ostream&, T::mut_type)

Methods:

T(T::age_type T::random_age())

bool T::progress(sim::count_array const &, sim::count_array const &);
bool T::adult() const;
animal_concept T::make_child();
std::ostream & T::print(std::ostream &) const;
tns::tag_enum T::index() const;

Public Members:

static age_type prop.gene_size;
static age_type prop.repr_age;
static mut_type prop.threshold;
static mut_type prop.mut_rate;
static const std::string name;
static const tag::animal_enum index;

*/

#ifndef ANIMALCONCEPT_HEADER
#define ANIMALCONCEPT_HEADER

#include <sim_typedef.hpp>

#include <memory>
#include <type_traits>


namespace sim {

template<typename CA>
class animal_concept;

template<typename CA>
class animal_concept_base {  // polymorphic base class

    public:

    virtual ~animal_concept_base() {}


    virtual bool progress( CA const & N_max
                         , CA const & N_t) = 0;
    virtual bool adult() const = 0;
    virtual animal_concept<CA> make_child() = 0;
    virtual std::ostream & print(std::ostream &) const = 0;
    virtual count_type index() const = 0;

    // using age_type = uint32_t;
    // using mut_type = uint32_t;
    // static age_type prop.gene_size;
    // static age_type prop.repr_age;
    // static mut_type prop.threshold;
    // static mut_type prop.mut_rate;
    // static const std::string name;
    // static const tag::animal_enum index;

};

template <typename T, typename CA>
class animal_concept_impl;

template<typename CA>
class animal_concept {  // wrapper class

    public:
    animal_concept(animal_concept const &) = delete;
    animal_concept(animal_concept &&) = default;
    template <typename T, typename DUMMY = std::enable_if_t<!std::is_same<T, animal_concept<CA>>::value, int>>
    animal_concept(T && t):
        p(new animal_concept_impl<std::remove_reference_t<T>, CA>(std::forward<T>(t))) {}

    inline bool progress( CA const & N_max
                        , CA const & N_t) {
        return p->progress(N_max, N_t);
    }
    inline bool adult() const { return p->adult(); }
    inline animal_concept make_child() { return p->make_child(); }
    inline std::ostream & print(std::ostream & os) const {
        return (*p).print(os);
    }
    inline count_type index() const { return p->index(); }

    private:

    std::unique_ptr<animal_concept_base<CA>> p;

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
    inline std::ostream & print(std::ostream & os) const override {
        return os << t_;
    }
    inline count_type index() const override { return T::index; }

    private:

    T t_;

};

// We don't outsource the above classes with template methods => this would be
// the only function in the cpp, so let's be reasonable here and skip the cpp.
template<typename CA>
std::ostream & operator<<(std::ostream & os, animal_concept<CA> const & arg) {
    return arg.print(os);
}

}

#endif // ANIMALCONCEPT_HEADER
