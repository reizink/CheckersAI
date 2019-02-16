//Reilly Zink
// 4/7/17

#include<iostream>
#include<string>
#include"game.h"
#include"space.h"
#include"colors.h"
#include"checkers.h"
using namespace std;
using namespace main_savitch_14;

void space::king_me(){
    if(piece == 'r')
        piece = 'R';
    else if(piece == 'b') //black
        piece = 'B';
}

bool space::is_king()const{
    if(piece == 'R' || piece == 'B'){
        return true;
    }
    else
        return false;
}

bool space::is_empty()const{
    if(piece == ' ')
        return true;
    else 
        return false;
}

bool space::is_red()const{
    if(piece == 'r' || piece == 'R')
        return true;
    else
        return false;
}

bool space::is_black()const{
    if(piece == 'b' || piece == 'B')
        return true;
    else
        return false;
}

bool space::is_playable()const{
        return playable; 
}

char space::get_piece()const{
    return piece;
}

bool space::get_playable()const{
    return playable;
}
void space::set_black(){
    piece = 'b';
}

void space::set_red(){
    piece = 'r';
}

void space::set_empty(){
    piece = ' ';
}

void space::set_playable(){
        playable = true;
}

void space::set_unplayable(){
        playable = false;
}