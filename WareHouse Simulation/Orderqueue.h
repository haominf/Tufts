// COMP 15 PROJECT 1
// Orderqueue.h
// Complete Orderqueue Class Header and Declaration
// By: hfeng03 (Haomin Feng)
// Date: Oct 4 2016

#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include "Order.h"

class Orderqueue
{
    private:

        // initial capacity of the array
        static const int InitCapacity = 5;  

        // keep track of the number of orders in the queue
        int num_order;

        // capacity of the dynamic array
        int Capacity;

        // expand the array when there's no space left
        void expand();

    public:

        Orderqueue();

        ~Orderqueue();

        // pointer used for dynamic array
        Order *Sequence;

        // check whether the sequence is empty
        bool isEmpty();
        
        // return the top order in the queue
        Order get_top();

        // get the number of orders in the sequence
        int get_num_order();

        // put order into the queue
        void enqueue(Order order);

        // get order out of the queue
        Order dequeue();
};
#endif
