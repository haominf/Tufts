// Dot Class Implementation
// dot.cpp
// purpose: the full implementation of the Dot class:
// This class represents the dots onto the board. The coordinates of a dot is 
// randomly generated, but it cannot overlap boulders. A dot can printed on the 
// board
// By Haomin Feng
// March 27 2016

#include <iostream>
using namespace std;

#include "termfuncs.h"
#include "constants.h"
#include "dot.h"

// dot constructor
// purpose: initialize private members
// arguments: none
// returns: none
Dot::Dot()
{
        row = 0;
        col = 0;
        eaten = false;
}

// set_random_location
// purpose: choose a random location for the dot on the board
// arguments: 2D array of board
// returns: none
void Dot::set_random_location(char board[ROWS][COLS])
{
        row = random_int(0,ROWS-1);
        col = random_int(0,COLS-1);
        while (board[row][col] != SPACE){
                row = random_int(0,ROWS-1);
                col = random_int(0,COLS-1);
        }
}

// place_on_board
// purpose: place the dot on the board, at its location
// arguments: 2D array of board
// returns: none
void Dot::place_on_board(char board[ROWS][COLS])
{
        if (eaten == false){
                board[row][col] = DOT;
        }
}

// is_at
// purpose: return if the dot is at this row and col
// arguments: two integers
// returns: true/false
bool Dot::is_at(int r, int c)
{
        if (row == r and col == c) {
                return true;
        }
        else {
                return false;
        }
}

// set_eaten
// purpose: set eaten to be the passed-in bool
// arguments: a boolean value
// returns: none
void Dot::set_eaten(bool isEaten)
{
        eaten = isEaten;
}

// was_eaten
// purpose: return if the dot has been eaten
// arguments: none
// returns: boolean value of eaten
bool Dot::was_eaten()
{
        return eaten;
}
