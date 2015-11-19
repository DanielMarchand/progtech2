#ifndef FLOFREI_HEADER
#define FLOFREI_HEADER

struct tri_bot{
	dir::type move(int const & // field-size
                 , std::array<field_type, dir::N> const & neighbour// the six neighbour fields
                 , field_type const & my_pos// the field I'm currently on
                 , std::mt19937 & eng)
	{
		for(int k=0;k<dir::N;++k)
		{
			field_type tester=neighbour[k];
			if(tester.player!=my_pos.player&&(tester.cnt==my_pos.cnt||tester.cnt==my_pos.cnt+1))
			{
			if((my_pos.cnt+10)%10==0){return eng() % dir::N;}
				switch(k){
				case 0:
					return dir::up_left;
					break;
				case 1:
					return dir::left;
					break;
				case 2:
					return dir::down_left;
					break;
				case 3:
					return dir::down_right;
					break;
				case 4:
					return dir::right;
					break;
				case 5:
					return dir::up_right;
					break;
				default:
					return dir::right;
					break;
				}
			}
		}
		
		if(((my_pos.cnt+3)/3)%2==0){return eng() % dir::N;}
		
		
		if(my_pos.cnt%3 == 0){
			return dir::up_left;
			}
		else if(my_pos.cnt%3 == 1){
			return dir::down_left;
			}
		else if(my_pos.cnt%3 == 2){
			return dir::right;
			}
		else{
			return (eng() % dir::N);
			}
		
		
	}
	std::string name() const {
		return "FF rnd triangle";
		}
	
	};
	
struct quad_bot{
	dir::type move(int const & // field-size
                 , std::array<field_type, dir::N> const & neighbour// the six neighbour fields
                 , field_type const & my_pos// the field I'm currently on
                 , std::mt19937 & eng)
	{
		for(int k=0;k<dir::N;++k)
		{
			field_type tester=neighbour[k];
			if(tester.player!=my_pos.player&&(tester.cnt==my_pos.cnt||tester.cnt==my_pos.cnt+1))
			{
			if((my_pos.cnt+10)%10==0){return eng() % dir::N;}
				switch(k){
				case 0:
					return dir::up_left;
					break;
				case 1:
					return dir::left;
					break;
				case 2:
					return dir::down_left;
					break;
				case 3:
					return dir::down_right;
					break;
				case 4:
					return dir::right;
					break;
				case 5:
					return dir::up_right;
					break;
				default:
					return dir::right;
					break;
				}
			}
		}
		
		if(((my_pos.cnt+4)/4)%2==0){return eng() % dir::N;}
		
		
		if(my_pos.cnt%4 == 0){
			return dir::down_left;
			}
		else if(my_pos.cnt%4 == 1){
			return dir::down_right;
			}
		else if(my_pos.cnt%4 == 2){
			return dir::up_right;
			}
		else if(my_pos.cnt%4 == 3)
			{
			return dir::up_left;
			}
		else{
			return (eng() % dir::N);
			}
		
		
	}
	std::string name() const {
		return "FF rnd quadrat";
		}
	
	};

#endif //FLOFREI_HEADER
