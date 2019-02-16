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


Checkers::Checkers(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i %2 == 0 && j %2 == 1) || (i %2 == 1 && j %2 == 0)){
                board[i][j].set_playable();
            }
            else board[i][j].set_unplayable();
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 8; j++){
            if( (i == 0 || i == 2) && (j %2 == 1))
                board[i][j].set_black();
            else if((i == 1) && (j %2 == 0))
                board[i][j].set_black();
            else
                board[i][j].set_empty();
        }
    }
    for(int i = 5; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if( (i == 5 || i == 7) && (j %2 == 0))
                board[i][j].set_red();
            else if((i == 6) && (j %2 == 1))
                board[i][j].set_red();
            else
                board[i][j].set_empty();
        }
    }
}

void Checkers::display_status()const{
    display_message("\nMove example: a6b5 \n\n");

    cout<< "  / A  / B  / C  / D  / E  / F  / G  / H  " << endl;
    for(int i = 0; i < 8; i++){
        if(i%2 == 0) cout<< "  " << B_MAGENTA << "     "<< RESET << B_WHITE << "     "<< RESET << B_MAGENTA << "     "<< RESET << B_WHITE << "     "<< RESET << B_MAGENTA << "     "<< RESET << B_WHITE << "     "<< RESET << B_MAGENTA << "     "<< RESET << B_WHITE << "     "<< RESET << " | " << endl;
        if(i%2 == 1) cout<< "  " << B_WHITE << "     "<< RESET << B_MAGENTA << "     "<< RESET << B_WHITE << "     "<< RESET << B_MAGENTA << "     "<< RESET << B_WHITE << "     "<< RESET << B_MAGENTA << "     "<< RESET << B_WHITE << "     "<< RESET << B_MAGENTA << "     "<< RESET << " | " << endl;
        cout<< i+1 << " ";
        for(int j = 0; j < 8; j++){
            if(board[i][j].is_empty()){
                if (board[i][j].is_playable()){
                    cout<< B_WHITE << "     "<< RESET;
                }
                else{
                    cout<< B_MAGENTA << "     "<< RESET;
                }
                
            }
            else{
                if(board[i][j].is_red()){
                    cout<<B_WHITE<<RED<< "  " << board[i][j].get_piece() << "  "<< RESET;
                }
                else{
                    cout<<B_WHITE<<BLACK<< "  " << board[i][j].get_piece() << "  " << RESET;
                }
            } 
        }
        cout<< " | " << endl;
    }
    cout<< "  ------------------------------------------" << endl << endl;
}

