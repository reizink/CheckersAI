//Reilly Zink

#ifndef SPACE_H
#define SPACE_H

#include<iostream>
using namespace std;

namespace main_savitch_14{
class space{
    public:
        space(){playable = false; piece = ' ';}
        bool is_empty()const;
        bool is_red()const;
        bool is_black()const;
        bool is_playable()const;
        bool is_king()const;
        void king_me();
        char get_piece()const;
        bool get_playable()const;
        void set_black();
        void set_red();
        void set_playable();
        void set_unplayable();
        void set_empty();

    private:
        bool playable;
        char piece;

        

};
}

#endif