// COMP 15 PROJECT 1
// Retrieve.cpp
// Complete Retrieve Class Implementation
// By: hfeng03 (Haomin Feng)
// Date: Oct 12 2016

#include <iostream>
#include <string>

#include "Retrieve.h"

using namespace std;

/* Purpose: constructor to initialize private members
 * Parameter: none
 * Return: none
 */
Retrieve::Retrieve()
{
    worker_timer = 0;
}

/* default destructor
*/
Retrieve::~Retrieve()
{
}

/* Purpose: enqueue an order intot the retrieve queue when the system time 
 * matches the order's arrival time
 * Parameter: an Order struct
 * Return: none
 */
void Retrieve::place_in_retrieve(Order order)
{
    ToBeFetched.enqueue(order);
}

/* Purpose: dequeue an order if the fetcher is done fetching
 * Parameter: none
 * Return: an Order struct
 */
Order Retrieve::leave_retrieve()
{
    Order top = ToBeFetched.dequeue();
    return top;
}

/* Purpose: check if there is any order in the retireve queue
 * Parameter: none
 * Return: bool of true is it is empty, otherwise false
 */
bool Retrieve::isEmpty() 
{
    return ToBeFetched.isEmpty();
}

/* Purpose: return the top order from the retireve queue
 * Parameter: none
 * Return: an Order struct of the first order in the queue
 */
Order Retrieve::get_top()
{
    return ToBeFetched.get_top();
}






