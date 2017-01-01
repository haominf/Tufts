// snake.cpp --snake game
// purpose: design a game which lets the player move the snake 
// around and scores inside the board
// by: Haomin Feng
// date: March 12 2016

#include <iostream> 
#include "termfuncs.h"
using namespace std;

const int COLS = 61;
const int ROWS = 21;
const char HEAD[4]={'^','<','v','>'};
const char BODY='#';
const char SNACK1='o';
const char SNACK2='X';

// know where the head of the snake is and the snake's status 
struct Position{
        int column;
        int row;
        int direction;
        int energy;
        bool die; 
};

void setup_board(char array[][COLS]);
void print_board(char array[][COLS]);
int play_game(char array[][COLS]);
Position draw_hash(char array[][COLS], char input, Position snake);
Position move_HEAD(char array[][COLS],char input,Position snake);
Position cross_wall(Position snake);
void put_snacks(char array[][COLS], char snack_type);
int calc_score(char array[][COLS]);
void print_result(int score, Position snake);
Position add_energy(char array[][COLS],Position snake);
void report(int score);
void generate_snack(char array[][COLS]);
Position game_over(char array[][COLS],Position snake);

int main()
{
        char board[ROWS][COLS]; 
        int score;
        setup_board(board);
        score = play_game(board);
        report(score);
        return 0;
}

// setup_board
// purpose: display the initial condition of the board, set all the initial
// values to " "(blank space) and set the initial snake HEAD
// argument: a 2D char array that sets the board
void setup_board(char array[][COLS])
{
        screen_clear(); // clear terminal
        for(int i=0;i<ROWS;i++){
                for(int j=0;j<COLS;j++){
                        array[i][j]=' ';
                }
        }
        array[ROWS/2][COLS/2]='^';
        generate_snack(array);
        print_board(array);
}

// print_board
// purpose: print the board everytime the array gets renewed
// argument: a 2D char array that sets the board
void print_board(char array[][COLS])
{
        cout<<"+";
        for(int i=0;i<COLS;i++){
                cout<<"-";
        }
        cout<<"+"<<endl;
        for(int i=0;i<ROWS;i++){
                cout<<"|";
                for(int j=0;j<COLS;j++){
                        cout<<array[i][j];
                }
                cout<<"|"<<endl;
        }
        cout<<"+";
        for(int i=0;i<COLS;i++){
                cout<<"-";
        }
        cout<<"+"<<endl;
}

// play_game
// purpose: use this function to call other small functions to play the game
// argument: a 2D char array that sets the board
// return value: return score  
int play_game(char array[][COLS])
{
        Position snake;  // initial values
        snake.column=COLS/2;
        snake.row=ROWS/2;
        snake.direction=0;
        snake.energy=60;
        snake.die=false;
        int score=0;
        print_result(score,snake); 
        char input='a';
        
        do { 
                input=getachar();
                snake= move_HEAD(array,input,snake);
                snake=draw_hash(array,input,snake);
                screen_clear(); // clear terminal
                generate_snack(array);
                print_board(array);
                score = calc_score(array);
                print_result(score, snake);
        } while (snake.die==false);
        return score;
}

// move_HEAD
// purpose: move the HEAD of the snake to four different direcitons
// argument: a 2D char array that sets the board, a char input that controls 
// the directions, and a struct that knows the info of the snake
// return value: return new values to the struct 
Position move_HEAD(char array[][COLS],char input,Position snake)
{
        if (input=='l'){
                snake.direction++;
                if (snake.direction==4){
                        snake.direction=0;
                }
                array[snake.row][snake.column]=HEAD[snake.direction];
        }
        if (input=='r'){
                snake.direction--;
                if (snake.direction==-1){
                        snake.direction=3;
                }
                array[snake.row][snake.column]=HEAD[snake.direction];
        }
        return snake;
}

// draw_hash
// purpose: draw the hash when moving the snake
// argument: a 2D char array that sets the board, a char input that controls 
// the directions, and a struct that knows the info of the snake
// return value: return new values to the struct
Position draw_hash(char array[][COLS], char input, Position snake)
{        
        if (input=='f'){
                array[snake.row][snake.column]=BODY;
                snake.energy--;
                if (snake.direction==0) {
                        snake.row--;
                }
                if (snake.direction==1){
                        snake.column--;
                }
                if (snake.direction==2){
                        snake.row++;
                }
                if (snake.direction==3){
                        snake.column++;
                }
                snake=add_energy(array,snake); 
                snake=game_over(array,snake); // check if it dies
                snake=cross_wall(snake);
                array[snake.row][snake.column]=HEAD[snake.direction];
         }
        return snake;
}

