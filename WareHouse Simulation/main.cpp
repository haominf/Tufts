/* COMP 15 PROJECT 1
 * This is the main() to run the whole program
 * By: Haomin Feng (hfeng03)
 * Date: Oct 14 2016
 */

#include <iostream>
#include <string>

#include "Operation.h"
#include "string2int.h"

using namespace std;

int main(int argc, char* argv[])
{
    int num_units = string2int(argv[2]);
    Operation o(num_units);
    o.run(argv[1],argv[3]);
    return 0;
}