bool Checkers::is_legal(const std::string& move)const{
    int col, row, newc, newr;

    col = int(tolower(move[0]) - 'a');
    row = int(move[1] - '1');
    newc = int(tolower(move[2]) - 'a');
    newr = int(move[3] - '1');


    if( board[row][col].is_empty() || board[row][col].is_playable() == 0 || board[newr][newc].is_playable() == 0 ){
        return false;
    }
    else if( col < 0 || col > 7 || row < 0 || row > 7 || newc < 0 || newc > 7 || newr < 0 || newr > 7 ){
        return false;
    }
    else if( board[newr][newc].is_empty() == 0){ 
        return false;
    }
    else if( next_mover() == COMPUTER && board[row][col].is_red()){ //comp trying to move human piece
        return false;
    }
    else if( next_mover() == HUMAN && board[row][col].is_black()){ //human trying to move comp
        return false;
    }
    else{ // 
        if( next_mover() == HUMAN && board[row][col].is_red() && board[row][col].is_king() == false){ //move up if not king
            if( row - 1 == newr && (col + 1 == newc || col - 1 == newc )){
                return true;
            }
            else if( (row - 2 == newr &&  col - 2 == newc ) && board[row-1][col-1].is_black()){ //single jump
                return true;
            }
            else if( (row - 2 == newr &&  col + 2 == newc ) && board[row-1][col+1].is_black()){ //single jump
                return true;
            }
            else if( (row - 4 == newr &&  col - 4 == newc ) && board[row-1][col-1].is_black() && board[row-3][col-3].is_black() && board[row-2][col-2].is_empty()){ //double jump
                return true;
            }
            else if( (row - 4 == newr &&  col + 4 == newc ) && board[row-1][col+1].is_black() && board[row-3][col+3].is_black() && board[row-2][col+2].is_empty()){ //double jump
                return true;
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col+1].is_black() && board[row-3][col+1].is_black() && board[row-2][col+2].is_empty()){ //double jump
                return true;
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col-1].is_black() && board[row-3][col-1].is_black() && board[row-2][col-2].is_empty()){ //double jump
                return true;
            }
            else
                return false;
        } //
        else if( next_mover() == COMPUTER && board[row][col].is_black() && board[row][col].is_king() == false){ //move down if not king
            if( row + 1 == newr && (col + 1 == newc || col - 1 == newc )){
                return true;
            }
            else if( (row + 2 == newr &&  col - 2 == newc ) && board[row+1][col-1].is_red()){ //single jump
                return true;
            }
            else if( (row + 2 == newr &&  col + 2 == newc ) && board[row+1][col+1].is_red()){ //single jump
                return true;
            }
            else if( (row + 4 == newr &&  col - 4 == newc ) && board[row+1][col-1].is_red() && board[row+3][col-3].is_red() && board[row+2][col-2].is_empty()){ //double jump
                return true;
            }
            else if( (row + 4 == newr &&  col + 4 == newc ) && board[row+1][col+1].is_red() && board[row+3][col+3].is_red() && board[row+2][col+2].is_empty()){ //double jump
                return true;
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col+1].is_red() && board[row+3][col+1].is_red() && board[row+2][col+2].is_empty()){ //double jump
                return true;
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col-1].is_red() && board[row+3][col-1].is_red() && board[row+2][col-2].is_empty()){ //double jump
                return true;
            }
            else
                return false;
        }
        else{ // king moves both ways
            if(board[row][col].is_red()){
                if( row - 1 == newr && (col + 1 == newc || col - 1 == newc )){
                    return true;
                }
                else if( (row - 2 == newr &&  col - 2 == newc ) && board[row-1][col-1].is_black()){ //single jump
                    return true;
                }
                else if( (row - 2 == newr &&  col + 2 == newc ) && board[row-1][col+1].is_black()){ //single jump
                    return true;
                }
                else if( (row - 4 == newr &&  col - 4 == newc ) && board[row-1][col-1].is_black() && board[row-3][col-3].is_black() && board[row-2][col-2].is_empty()){ //double jump
                    return true;
                }
                else if( (row - 4 == newr &&  col + 4 == newc ) && board[row-1][col+1].is_black() && board[row-3][col+3].is_black() && board[row-2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row - 4 == newr &&  col == newc ) && board[row-1][col+1].is_black() && board[row-3][col+1].is_black() && board[row-2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row - 4 == newr &&  col == newc ) && board[row-1][col-1].is_black() && board[row-3][col-1].is_black() && board[row-2][col-2].is_empty()){ //double jump
                    return true;
                }
                else if( row + 1 == newr && (col + 1 == newc || col - 1 == newc )){
                    return true;
                }
                else if( (row + 2 == newr &&  col - 2 == newc ) && board[row+1][col-1].is_black()){ //single jump
                    return true;
                }
                else if( (row + 2 == newr &&  col + 2 == newc ) && board[row+1][col+1].is_black()){ //single jump
                    return true;
                }
                else if( (row + 4 == newr &&  col - 4 == newc ) && board[row+1][col-1].is_black() && board[row+3][col-3].is_black() && board[row+2][col-2].is_empty()){ //double jump
                    return true;
                }
                else if( (row + 4 == newr &&  col + 4 == newc ) && board[row+1][col+1].is_black() && board[row+3][col+3].is_black() && board[row+2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row + 4 == newr &&  col == newc ) && board[row+1][col+1].is_black() && board[row+3][col+1].is_black() && board[row+2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row + 4 == newr &&  col == newc ) && board[row+1][col-1].is_black() && board[row+3][col-1].is_black() && board[row+2][col-2].is_empty()){ //double jump
                    return true;
                }
                else
                    return false;
            }
            else{ //black king
                if( row - 1 == newr && (col + 1 == newc || col - 1 == newc )){
                    return true;
                }
                else if( (row - 2 == newr &&  col - 2 == newc ) && board[row-1][col-1].is_red()){ //single jump
                    return true;
                }
                else if( (row - 2 == newr &&  col + 2 == newc ) && board[row-1][col+1].is_red()){ //single jump
                    return true;
                }
                else if( (row - 4 == newr &&  col - 4 == newc ) && board[row-1][col-1].is_red() && board[row-3][col-3].is_red() && board[row-2][col-2].is_empty()){ //double jump
                    return true;
                }
                else if( (row - 4 == newr &&  col + 4 == newc ) && board[row-1][col+1].is_red() && board[row-3][col+3].is_red() && board[row-2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row - 4 == newr &&  col == newc ) && board[row-1][col+1].is_red() && board[row-3][col+1].is_red() && board[row-2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row - 4 == newr &&  col == newc ) && board[row-1][col-1].is_red() && board[row-3][col-1].is_red() && board[row-2][col-2].is_empty()){ //double jump
                    return true;
                }
                else if( row + 1 == newr && (col + 1 == newc || col - 1 == newc )){
                    return true;
                }
                else if( (row + 2 == newr &&  col - 2 == newc ) && board[row+1][col-1].is_red()){ //single jump
                    return true;
                }
                else if( (row + 2 == newr &&  col + 2 == newc ) && board[row+1][col+1].is_red()){ //single jump
                    return true;
                }
                else if( (row + 4 == newr &&  col - 4 == newc ) && board[row+1][col-1].is_red() && board[row+3][col-3].is_red() && board[row+2][col-2].is_empty()){ //double jump
                    return true;
                }
                else if( (row + 4 == newr &&  col + 4 == newc ) && board[row+1][col+1].is_red() && board[row+3][col+3].is_red() && board[row+2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row + 4 == newr &&  col == newc ) && board[row+1][col+1].is_red() && board[row+3][col+1].is_red() && board[row+2][col+2].is_empty()){ //double jump
                    return true;
                }
                else if( (row + 4 == newr &&  col == newc ) && board[row+1][col-1].is_red() && board[row+3][col-1].is_red() && board[row+2][col-2].is_empty()){ //double jump
                    return true;
                }
                else
                    return false;
            }
        } //end king
    } //end else
 }

