#ifndef UNTERGAM_HEADER
#define UNTERGAM_HEADER

#include <algorithm>

struct basebot {
  
	public:

		// Moving
		dir::type move(int const & size
					 , std::array<field_type, dir::N> const & nbrfields
					 , field_type const & myfield
					 , std::mt19937 & rndeng)
		{

			int myID = myfield.player;
			int cnt = myfield.cnt;
			
			// Check which players turn it is first
			bool iamfirst = (myID == 0);

			// only compares the field values associated with the enemy
			auto fieldcomp_enemy = [myID] (field_type a, field_type b) {
				int ca = (a.player==myID ? 0 : a.cnt);
				int cb = (b.player==myID ? 0 : b.cnt);
				return ca < cb;
			};
			
			auto fieldcomp_me = [myID] (field_type a, field_type b) {
				int ca = (a.player==myID ? a.cnt : 0);
				int cb = (b.player==myID ? b.cnt : 0);
				return ca < cb;
			};


			// direction of maximal value of enemy
			auto iter_max_value = std::max_element( nbrfields.begin(), nbrfields.end(), fieldcomp_enemy);
			int max_value = (*iter_max_value).cnt;
			int max_dir = std::distance(nbrfields.begin(),iter_max_value);

			// direction of minimal value of enemy
			auto iter_min_value = std::min_element( nbrfields.begin(), nbrfields.end(), fieldcomp_enemy);
			int min_value = (*iter_min_value).cnt;
			int min_dir = std::distance(nbrfields.begin(),iter_min_value);

			// direction of motion 
			auto iter_dir_of_motion = std::max_element( nbrfields.begin(), nbrfields.end(), fieldcomp_me);
			int current_dir = (std::distance(nbrfields.begin(),iter_dir_of_motion) + dir::N/2) % dir::N;

			// random direction
			int rnd_dir = rndeng() % dir::N;

			return getDir(cnt,size,iamfirst,max_value,max_dir,min_value,min_dir,current_dir,rnd_dir)%dir::N;
		}
	  
		// Return Name
		virtual std::string name() const = 0;

	protected: 
		// uuuuuuuugly
		virtual int getDir(int&,int const&,bool&,int&,int&,int&,int&,int&,int&) = 0;

};

// ANNIHILATOR
struct annihilator_bot : basebot {
	
	// Return Name
	std::string name() const {
		return "UM annihilator";
	}
   
	protected:

	int getDir(int& cnt, int const& size, bool& iamfirst,
			int& max_val, int& max_dir,
			int& min_val, int& min_dir,
			int& current_dir, int& rnd_dir) override {

		int nextdir = 0; // direction of next move

		if(max_val == cnt-iamfirst+1) {
			nextdir = max_dir;
		} else if(max_val == cnt-iamfirst-1){
			nextdir = min_dir;
		} else if(min_val == cnt-iamfirst){
			nextdir = max_dir;
		} else if(max_val-cnt > size/5) {
			nextdir = (cnt%(size/5) ? current_dir : rnd_dir);
		}

		return nextdir;

	}
  
};


// META-ANNIHILATOR
struct metaannihilator_bot : basebot {
	
	// Return Name
	std::string name() const {
		return "UM metaannihilator";
	}
   
	protected:

	int getDir(int& cnt, int const& size, bool& iamfirst,
			int& max_val, int& max_dir,
			int&        , int& min_dir,
			int& current_dir, int& rnd_dir) override {

		int nextdir = 0; // direction of next move

		nextdir = (cnt%(size/5) ? current_dir : rnd_dir);

		if(max_val == cnt-iamfirst+1) {
			nextdir = max_dir;
		} else if(max_val == cnt-iamfirst) {
			nextdir = rnd_dir;
		} else if(max_val == cnt-iamfirst-1){
			nextdir = (rnd_dir%2 ? min_dir : current_dir+2);
		} else {
			nextdir = current_dir+3;
		}

		return nextdir;

	}
  
};


#endif //UNTERGAM_HEADER
