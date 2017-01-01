// COMP 15 PROJECT 1
// Orderqueue.cpp
// Complete Orderqueue Class Implementation
// By: hfeng03 (Haomin Feng)
// Date: Oct 12 2016

#include <iostream>
#include <string>

#include "Orderqueue.h"

using namespace std;

/* Purpose: constructor to initialize private members
 * Parameter: none
 * Return: none
 */
Orderqueue::Orderqueue()
{
    Sequence = new Order[InitCapacity];
    Capacity = InitCapacity;
    num_order = 0;
}

/* Purpose: destructor to delete heap memory
 * Parameter: none
 * Return: none
 */
Orderqueue::~Orderqueue()
{
    delete [] Sequence;    
}

/* Purpose: check whether the sequence is empty
 * Paramater: none
 * Return: true if is empty, otherwise false
 */
bool Orderqueue::isEmpty()
{
    if (num_order == 0) {
        return true;
    }
    return false;
}

/* Purpose: return the first order in the queue
 *          (for getting the information of the order)
 * Parameter: none;
 * Return: an Order struct
 */
Order Orderqueue::get_top()
{
    Order top = Sequence[0];
    return top;
}

/* Purpose: get the number of the orders in the sequence
 * Parameter: none;
 * Return: number of the orders
 */
int Orderqueue::get_num_order()
{
    return num_order;
}

/* Purpose: put the order into the queue
 * Parameter: an Order struct
 * Return: none
 */
void Orderqueue::enqueue(Order order)
{
    if (num_order == Capacity) {
        expand();
    }
    Sequence[num_order] = order;
    num_order++;
}

/* Purpose: return and remove the first item in the queue
 * Parameter: none
 * Return: an Order struct
 */
Order Orderqueue::dequeue()
{
    if (!isEmpty()) {
        Order copy = Sequence[0];
        for (int i = 0; i < num_order - 1; i++) {
            Sequence[i] = Sequence[i+1];
        }
        num_order--;
        return copy;
    }
    else {
        throw runtime_error("empty_queue");
    }
}

/* Purpose: expand the sequence if there's not enough space
 * Parameter: none
 * Return: none
 */
void Orderqueue::expand()
{
    Order *bigger = new Order[Capacity*2];
    for (int i = 0; i < num_order; i++) {
        bigger[i] = Sequence[i];
    }
    delete []Sequence;
    Sequence = bigger;
    Capacity *= 2;
}


