// COMP 15 PROJECT 1  
// Packer.h
// Complete Packer Class Header and Declaration    
// By: hfeng03 (Haomin Feng) 
// Date: Oct 12 2016     


#ifndef PACKER_H
#define PACKER_H

/* Packer contains Orderqueue class as a private member to store orders 
 * into the queue. Since Orderqueue class contains Order struct, Packer also
 * contains Order struct, and in its function, Order is taken in as an argument.
 */
#include "Orderqueue.h" 

class Packer
{
    private:

        Orderqueue ToBePacked;

    public:

        Packer();

        ~Packer();

        // place (enqueue) an incoming order into the packer queue
        void place_in_packer(Order order);  

        // dequeue the order from the packer queue when it's done being packed
        Order leave_packer();

        /* get a boolean value of whether the packer queue is empty; aka whether
         * all the orders have been packed. Return true if is empty.
         */
        bool isEmpty();

        // return the number of total time 
        int get_total_time();

        /* get a total number of the orders remaining in the queue; used 
         * for fewest_items packing method especially.
         * (call get_num_order in Orderqueue class)
         */
        int get_num_orders();

        // a timer that counts up time till the packer is done with packing
        int worker_timer;

        // return the first order in the packing unit
        Order get_top();
};

#endif

