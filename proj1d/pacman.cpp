// Pacman Class Implementation
// pacman.cpp
// purpose: This class is responsible for setting the location of the Pac-Man 
// character, moving and placing it on the board, and determining if it is alive
// or not. All of the moving logic happens inside the class. This includes going
// through walls and not going through boulders.
// By Haomin Feng
// March 29 2016

#include <iostream>
using namespace std;

#include "termfuncs.h"
#include "constants.h"
#include "pacman.h"

// pacman constructor
// purpose: initialize the private members of the Pacman class
// arguments: none
// returns: none
Pacman::Pacman()
{
        alive = true;
        head = SPACE;
        num_moves = 0;
        score = 0;
        row = 0; 
        col = 0;
        center();
}

// center
// purpose: change Pacman's location to be the center of the board, and faces 
// Pacman up
// arguments: none
// returns: none
void Pacman::center()
{
        row = ROWS/2;
        col = COLS/2;
        head = UP;
}

// move
// purpose: move pacman based on an input command which wraps Pacman across the 
// borders of the board. If Pacman runs into a GHOST character, this sets Pacman
// to not be alive. If Pacman attempts to move into a BOULDER character, Pacman 
// does not move.
// arguments: a 2D array of board and a char command
// returns: true/false
bool Pacman::move(char board[ROWS][COLS], char command)
{
        int old_row = row;
        int old_col = col;
        move_head(command);
        cross_border();
        if (board[row][col] == GHOST){ // die if run into a ghost
                alive = false; 
        }                                       
        if (board[row][col] == BOULDER){ // cannot cross boulders
                row = old_row;
                col = old_col;
        }
        if (board[row][col] == DOT){ // determine if a dot is eaten
                return true;
        }
        return false;
}       

// move_head
// purpose: move pacman based on an input command
// arguments: a char command
// returns: none        
void Pacman::move_head(char command)
{        
        if (command == CMD_LFT){
                head = LEFT;
                col--;
        }
        if (command == CMD_RGT){
                head = RIGHT;
                col++;
        }
        if (command == CMD_UP){
                head = UP;
                row--;
        }
        if (command == CMD_DWN){
                head = DOWN;
                row++;
        }
}

// cross_border
// purpose: enable Pacman to cross borders
// arguments: none
// returns: none
void Pacman::cross_border()
{
        if (row < 0){
                row = ROWS-1;
        }
        if (row == ROWS){
                row = 0;
        }
        if (col < 0){
                col = COLS-1;
        }
        if (col == COLS){
                col = 0;
        }
} 

// place_on_board
// purpose: place Pacman on the board, at Pacman's location 
// arguments: a 2D array of board
// returns: none
void Pacman::place_on_board(char board[ROWS][COLS])
{
        board[row][col] = head;
}

// get_num_moves
// purpose: return the number of moves Pacman has made
// arguments: none
// returns: an integer of num_moves
int Pacman::get_num_moves()
{
        num_moves++;
        return num_moves;
}

// set_col
// purpose: location setter
// arguments: an integer of c 
// returns: none
void Pacman::set_col(int c)
{
        col = c;
}

// set_row
// purpose: location setter
// arguments: an integer of r
// returns: none
void Pacman::set_row(int r)
{
        row = r;
}

// get_col
// purpose: location setter
// arguments: none
// returns: an integer of col
int Pacman:: get_col()
{
        return col;
}

// get_row
// purpose: location setter    
// arguments: none  
// returns: an integer of row       
int Pacman::get_row()
{
        return row;
}


// is_at
// purpose: return if the Pacman is at this row and col
// arguments: none
// returns: true/false
bool Pacman::is_at(int r, int c)
{
        if (row == r and col == c){
                return true;
        }
        else{
                return false;
        }
}

// add_to_score
// purpose: take an integer n, and adds n to the Pacman's score
// arguments: an integer of n
// returns: none
void Pacman::add_to_score(int n)
{
        score = score + n;
}

// get_score
// purpose: return the Pacman's score
// arguments: none
// returns: an integer of socre
int Pacman::get_score()
{
        return score;
}

// die
// purpose: kill Pacman
// arguments: none
// returns: none
void Pacman::die()
{
        alive = false;
}

// is_alive
// purpose: returns true if Pacman is alive, false otherwise
// arguments: none
// returns: a bool value of alive
bool Pacman::is_alive()
{
        return alive;
}