void Checkers::restart(){ 
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i %2 == 0 && j %2 == 1) || (i %2 == 1 && j %2 == 0)){
                board[i][j].set_playable();
            }
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 8; j++){
            if( (i == 0 || i == 2) && (j %2 == 1))
                board[i][j].set_black();
            else
                board[i][j].set_empty();
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 8; j++){
            if( (i == 0 || i == 2) && (j %2 == 1))
                board[i][j].set_black();
            else if((i == 1) && (j %2 == 0))
                board[i][j].set_black();
            else
                board[i][j].set_empty();
        }
    }
    for(int i = 5; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if( (i == 5 || i == 7) && (j %2 == 0))
                board[i][j].set_red();
            else if((i == 6) && (j %2 == 1))
                board[i][j].set_red();
            else
                board[i][j].set_empty();
        }
    }

    game::restart();
}

void Checkers::make_move(const std::string& move){
    int col, row, newc, newr;

    col = int(tolower(move[0]) - 'a');
    row = int(move[1] - '1');
    newc = int(tolower(move[2]) - 'a');
    newr = int(move[3] - '1');

    if( board[row][col].is_king() == 0){ // not a king
        if(board[row][col].is_black() ){
            board[newr][newc].set_black(); //black
            if( (row + 2 == newr &&  col - 2 == newc ) && board[row+1][col-1].is_red()){ //single jump
                board[row+1][col-1].set_empty(); // jump down left
            }
            else if( (row + 2 == newr &&  col + 2 == newc ) && board[row+1][col+1].is_red()){ //single jump
                board[row+1][col+1].set_empty(); // jump down right
            }
            else if( (row + 4 == newr &&  col - 4 == newc ) && board[row+1][col-1].is_red() && board[row+3][col-3].is_red() && board[row+2][col-2].is_empty()){ //double jump
                board[row+1][col-1].set_empty();
                board[row+3][col-3].set_empty();
            }
            else if( (row + 4 == newr &&  col + 4 == newc ) && board[row+1][col+1].is_red() && board[row+3][col+3].is_red() && board[row+2][col+2].is_empty()){ //double jump
                board[row+1][col+1].set_empty();
                board[row+3][col+3].set_empty();
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col+1].is_red() && board[row+3][col+1].is_red() && board[row+2][col+2].is_empty()){ //double jump
                board[row+1][col+1].set_empty();
                board[row+3][col+1].set_empty();
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col-1].is_red() && board[row+3][col-1].is_red() && board[row+2][col-2].is_empty()){ //double jump
                board[row+1][col-1].set_empty();
                board[row+3][col-1].set_empty();
            }
        }
        else{
            board[newr][newc].set_red(); //red
            if( (row - 2 == newr &&  col - 2 == newc ) && board[row-1][col-1].is_black()){ //single jump
                board[row-1][col-1].set_empty(); // jump up left
            }
            else if( (row - 2 == newr &&  col + 2 == newc ) && board[row-1][col+1].is_black()){ //single jump
                board[row-1][col+1].set_empty(); // jump up right
            }
            else if( (row - 4 == newr &&  col - 4 == newc ) && board[row-1][col-1].is_black() && board[row-3][col-3].is_black() && board[row-2][col-2].is_empty()){ //double jump
                board[row-1][col-1].set_empty();
                board[row-3][col-3].set_empty();
            }
            else if( (row - 4 == newr &&  col + 4 == newc ) && board[row-1][col+1].is_black() && board[row-3][col+3].is_black() && board[row-2][col+2].is_empty()){ //double jump
                board[row-1][col+1].set_empty();
                board[row-3][col+3].set_empty();
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col+1].is_black() && board[row-3][col+1].is_black() && board[row-2][col+2].is_empty()){ //double jump
                board[row-1][col+1].set_empty();
                board[row-3][col+1].set_empty();
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col-1].is_black() && board[row-3][col-1].is_black() && board[row-2][col-2].is_empty()){ //double jump
                board[row-1][col-1].set_empty();
                board[row-3][col-1].set_empty();
            }
        }
    } //end of not king
    else{ //is_king
        if(board[row][col].is_black() ){
            board[newr][newc].set_black(); //black
            board[newr][newc].king_me();
            if( (row + 2 == newr &&  col - 2 == newc ) && board[row+1][col-1].is_red()){ //single jump
                board[row+1][col-1].set_empty(); // jump down left
            }
            else if( (row + 2 == newr &&  col + 2 == newc ) && board[row+1][col+1].is_red()){ //single jump
                board[row+1][col+1].set_empty(); // jump down right
            }
            else if( (row + 4 == newr &&  col - 4 == newc ) && board[row+1][col-1].is_red() && board[row+3][col-3].is_red() && board[row+2][col-2].is_empty()){ //double jump
                board[row+1][col-1].set_empty();
                board[row+3][col-3].set_empty();
            }
            else if( (row + 4 == newr &&  col + 4 == newc ) && board[row+1][col+1].is_red() && board[row+3][col+3].is_red() && board[row+2][col+2].is_empty()){ //double jump
                board[row+1][col+1].set_empty();
                board[row+3][col+3].set_empty();
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col+1].is_red() && board[row+3][col+1].is_red() && board[row+2][col+2].is_empty()){ //double jump
                board[row+1][col+1].set_empty();
                board[row+3][col+1].set_empty();
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col-1].is_red() && board[row+3][col-1].is_red() && board[row+2][col-2].is_empty()){ //double jump
                board[row+1][col-1].set_empty();
                board[row+3][col-1].set_empty();
            }
            else if( (row - 2 == newr &&  col - 2 == newc ) && board[row-1][col-1].is_red()){ //single jump
                board[row-1][col-1].set_empty(); // jump up left
            }
            else if( (row - 2 == newr &&  col + 2 == newc ) && board[row-1][col+1].is_red()){ //single jump
                board[row-1][col+1].set_empty(); // jump up right
            }
            else if( (row - 4 == newr &&  col - 4 == newc ) && board[row-1][col-1].is_red() && board[row-3][col-3].is_red() && board[row-2][col-2].is_empty()){ //double jump
                board[row-1][col-1].set_empty();
                board[row-3][col-3].set_empty();
            }
            else if( (row - 4 == newr &&  col + 4 == newc ) && board[row-1][col+1].is_red() && board[row-3][col+3].is_red() && board[row-2][col+2].is_empty()){ //double jump
                board[row-1][col+1].set_empty();
                board[row-3][col+3].set_empty();
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col+1].is_red() && board[row-3][col+1].is_red() && board[row-2][col+2].is_empty()){ //double jump
                board[row-1][col+1].set_empty();
                board[row-3][col+1].set_empty();
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col-1].is_red() && board[row-3][col-1].is_red() && board[row-2][col-2].is_empty()){ //double jump
                board[row-1][col-1].set_empty();
                board[row-3][col-1].set_empty();
            }
        }
        else{
            board[newr][newc].set_red(); //red
            board[newr][newc].king_me();
            if( (row - 2 == newr &&  col - 2 == newc ) && board[row-1][col-1].is_black()){ //single jump
                board[row-1][col-1].set_empty(); // jump up left
            }
            else if( (row - 2 == newr &&  col + 2 == newc ) && board[row-1][col+1].is_black()){ //single jump
                board[row-1][col+1].set_empty(); // jump up right
            }
            else if( (row - 4 == newr &&  col - 4 == newc ) && board[row-1][col-1].is_black() && board[row-3][col-3].is_black() && board[row-2][col-2].is_empty()){ //double jump
                board[row-1][col-1].set_empty();
                board[row-3][col-3].set_empty();
            }
            else if( (row - 4 == newr &&  col + 4 == newc ) && board[row-1][col+1].is_black() && board[row-3][col+3].is_black() && board[row-2][col+2].is_empty()){ //double jump
                board[row-1][col+1].set_empty();
                board[row-3][col+3].set_empty();
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col+1].is_black() && board[row-3][col+1].is_black() && board[row-2][col+2].is_empty()){ //double jump
                board[row-1][col+1].set_empty();
                board[row-3][col+1].set_empty();
            }
            else if( (row - 4 == newr &&  col == newc ) && board[row-1][col-1].is_black() && board[row-3][col-1].is_black() && board[row-2][col-2].is_empty()){ //double jump
                board[row-1][col-1].set_empty();
                board[row-3][col-1].set_empty();
            }
            else if( (row + 2 == newr &&  col - 2 == newc ) && board[row+1][col-1].is_black()){ //single jump
                board[row+1][col-1].set_empty(); // jump down left
            }
            else if( (row + 2 == newr &&  col + 2 == newc ) && board[row+1][col+1].is_black()){ //single jump
                board[row+1][col+1].set_empty(); // jump down right
            }
            else if( (row + 4 == newr &&  col - 4 == newc ) && board[row+1][col-1].is_black() && board[row+3][col-3].is_black() && board[row+2][col-2].is_empty()){ //double jump
                board[row+1][col-1].set_empty();
                board[row+3][col-3].set_empty();
            }
            else if( (row + 4 == newr &&  col + 4 == newc ) && board[row+1][col+1].is_black() && board[row+3][col+3].is_black() && board[row+2][col+2].is_empty()){ //double jump
                board[row+1][col+1].set_empty();
                board[row+3][col+3].set_empty();
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col+1].is_black() && board[row+3][col+1].is_black() && board[row+2][col+2].is_empty()){ //double jump
                board[row+1][col+1].set_empty();
                board[row+3][col+1].set_empty();
            }
            else if( (row + 4 == newr &&  col == newc ) && board[row+1][col-1].is_black() && board[row+3][col-1].is_black() && board[row+2][col-2].is_empty()){ //double jump
                board[row+1][col-1].set_empty();
                board[row+3][col-1].set_empty();
            }
        }
    }
    board[row][col].set_empty();

    if(board[newr][newc].is_black() && newr == 7 ) board[newr][newc].king_me();
    else if(board[newr][newc].is_red() && newr == 0 ) board[newr][newc].king_me();

    game::make_move(move);
}

