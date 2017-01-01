// game.cpp
// purpose: This class contains all of the objects that game needs (Pacman, 
// Ghosts, Dots, Boulders) and places them on the board. This class also runs 
// the gameplay.
// By Haomin Feng
// April 3 2016
/*******************************************************************************
 * Game Class Implementation                                                   *
 * For Pacman Game (COMP 11 Project 1 | 2016 Spring)                           *
 *****************************************************************************/

#include <iostream>
using namespace std;

#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "dot.h"
#include "termfuncs.h"


/* Constructor */
Game::Game()
{
        level = 10; // start with level 1
        num_moves = 0;
}

/* print_manual()
 * Purpose:   Prints the manual and stalls until the user types a character
 * Arguments: None
 * Returns:   None
 */
void Game::print_manual()
{
        screen_clear();
        cout << "PACMAN GAME\n"
                "            \n"
                " Move left:    " << CMD_LFT << "\n"
                " Move right:   " << CMD_RGT << "\n"
                " Move up:      " << CMD_UP  << "\n"
                " Move down:    " << CMD_DWN << "\n"
                "\n"
                " Collect all the dots. They look like: " << DOT << "\n"
                " Avoid the ghosts.     They look like: " << GHOST << "\n"
                "\n"
                " Good luck!\n"
                "\n"
                " Press any key to continue...\n";

        getachar();
}

// setup_game
// purpose: set up the initial conditions
// arguments: none
// returns: none
void Game::setup_game()
{
        screen_clear(); // clear terminal
        setup_board();
        set_level();
        p.center(); // re-center pacman in the next level
        put_boulder();
        put_pman();
        set_location_d();
        put_dot();
        set_location_g();
        put_ghost();
        print_board(); // before game starts. board should be displayed
        //before "cout"  
        cout<<"Level "<<level<<": Press any key to start"<<endl;
        getachar();
}

// run
// purpose: run the game
void Game::run()
{
        setup_game();
        while (p.is_alive() == true and check_dots() == false) {
                screen_clear(); // clear terminal
                setup_board();
                put_boulder();
                put_dot();
                put_pman();
                put_ghost();
                print_board();
                command = getacharnow(SPEED);
                bool NotOnBoard = p.move(board, command); // know if the dot is
                // eaten on the board
                score_dot(NotOnBoard);
                num_moves = p.get_num_moves();
                move_ghost();
                dot_eaten();
        }
        replace_pman(); // let pacman eat by ghost on the board
        print_lose();
        next_level(); // advance to next level if winning
}

// setup_board
// purpose: display the initial condition of the board, set all the initial
// values to " "(blank space) and set the initial head
// arguments: none
// returns: none
void Game::setup_board()
{
        for(int i = 0;i < ROWS;i++){
                for(int j = 0;j < COLS;j++){
                        board[i][j] = ' ';
                }
        }
}

// print_board
// purpose: print the board everytime the array gets renewed
// arguments: none
// returns: none
void Game::print_board()
{
        cout << BORD_CORN;
        for(int i = 0;i < COLS;i++){
                cout << BORD_TOP;
        }
        cout << "+" << endl;
        for(int i = 0;i < ROWS;i++){
                cout << BORD_SIDE;
                for(int j = 0;j < COLS;j++){
                        cout << board[i][j];
                }
                cout << BORD_SIDE << endl;
        }
        cout << BORD_CORN;
        for(int i = 0;i < COLS;i++){
                cout << BORD_TOP;
        }
        cout << BORD_CORN << endl;
        display_score();
}

// put_boulder
// purpose: place all the boulders on the board
// arguments: none
// returns: none
void Game::put_boulder()
{
        for (int i = 0;i < BOULDERS_PER_LEVEL*level;i++) {
                boulders[i].place_on_board(board);
        }
}

// put_dot
// purpose: place all the dots on the board
// arguments: none
// returns: none
void Game::put_dot()
{
        for (int i = 0;i < DOTS_PER_LEVEL*level;i++) {
                dots[i].place_on_board(board);
        }
}

