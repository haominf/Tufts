// COMP 15 PROJECT 1
// Operation.cpp
// Complete Operation Class Implementation
// By: hfeng03 (Haomin Feng)
// Date: Oct 9 2016

#include <iostream>
#include <string>
#include <fstream>

#include "Operation.h"

using namespace std;

/* Purpose: constructor to initialize private members
 * Parameter: none
 * Return: none
 */
Operation::Operation(int num_units)
{
    clock = 0;
    P = new Packer[num_units];
    num = num_units;
    index_Robin = 0;
    min = 0;
    max = 0;
    num_orders = 0;
    total_elapsed_time = 0;
}

/* destructor to delete the heap memory
*/
Operation::~Operation()
{
    delete [] P;
}

/* Purpose: check whether all packing units are empty
 * Parameter: none
 * Return: a bool value of true if empty, otherwise false
 */
bool Operation::PackerisEmpty()
{
    int count = 0;
    for (int i = 0; i < num; i++) {
        if (P[i].isEmpty()) {
            count++;
        }
    }
    if (count == num) {
        return true;
    }
    return false;
}

/* Purpose: check check if file queue, queue in Retrieve class, and queues in 
 *          Packer class are empty
 * Parameter: none
 * Return: a bool value of true if empty, otherwise false 
 */
bool Operation::isEmpty()
{
    if (R.isEmpty() and file.isEmpty() and PackerisEmpty()) {
        return true;
    }
    return false;
}

/* Purpose: parse the file given and read the info into Order strcut
 * Paramter: a string of the file's name
 * Return: none
 */
void Operation::parse_file(string filename)
{
    Parser p(filename);
    while (!p.is_done()) {
        Order order = p.read_order();
        file.enqueue(order);
    }
}

void Operation::run(string filename, string method) 
{    
    parse_file(filename);
    ofstream outf;
    outf.open("results.txt");
    while (!isEmpty()) {
        if (!file.isEmpty()) {
            if (file.get_top().arrival_timestamp == clock) {   
                R.place_in_retrieve(file.dequeue());           
            }
        }
        if (!R.isEmpty()) {
            if (R.worker_timer == R.get_top().fetch_duration) {
                R.worker_timer = 0;
                choose_method(method);
            }
            if (!R.isEmpty()) {
                R.worker_timer++;
            }
        }
        packing(outf);
        clock++;
    }
    sum_up(outf);
    outf.close();
}

// Purpose: run() helper funtion that deals with work in all the packing units
//          (pop the order when the worker timer is equal to the pack duration)
// Paramter: none
// Return: none
void Operation::packing(ofstream &outf)
{
    for (int i = 0; i < num; i++) {
        if (!P[i].isEmpty()) {
            if (P[i].worker_timer == P[i].get_top().pack_duration) {
                P[i].worker_timer = 0;
                 print(P[i].leave_packer(), outf);
            }
            if (!P[i].isEmpty()) {
                P[i].worker_timer++;
            }
        }
    }
}

/* Puporse: run() helper function: choose a method and place the order into the 
 *          packing unit
 * Parameter: none
 * Return: none
 */
void Operation::choose_method(string method)
{
    if (method == "FEWEST_ITEMS") {
        fewest_items(R.leave_retrieve());
    }
    else if (method == "SHORTEST_TIME") {
         shortest_time(R.leave_retrieve());
    }
    else if (method == "ROUND_ROBIN") {
        round_robin(R.leave_retrieve());
    }
}

/* Purpose: choose a packaging unit to assign the next order to based on
 *          which packaging unit has fewest items in its queue
 * Parameter: an Order struct
 * Return: none
 */
void Operation::fewest_items(Order order)
{
    int items = P[0].get_num_orders();
    int index = 0;
    for (int i = 1; i < num; i++) {
        if (P[i].get_num_orders() < items) {
            items = P[i].get_num_orders();
            index = i;
        }
    }
    P[index].place_in_packer(order);
}

/* Purpose: choose a packaging unit to assign the next order to based on which 
 *          packaging unit has the "shortest total time"
 * Parameter: an Order struct
 * Return: none
 */
void Operation::shortest_time(Order order)
{
    int time = P[0].get_total_time(); 
    int index = 0; 
    for (int i = 1; i < num; i++) { 
        if (P[i].get_total_time() < time) {
            time = P[i].get_total_time(); 
            index = i;
        }
    }
    P[index].place_in_packer(order); 
}

/* Purpose: choose a packaging unit to assign the next order to based on 
 *          "taking turns."
 * Parameter: an Order struct
 * Return: none
 */
void Operation::round_robin(Order order)
{
    P[index_Robin].place_in_packer(order);
    if (index_Robin == num - 1) {
        index_Robin = 0;
    }
    else {
        index_Robin++;
    }
}   

/* Purpose: store the printing result into an output file
 * Parameter: an Order struct
 * ReturnL none
 */
void Operation::print(Order order, ofstream &outf)
{
    cout << "<Order(" << order.id << ")" << " arrival_timestamp = "
        << order.arrival_timestamp << " fetch_duration = "
        << order.fetch_duration << " pack_duration = " << order.pack_duration
        << " total_time = " << clock - order.arrival_timestamp
        << ">" << endl;
    outf << "<Order(" << order.id << ")" << " arrival_timestamp = "        
        << order.arrival_timestamp << " fetch_duration = "
        << order.fetch_duration << " pack_duration = " << order.pack_duration 
        << " total_time = " << clock - order.arrival_timestamp 
        << ">" << endl;
    elapsed_time(order);
}

/* Purpose: record the min and max elapsed time, the total elapsed time of all 
 *          orders, and num of orders.
 * Parameter: an Order struct
 * Return: none
 */
void Operation::elapsed_time(Order order)
{
    num_orders++;
    if (num_orders == 1) {
        min = clock - order.arrival_timestamp;
        max = clock - order.arrival_timestamp;
    }
    if (clock - order.arrival_timestamp > max) {
        max = clock - order.arrival_timestamp;
    }
    else if (clock - order.arrival_timestamp < min) {
        min = clock - order.arrival_timestamp;
    }
    total_elapsed_time += clock - order.arrival_timestamp;
}

/* Purpose: to sum up the information of all orders
 *          (the min, max, mean elapsed time and the total oders)
 * Parameter: none
 * Return: none
 */
void Operation::sum_up(ofstream &outf)
{ 
    cout << "min elapsed time " << min <<" minutes" <<endl;
    cout << "max elapsed time " << max <<" minutes" <<endl; 
    cout << "mean elapsed time " << total_elapsed_time / num_orders
         << " minutes" << endl;
    cout << num_orders << " orders processed" << endl;
    outf << "min elapsed time " << min <<" minutes" <<endl;
    outf << "max elapsed time " << max <<" minutes" <<endl; 
    outf << "mean elapsed time " << total_elapsed_time / num_orders 
        << " minutes" << endl;
    outf << num_orders << " orders processed" << endl;
}


