// cross_wall
// purpose: enable the snake to cross the boarders and then appear on the other
// side
// argument: a struct that knows the info of the snake
// return value: return new values to the struct
Position cross_wall(Position snake)
{
        if (snake.row<0){
                snake.row=ROWS-1;
        }
        if (snake.row==ROWS){
                snake.row=0;
        }
        if (snake.column<0){
                snake.column=COLS-1;
        }
        if (snake.column==COLS){
                snake.column=0;
        }
        return snake;
}

// put_snacks
// purpose: put new snack if the old one is eaten by the snake
// argument: a 2D char array that sets the board, and a char that determines
// which type of snack to put
void put_snacks(char array[][COLS], char snack_type)
{
        int snack_row1, snack_col1;
        int snack_row2, snack_col2;
        snack_row1 = random_int(0,ROWS); //generate random positions
        snack_col1 = random_int(0,COLS);
        snack_row2 = random_int(0,ROWS);
        snack_col2 = random_int(0,COLS);
        if (snack_type==SNACK1){ 
                while (array[snack_row1][snack_col1] != ' ') { // make sure the 
                        snack_row1 = random_int(0,ROWS);       // snack is put
                        snack_col1 = random_int(0,COLS);       // in the empty
                }                                              // array
                array[snack_row1][snack_col1]=SNACK1;
        }
        if (snack_type==SNACK2){
                while  (array[snack_row2][snack_col2] != ' ') {
                        snack_row2 = random_int(0,ROWS);
                        snack_col2 = random_int(0,COLS);
                }
                array[snack_row2][snack_col2]=SNACK2;
        }
}

// calc_score
// purpose: calculate the socre of the game, aka count how many hashes are in
// the board
// argument: a 2D char array that sets the board
// return value: return the integer sum/score of the hashes/HEAD 
int calc_score(char array[][COLS])
{
        int sum = 0;
        for (int i=0;i<COLS;i++){
                for (int j=0;j<COLS;j++){
                        if (array[i][j]==BODY) {
                                sum++;
                        }
                }
        }
        return sum;
}

// print_result
// purpose: print the the energy and the score
// argument: an integer that shows the score and a struct that knows the info of
// the snake 
void print_result(int score, Position snake)
{
        cout<<"EU: "<<snake.energy<<"   ";
        cout<<"Score: "<<score<<endl;
}

// add_energy
// purpose: add energu if the snake eats a snack
// argument: a 2D char array that sets the board and a struct that knows the 
// info of the snake
// return value: return new values to the struct  
Position add_energy(char array[][COLS],Position snake)
{
        if (array[snake.row][snake.column]==SNACK1){
                snake.energy=snake.energy+15;
        }
        if (array[snake.row][snake.column]==SNACK2){
                snake.energy=snake.energy+25;
        }
        return snake;
}

// report
// purpose: report the final score when game is over
// argument: an integer of the total score
void report(int score)
{
        cout<<"Game Over."<<" "<<"Final Score:   "<<score<<endl;
}

// generate_snack
// purpose: determine the condition whether needs to add snacks
// argument: a 2D char array that sets the board
void generate_snack(char array[][COLS])
{
        int exist=0; // the existence of the snack
        for (int i=0;i<ROWS;i++){
                for (int j=0;j<COLS;j++){
                        if (array[i][j]==SNACK1) { // determine if the snack is 
                                exist=1;           // eaten or not
                        }
                }
        }
        if (exist!=1){
                put_snacks(array,SNACK1); // put new snack
        }
        exist=0; //reset the existence of snack 2
        for (int i=0;i<ROWS;i++){
                for (int j=0;j<COLS;j++){
                        if (array[i][j]==SNACK2) {
                                exist=1;
                        }
                }
        }
        if (exist!=1){
                put_snacks(array,SNACK2);
        }
}

// game_over
// purpose: determine when the snake dies and then end the game
// argument: a 2D char array that sets the board and and a struct that knows the
// info of the snake
// return value: return new values to the struct    
Position game_over(char array[][COLS],Position snake)
{
        if (array[snake.row][snake.column]==BODY or snake.energy==0) {
                snake.die=true;
        }
        else {
                snake.die=false;
        }
        return snake;
} 