// dot_eaten
// purpose: set the associated Dot in the dots array to have been eaten if dot's
// location matches pacman's location
// arguments: none
// returns: none
void Game::dot_eaten()
{
        int col = p.get_col();
        int row = p.get_row();
        for (int i = 0;i < DOTS_PER_LEVEL*level;i++){
                if(dots[i].is_at(row,col) == true){
                        dots[i].set_eaten(true);
                }
        }
}


// set_location_d
// purpose: place all the dots on certain locations
// arguments: none
// returns: none
void Game::set_location_d()
{
        for (int i = 0;i < DOTS_PER_LEVEL*level;i++) {
                dots[i].set_eaten(false);
                dots[i].set_random_location(board);
                dots[i].place_on_board(board); 
        }
}

// set_location_g
// purpose: place all ghosts on certain locations   
// arguments: none
// returns: none
void Game::set_location_g()  
{   
        ghosts[0].set_location(0,0);
        ghosts[1].set_location(ROWS-1,0);
        ghosts[2].set_location(0,COLS-1);
        ghosts[3].set_location(ROWS-1,COLS-1);
}

// put_pman
// purpose: place Pacman on board
// arguments: none
// returns: none
void Game::put_pman()
{
        p.place_on_board(board);
}

// put_ghost
// purpose: place the ghosts on the board
// arguments: none
// returns: none
void Game::put_ghost()
{
        for (int i = 0;i < NUM_GHOSTS;i++){
                ghosts[i].place_on_board(board);
        }
}

// check_dots
// purpose: check if all the dots are eaten
// arguments: none
// returns: true/false
bool Game::check_dots()
{
        int sum_eaten = 0; 
        for (int i = 0;i < DOTS_PER_LEVEL*level;i++){
                if (dots[i].was_eaten() == true) {
                        sum_eaten++;
                }
        }
        if (sum_eaten == DOTS_PER_LEVEL*level){
                return true;
        }
        else {
                return false;
        }
}

// next_level
// purpose: check if win the level and then proceed to next level
// arguments: none
// returns: none
void Game::next_level()
{
        if (p.is_alive() == true and check_dots() == true) {
                if (level < NUM_LEVELS) {
                        score_level();
                        run();
                }
                else if (level == NUM_LEVELS){
                        cout << " YOU WIN !!! " << endl;
                }
        }
}

// print_lose
// purpose: print losing message if Pacman is no longer alive
// arguments: none
// returns: none
void Game::print_lose()
{
        if (p.is_alive() == false) {
                cout << " YOU LOSE !!! " << endl;
        }
}

// set_level
// purpose: set to next level after all the dots are eaten
// arguments: none
// returns: none
void Game::set_level()
{
        while (check_dots() == true and level <= NUM_LEVELS) {
                level++;
        }
}

// score_dot
// purpose: 1 point will be awarded for each dot eaten and print out the result
// arguments: none
// returns: none
void Game::score_dot(bool NotOnBoard)
{
        if(NotOnBoard == true){
                p.add_to_score(DOT_REWARD);
        }
}

// display_score
// purpose: display score
// arguments: none
// returns: none
void Game::display_score()
{
        cout << "Score: " << p.get_score() << endl;
}


// score_level
// purpose: 10 points will be awarded for each level completed
// arguments: none
// returns: none
void Game::score_level()
{
        p.add_to_score(LEVEL_REWARD);
}

// replace_pman()
// purpose: let ghost replace pacman on board after pacman is eaten
// arguments: none
// returns: none
void Game::replace_pman()
{
        screen_clear();
        setup_board();
        put_boulder();
        put_dot();
        p.place_on_board(board);
        put_ghost();
        print_board();
}

// move_ghost
// purpose: move ghost towards pacman
// arguments: none
// returns: none
void Game::move_ghost()
{
        for (int i = 0; i < NUM_GHOSTS; i++){
                if(num_moves % GHOST_FREQ == 0){
                        if(ghosts[i].move(board, p.get_row(), p.get_col())) {
                                p.die();
                        }
                        ghosts[i].place_on_board(board);
                } 
        }
}        
