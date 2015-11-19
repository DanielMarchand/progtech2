#ifndef KRUMMENF_HEADER
#define KRUMMENF_HEADER

//shy bot
struct krummenf_shy {
    dir::type move(int const & size
                 , std::array<field_type, dir::N> const & neighbours
                 , field_type const & current
                 , std::mt19937 &) {
		int me = current.player;
		int highest_enemy = -1;
		int highest_me = -1;
		int direction_enemy = -1;
		int direction_me = -1;
		int direct[] = {dir::up_left, dir::left, dir::down_left, dir::down_right, dir::right, dir::up_right};
		for(int i = 0; i < dir::N; ++i){
			auto v = neighbours[i];
			if(v.player == me && highest_me < v.cnt){
				highest_me = v.cnt;
				direction_me = i;
			}
			if(v.player != me && v.player != -1 && highest_enemy < v.cnt){
					highest_enemy = v.cnt;
					direction_enemy = i;
			}	
		}
		if(highest_enemy > -1 && std::abs(current.cnt - highest_enemy) < 2)
			return direct[direction_enemy]; //catch enemy if close enough
		else
			if(current.cnt != 0)
				if(current.cnt % (size*size/2) < size/4.)
					return direct[(direction_me + 3) % dir::N];
				else
					return direct[(direction_me + 1) % dir::N];
			else
				return direct[1];

    }
    std::string name() const {
        return "KF shy";
    }
};

//hunting bot 
struct krummenf_hunter {
    dir::type move(int const & size
                 , std::array<field_type, dir::N> const & neighbours
                 , field_type const & current
                 , std::mt19937 & eng) {
		int me = current.player;
		int highest_enemy = -1;
		int highest_me = -1;
		int direction_enemy = -1;
		int direction_me = -1;
		int direct[] = {dir::up_left, dir::left, dir::down_left, dir::down_right, dir::right, dir::up_right};
		for(int i = 0; i < dir::N; ++i){
			auto v = neighbours[i];
			if(v.player == me && highest_me < v.cnt){
				highest_me = v.cnt;
				direction_me = i;
			}
			if(v.player != me && v.player != -1 && highest_enemy < v.cnt){
					highest_enemy = v.cnt;
					direction_enemy = i;
			}	
		}
		
		if(highest_enemy > -1){
			if(eng() % (size*size) == 0){
				int k = (eng()%2) *2 - 1;
				return direct[(direction_enemy + dir::N + k) % dir::N];
				}
			else
				return direct[direction_enemy];
		}
		else{
			if(highest_me > -1){
				int op = (dir::N/2+direction_me) % dir::N;	//try moving in the same direction until finding your own trace
				if(neighbours[op].player != me)
					return direct[op];	
			}
		}
	
		return eng() % dir::N;
			
    } 
    std::string name() const {
        return "KF hunter";
    }
};

#endif //KRUMMENF_HEADER
