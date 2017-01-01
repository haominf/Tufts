// COMP 15 PROJECT 1  
// Packer.cpp
// Complete Packer Class Implementation
// By: hfeng03 (Haomin Feng) 
// Date: Oct 12 2016

#include <iostream>
#include <string>

#include "Packer.h"

using namespace std;

/* Purpose: constructor to initialize private members
 * Parameter: none
 * Return: none
 */
Packer::Packer()
{
    worker_timer = 0;
}

/* default destructor
*/
Packer::~Packer()
{

}

/* Purpose: enqueue an order into the packing unit when the fetcher is done 
 * fetching
 * Parameter: an Order struct   
 * Return: non3
 */ 
void Packer::place_in_packer(Order order)
{
    ToBePacked.enqueue(order);
}

/* Purpose: dequeue an order if the packer is done packing
 * Parameter: none
 * Return: an Order struct
 */
Order Packer::leave_packer()
{
    Order top = ToBePacked.dequeue();
    return top;
}

/* Purpose: check if there is any order in the packing unit
 * Parameter: none
 * Return: bool of true is it is empty, otherwise false
 */
bool Packer::isEmpty()
{
    return ToBePacked.isEmpty();
}

/* Purpose: get the total time left of all the orders in the packing unit
 * Parameter: none
 * Return: an integter of the total time
 */
int Packer::get_total_time()
{
    int total_time = 0;
    for(int i = 0; i < ToBePacked.get_num_order(); i++) {
        total_time += ToBePacked.Sequence[i].pack_duration;
    }
    return total_time - worker_timer;
} 

/* Purpose: get the total number of orders in the packing unit
 * Parameter: none
 * Return: an integetr of the number of orders
 */
int Packer::get_num_orders()
{
    return ToBePacked.get_num_order();
}

/* Purpose: return the top order in the packing unit
 *          (for getting the information of the first order)
 * ParameterL none
 * Return: an Order struct
 */
Order Packer::get_top()
{
    if (!ToBePacked.isEmpty()) {
        Order top = ToBePacked.get_top();
        return top;
    }
    else {
        Order empty;
        empty.pack_duration = 0;
        return empty;
    }
}


