// Author:  Mario S. Könz <mskoenz@gmx.net>
// Date:    18.11.2015 09:38:16 CET
// File:    greschd.hpp

#ifndef GRESCHD_HEADER
#define GRESCHD_HEADER

// as the name suggests...
struct ultimate_camper {
    dir::type move(
        int const &,
        std::array<field_type, dir::N> const & fields,
        field_type const & my_field,
        std::mt19937 &
    ) {
        // catch
        for(int i = 0; i < dir::N; ++i) {
            if(
                (fields[i].cnt >= my_field.cnt - 1 + my_field.player) &&
                (fields[i].player != my_field.player) &&
                (fields[i].player != no_player)
            ) {
                return i;
            }
        }
        // run
        for(int i = 0; i < dir::N; ++i) {
            if(
                (fields[i].cnt >= my_field.cnt - 2 + my_field.player) &&
                (fields[i].player != my_field.player) &&
                (fields[i].player != no_player)
            ) {
                return (i + dir::N / 2) % dir::N;
            }
        }
        if(my_field.cnt % 2 == 0) {
            return dir::right;
        }
        return dir::left;
    }

    std::string name() const {
        return "GD ultimate camper";
    }
};

// a little less lazy
struct wandering_camper {
    dir::type move(
        int const &,
        std::array<field_type, dir::N> const & fields,
        field_type const & my_field,
        std::mt19937 & eng
    ) {
        // catch
        for(int i = 0; i < dir::N; ++i) {
            if(
                (fields[i].cnt >= my_field.cnt - 1 + my_field.player) &&
                (fields[i].player != my_field.player) &&
                (fields[i].player != no_player)
            ) {
                return i;
            }
        }
        // run
        for(int i = 0; i < dir::N; ++i) {
            if(
                (fields[i].cnt >= my_field.cnt - 2 + my_field.player) &&
                (fields[i].player != my_field.player) &&
                (fields[i].player != no_player)
            ) {
                return (i + dir::N / 2) % dir::N;
            }
        }
        // figure out where I came from
        int my_origin = 0;
        for(int i = 0; i < dir::N; ++i) {
            if(
                (fields[i].player == my_field.player) &&
                (fields[i].cnt == my_field.cnt - 1)
            ) {
                my_origin = i;
                break;
            }
        }
        // move either to the left or the right of where I came from
        std::uniform_real_distribution<> dist(0, 1);
        if(dist(eng) < 0.5) {
            //~ std::cout << (my_origin + 1 + dir::N) % dir::N << std::endl;
            return (my_origin + 1 + dir::N) % dir::N;
        }
        else {
            //~ std::cout << (my_origin - 1 + dir::N) % dir::N << std::endl;
            return (my_origin - 1 + dir::N) % dir::N;
        }
    }

    std::string name() const {
        return "GD wandering camper";
    }
};

// a little less lazy
struct random_camper {
    dir::type move(
        int const &,
        std::array<field_type, dir::N> const & fields,
        field_type const & my_field,
        std::mt19937 & eng
    ) {
        // catch
        for(int i = 0; i < dir::N; ++i) {
            if(
                (fields[i].cnt >= my_field.cnt - 1 + my_field.player) &&
                (fields[i].player != my_field.player) &&
                (fields[i].player != no_player)
            ) {
                return i;
            }
        }
        // run
        for(int i = 0; i < dir::N; ++i) {
            if(
                (fields[i].cnt >= my_field.cnt - 2 + my_field.player) &&
                (fields[i].player != my_field.player) &&
                (fields[i].player != no_player)
            ) {
                return (i + dir::N / 2) % dir::N;
            }
        }
        return eng() % dir::N;
    }

    std::string name() const {
        return "GD random camper";
    }
};

#endif //GRESCHD_HEADER
