// COMP 15 PROJECT 1
// Retrieve.h
// Complete Retrieve Class Header and Declaration
// By: hfeng03 (Haomin Feng)
// Date: Oct 12 2016


#ifndef RETRIEVE_H
#define RETRIEVE_H

/* Retrieve contains Orderqueue class as a private member to store orders
 * into the queue. Since Orderqueue class contains Order struct, Retrieve also
 * contains Order struct, and in its function, Order is taken in as an argument.
 */
#include "Orderqueue.h"

class Retrieve
{
    private:

        Orderqueue ToBeFetched;

    public:

        Retrieve();

        ~Retrieve();

        /* place (enqueue) an incoming order into the retrieve queue if its 
         * arrival time matches the system clock. 
         */
        void place_in_retrieve(Order order);  

        /* dequeue the order from the retrieve queue when the fetcher is ready 
        */
        Order leave_retrieve();

        // get information of the first order in the retreive queue
        Order get_top(); 

        /* get a boolean value of whether the Retrieve queue is empty.
         * (Call isEmpty() in Orderqueue class)
         */
        bool isEmpty(); 

        // a timer that counts up time till the fetcher is done with fetching
        int worker_timer;    
};

#endif