bool Checkers::is_game_over( ) const{
   int countr = 0;
   int countb = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j].is_red()){
                countr++;
            }
            else if(board[i][j].is_black()){
                countb++;
            } 
        }
    }
   
   if( countr == 0 ){
        cout<< "\nBLACK WINS!!";
        return true;
    }
    else if( countb == 0 ){
        cout<< "\nRED WINS!!";
        return true;
    }
    else
        return false;
}

/*string Checkers::get_user_move() const{
    string x;
    cout<<"Your move, please: ";
    cin>> x;

    if(is_legal(x)) return x;
    else{
        cout<<"Invalid.\n";
        get_user_move();
    }
}*/

game* Checkers::clone()const{
    return new Checkers (*this);
}

void Checkers::compute_moves(std::queue<std::string>& moves)const{
    string pmove = "    ";
    char col, row, newc, newr;

    for(row = '1'; row <= '8'; row++){
        for(col = 'a'; col <= 'h'; col++){
            for(newr = '1'; newr <= '8'; newr++){
                for(newc = 'a'; newc <= 'h'; newc++){
                        pmove[0] = col;
                        pmove[1] = row;
                        pmove[2] = newc;
                        pmove[3] = newr;
                        if(is_legal(pmove))
                            moves.push(pmove);
                } // move [3], newc
            } //newr
        } // [1], col
    } //move [0], row

}

int Checkers::evaluate()const{
    int countr = 0;
    int countb = 0;
    int eval;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j].is_red()){
                countr++;
            }
            else if(board[i][j].is_black()){
                countb++;
            } 
        }
    }

    eval = countb - countr;

    return eval;
}

game::who Checkers::winning( ) const{
    int countr = 0;
    int countb = 0;
    int eval;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j].is_red()){
                countr++;
            }
            else if(board[i][j].is_black()){
                countb++;
            } 
        }
    }

    eval = countb - countr;

    if (eval > 0) //computer, last
        return COMPUTER;
    else if (eval < 0) //human, next
        return HUMAN;
    else
        return NEUTRAL;
}
