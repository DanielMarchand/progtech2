/*******************************************************************************
 *
 * adapter to simulation
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

/*
 * types and const/volatile/reference (cvr) in red
 * can be defined by you
 * 
 * don't forget the include-guard
 */

template<typename T>
class yourlibname_to_sim {
    public:
    
    using count_array = /*impl*/;
    
    adapter(/*age_type crv*/ = 0);

    adapter(adapter && rhs) noexcept;
    bool progress(count_array /*cvr*/, count_array /*cvr*/);
    static /*age_type crv*/ random_age();
    static void set_gene_size(/*age_type crv*/);
    
    // const methods
    bool adult() const;
    T make_child() const;
    static /*int convertible*/ index;
};

template<typename T>
std::ostream & operator<<(std::ostream & os, adapter<T> const & arg);
