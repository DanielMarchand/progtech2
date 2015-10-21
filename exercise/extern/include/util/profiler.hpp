// Author:  Mario S. Könz <mskoenz@gmx.net>, Donjan Rodic <donjan@dyx.ch>
// Date:    05.09.2015 20:21:53 CEST
// File:    profiler.hpp
// License: WTFPL (http://sam.zoy.org/wtfpl/)

#ifndef UTIL_PROFILER_HEADER
#define UTIL_PROFILER_HEADER

#include "rdtsc_timer.hpp"
#include "accumulator.hpp"

#include <assert.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <set>
#include <map>
#include <functional>

// todo: force inline->see no_macros_branch


namespace util {
    namespace detail {
        struct node_struct {
            using res_type = double;
            using pair_type = std::pair<res_type, res_type>;
            node_struct(): name(""), parent(nullptr), current_run(pair_type(0, 0)) {
            }
            std::string name;
            node_struct * parent;
            pair_type current_run;
            accumulator<res_type> acc[2];
            std::set<node_struct*> children;
        };
        
        inline rdtsc_timer & get_timer() {
            static rdtsc_timer t;
            return t;
        }
    }//end namespace detail
    
    class profiler {
        using res_type = detail::node_struct::res_type;
        using pair_type = detail::node_struct::pair_type;
    public:
        profiler(): timer_(detail::get_timer()) {
            sentinel_.name = "sentinel_root";
            stack_.push_back(&sentinel_);
        }
        profiler(profiler const &) = delete;
        
