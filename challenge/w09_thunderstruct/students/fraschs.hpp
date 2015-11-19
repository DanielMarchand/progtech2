#ifndef FRASCHS_HEADER
#define FRASCHS_HEADER


struct godzilla_bot
{
    //assuming bot with lowder player number begins
    dir::type move(int const &, std::array<field_type, dir::N> const & read, field_type const & self, std::mt19937 & eng) {

        dir::type count = 0;

        //check if direct win possible
        for(const auto& pos : read){
            const auto iAmSecond = pos.player < self.player; // 1 if i am second, 0 else
            if(pos.player != self.player && pos.player != no_player && pos.cnt == self.cnt + iAmSecond)
                return count;
            ++count;
        }

        //new direction
        auto new_dir = ( self.cnt + (eng()%2) ) % dir::N;


        //avoid following one step behind
        auto const & new_pos = read[new_dir];
        if(new_pos.player != new_pos.player && new_pos.player != no_player){
            const auto iAmFirst = (new_pos.player > self.player);
            if(new_pos.cnt != self.cnt - iAmFirst)
                new_dir = (new_dir+3) % dir::N;
        }

        return new_dir;
    }

    std::string name() const {
        return "FS GODZILLA";
    }
};

#endif //FRASCHS_HEADER
