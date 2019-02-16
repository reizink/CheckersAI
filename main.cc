//Reilly Zink
// 4/7/17

#include<iostream>
#include<string>
#include<cctype>
#include"game.h"
#include"checkers.h"
#include"space.h"
#include"colors.h"
using namespace std;
using namespace main_savitch_14;


int main(){
    
    game *x;
    x = new Checkers;
    x->play();

    return 0;
}
