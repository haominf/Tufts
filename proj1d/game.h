/*******************************************************************************
 * Game Class Interface                                                        *
 * For Pacman Game (COMP 11 Project 1 | 2016 Spring)                           *
 ******************************************************************************/

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "constants.h"
#include "pacman.h"
#include "ghost.h"
#include "dot.h"
#include "boulder.h"

class Game {
        public:
                Game();

                // prints the manual and stalls until the user types a character
                void print_manual();

                // Runs the Pacman game!
                void run();
        private:
                char board[ROWS][COLS];
                void setup_board();
                void print_board();
                void put_boulder();
                void put_dot();
                void set_location_d();
                void put_pman();
                void set_location_g();
                void put_ghost();
                void dot_eaten();
                bool check_dots();
                void next_level();
                void setup_game();
                void print_lose();
                void set_level();
                void score_dot(bool);
                void score_level();
                void replace_pman();
                Pacman p;
                Ghost ghosts[NUM_GHOSTS];
                Dot dots[NUM_DOTS];
                Boulder boulders[NUM_BOULDERS];
                char command;
                int level;
                int num_moves; // number of moves of pacman
                void move_ghost();
		void display_score();
};

#endif
