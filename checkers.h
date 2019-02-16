//Reilly Zink

#ifndef CHECKERS_H
#define CHECKERS_H

#include<iostream>
#include<string>
#include"space.h"
#include"game.h"
using namespace std;

namespace main_savitch_14{
class Checkers: public game{
    public:
        Checkers();
        void restart();
        void display_status()const;
        bool is_legal(const std::string& move)const;
        void make_move(const std::string& move);
        bool is_game_over() const; 
        //string get_user_move() const;
        game* clone()const;
        void compute_moves(std::queue<std::string>& moves)const;
        int evaluate()const;
        game::who winning( ) const;
    private:
        space board[8][8];
        //string move;
};
}

#endif


