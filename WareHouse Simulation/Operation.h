// COMP 15 PROJECT 1
// Operation.h
// Complete Operation Class Header and Declaration
// By: hfeng03 (Haomin Feng)
// Date: Oct 6 2016

#ifndef OPERATION_H
#define OPERATION_H    

/* Operation class contains Parser class to read in file inputs and parse them 
 * into structs. String2int() is to help convert variable types. Operation also
 * contains Retrieve and Packer class to assign retrieving/fetching and packing
 * tasks them to finish.
 */
#include "Parser.h"
#include "string2int.h"
#include "Packer.h"
#include "Retrieve.h"
#include "Orderqueue.h"

class Operation
{
    private:

        // system clock that adds one time step after every loop 
        int clock;

        // num of the packing units that the user wants
        int num;

        // record the current index of round robin unit
        int index_Robin;

        // used to store the min elapsed time
        int min;

        // used to store the max elasped time
        int max;

        // record the total number of orders for calculation
        int num_orders;

        // record the total elapsed time of all orders
        int total_elapsed_time;

        Packer *P;

        Orderqueue file;

        /* check if file queue, queue in Retrieve class, and queues in Packer 
         * class are empty. In other words, if there's no order in the 
         * warehouse anymore. Used to determine whether we should stop
         * the system clock (end the program).
         */
        bool isEmpty();

        // check if all the Packing units are empty (helper func) 
        bool PackerisEmpty();

        // create a Retrieve class instance to do the retrieving + fetching job
        Retrieve R;

        // packing method one, depends on user input 
        void fewest_items(Order order);

        // packing method two
        void shortest_time(Order order);

        // packing method three
        void round_robin(Order order);

        // read from the the file and store info in the Order struct
        void parse_file(std::string filenmae);

        void elapsed_time(Order order);

        void sum_up(std::ofstream &outf);   

        void packing(std::ofstream &outf);

        void choose_method(std::string method);     

    public:

        /* initialize an array of Packers in the constructor; number given by 
         * the user input.
         */
        Operation(int num_units);

        ~Operation();

        // run the program (helper functions are private members)
        void run(std::string filename, std::string method);

        // store the output into a file
        void print(Order order, std::ofstream &outf);
};

#endif