        inline void start(std::string const & name) {
            process_start(name, get_cyc());
        }
        inline void next(std::string const & name) {
            process_stop(stack_.back()->name, get_cyc());
            process_start(name, pair_type(0, 0));
        }
        inline void stop(std::string const & name) {
            process_stop(name, get_cyc());
        }
        void print_tree() const {
            std::cout << "Usage of rdtsc (CPU bound):" << std::endl;
            std::vector<bool> marker;
            std::string msm_mod_str = mod_ == msm_mod::cycle ? "cycle_mean" : "nsec_mean";
            std::cout << std::setw(8+14) << "┬ (% of parent) name"
                      << std::string(80-53, ' ')
                      << std::right << std::setw(10) << msm_mod_str
                      << std::setw(10+1) << "spread"
                      << std::setw(10) << "run_cnt"
                      << std::endl;
            auto i = sentinel_.children.size();
            auto mod = int(mod_);
            for(auto const & p : sentinel_.children) {
                --i;
                print_tree_helper( p
                                 , i == 0
                                 , marker
                                 , mod ? sentinel_.current_run.second : sentinel_.current_run.first
                                 , p->acc[mod].mean() * p->acc[mod].count()
                                 );
            }
        }
        void set_mod(std::string const & smod = "cycle") {
            if(smod == "cycle")
                mod_ = util::profiler::msm_mod::cycle;
            else if(smod == "nsec")
                mod_ = util::profiler::msm_mod::nsec;
            else {
                std::stringstream ss;
                ss << "util::profiler: invalid mode '" << smod << "'";
                throw std::runtime_error(ss.str());
            }
                
        }
        void save(std::string file) const {
            while(true) { // make sure no accidental overwrite can happen
                std::ifstream ifs(file);
                if(ifs.is_open()) {
                    ifs.close();
                    std::cout << "file '" << file << "' already exists" << std::endl;
                    std::cout << "type 'o' for overwrite or new filename: " << std::endl;
                    std::string choice;
                    std::cin >> choice;
                    if(choice != "o")
                        file = choice;
                    else
                        break;
                } else
                    break;
            }
            std::ofstream ofs(file);
            
            std::string smod = mod_ == msm_mod::cycle ? "cycle" : "nsec";
            ofs << "parent name " << smod << "_mean " << smod << "_std calls" << std::endl;
            auto mod = int(mod_);
            for(auto const & p: tree_) {
                auto node = p.second;
                auto count = node.acc[mod].count();
                ofs << node.parent->name << " "
                    << node.name << " "
                    << node.acc[mod].mean() << " "
                    << (count > 1 ? node.acc[mod].std() : 0) << " "
                    << count << std::endl;
            }
            
            ofs.close();
            
        }
    private:
        pair_type get_cyc() {
            auto cyc = timer_.cycles();
            auto nsec = timer_.nsec();
            timer_.start();
            timer_.stop();
            cyc -= timer_.cycles();
            return pair_type(cyc, nsec);
        }
        void process_start(std::string const & name, pair_type const & msm) {
            if(name.find(" ") != std::string::npos) {
                std::stringstream ss;
                ss << "util::profiler: name '" << name << "' invalid! no spaces allowed";
                throw std::runtime_error(ss.str());
            }
            
            static bool first_start = true;
            if(first_start)
                first_start = false;
            else
                for(auto ptr: stack_) {
                    ptr->current_run.first  += msm.first;
                    ptr->current_run.second += msm.second;
                }
            
            tree_[name].name = name;
            tree_[name].parent = stack_.back();
            stack_.push_back(&tree_[name]);
            tree_[name].parent->children.insert(&tree_[name]);
        }
        void process_stop(std::string const & name, pair_type const & msm) {
            if(name != stack_.back()->name) {
                std::stringstream ss;
                ss << "util::profiler: stopped '" << name << "' instead of '" 
                   << stack_.back()->name << "'";
                throw std::runtime_error(ss.str());
            }
            
            for(auto ptr: stack_) {
                ptr->current_run.first  += msm.first;
                ptr->current_run.second += msm.second;
            }
            
            auto node = stack_.back();
            node->acc[0] << node->current_run.first;
            node->acc[1] << node->current_run.second;
            node->current_run = pair_type(0, 0);
            stack_.pop_back();
        }
        void print_tree_helper( const detail::node_struct* parent
                              , const bool lastchild
                              , std::vector<bool> & marker
                              , const res_type & parent_time
                              , const res_type & self_time
                              ) const {

            auto mod = int(mod_);
            for(auto c : marker) {
                if(!c) {
                    std::cout << "│" << std::string(4-1, ' ');
                    
                } else
                    std::cout << std::string(4, ' ');
            }
            int whitespace = 80-8-12-30-2-1-4*marker.size();
            if(whitespace < 0) whitespace = 0;
            std::cout << (lastchild ? "└" : "├") << "─"
                      << std::setw(3) << int(100*self_time/parent_time) << "% "
                      << std::left << std::setw(12) << parent->name << std::right
                      << std::string(whitespace, ' ') << std::fixed <<  "["
                      << std::setw(10) << std::setprecision(parent->acc[mod].mean()<10?1:0) <<  parent->acc[mod].mean()
                      << std::setw(10) << 100*(parent->acc[mod].std()/parent->acc[mod].mean()) << "%"
                      << std::setw(10) << std::right << parent->acc[mod].count()
                      << "]" << std::defaultfloat << std::endl;
            auto i = parent->children.size();
            marker.push_back(lastchild);
            for(auto const & p : parent->children) {
                --i;
                print_tree_helper( p
                                 , i == 0
                                 , marker
                                 , self_time
                                 , int64_t(p->acc[mod].mean() * p->acc[mod].count())
                                 );
            }
            marker.pop_back();
        }
    public:
        rdtsc_timer & timer_;
    private:
        enum class msm_mod: uint8_t {cycle = 0, nsec = 1};
        msm_mod mod_ = msm_mod::cycle;
        
        detail::node_struct sentinel_;
        std::vector<detail::node_struct*> stack_;
        std::map<std::string, detail::node_struct> tree_;
    };
    
    namespace detail {
        inline profiler & get_profiler() {
            static profiler p;
            return p;
        }
        static auto & mib_prof = get_profiler();
        
        namespace dont_even_ask { //state of the art... trust me ;P
            inline void fct() {
                (void)mib_prof;
            }
        }//end namespace dont_even_ask
        
    }//end namespace detail
    
}//end namespace util

#define MIB_START(name)                 \
util::detail::mib_prof.timer_.stop();   \
util::detail::mib_prof.start(name);     \
util::detail::mib_prof.timer_.start();  //

#define MIB_STOP(name)                  \
util::detail::mib_prof.timer_.stop();   \
util::detail::mib_prof.stop(name);      \
util::detail::mib_prof.timer_.start();  //

#define MIB_NEXT(name)                  \
util::detail::mib_prof.timer_.stop();   \
util::detail::mib_prof.next(name);      \
util::detail::mib_prof.timer_.start();  //

#define MIB_PRINT(mod)                  \
util::detail::mib_prof.set_mod(mod);    \
util::detail::mib_prof.print_tree();    //

#define MIB_SAVE(mod, file)             \
util::detail::mib_prof.set_mod(mod);    \
util::detail::mib_prof.save(file);      //


#endif //UTIL_PROFILER_HEADER
