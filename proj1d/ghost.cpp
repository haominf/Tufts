// Ghost Class Implementation
// ghost.cpp
// purpose: This class is responsible for placing a ghost on the board and 
// moving it closer to the Pac-Man.
// By Haomin Feng
// March 30 2016

#include <iostream> 
using namespace std;    

#include "termfuncs.h"  
#include "constants.h"  
#include "ghost.h"
#include <cmath>

// Constructor
Ghost::Ghost()
{
        row = 0;
        col = 0;
}

// set_location
// purpose: for initializing location
// arguments: two integers of row and col
// returns: none
void Ghost::set_location(int r, int c)
{
        row = r;
        col = c;
}

// move
// purpose: move the ghost towards the given target (row and column). ghosts can
// move through anything on the board, but they cannot move through walls.
// arguments: a 2D char array, two integers of target_r and target_c
// returns: true/false
bool Ghost::move(char board[ROWS][COLS], int target_r, int target_c)
{
        int old_row = row;  
        int old_col = col;         
        how_to_move(target_r, target_c);
        if (board[row][col] == GHOST){
                row = old_row; 
                col = old_col;  
        }
        if (row == target_r and col == target_c){
                return true;
        }
        else{
                return false;
        }
}

// place_on_board
// purpose: places the ghost on the given board, at its location
// arguments: none
// returns: none
void Ghost::place_on_board(char board[ROWS][COLS])
{
        board[row][col] = GHOST;
}

// is_at
// purpose: return true if the ghost is at this row and column, false otherwise
// arguments: two integers of r and c
// returns: true/false
bool Ghost::is_at(int r, int c)
{
        if (row == r and col == c){
                return true;
        }
        else{
                return false;
        }
}

// how_to_move
// purpose: tell ghosts how to move towards the target
// arguments: none
// returns: none
void Ghost::how_to_move(int target_r, int target_c)
{
        int diff_col = abs(target_c - col); 
        int diff_row = abs(target_r - row);     
        if (diff_col > diff_row){
                if ((target_c - col) > 0){
                        col++;
                }
                else{
                        col--;
                }
        }
        else{
                if ((target_r - row) > 0){
                        row++;
                }
                else{
                        row--;
                }
        }
}
