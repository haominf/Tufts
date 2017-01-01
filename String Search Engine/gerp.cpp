// gerp.cpp
// COMP 15 PROJ 2
// main() function for this program "gerp"
// By: Haomin Feng (hfeng03)
// Date: Nov 25 2016

#include <iostream>
#include <string>
#include "FSTreeTraversal.h"
#include "Hashing.h"
#include "ReadFile.h"
#include "Search.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Usage:  gerp directory" << endl;
        cout << "            where:  directory is a valid directory" << endl;
        return 1;
    }
    else {
        Hashing hashing; // a shared Hashing Class to store and obtain data
        Hashing *HSH = &hashing;
        CreateFSTree(argv[1], HSH);
        cout << "Query? ";
        string command;
        Search search(HSH);
        while (cin >> command) { 
            if (command != "@q" and command != "@quit") {
                if (command == "@i" or command == "@insensitive") {
                    string query;
                    cin >> query;
                    search.InsensitiveSearch(query);
                }
                else {
                    search.SensitiveSearch(command);
                }
                cout << "Query? ";
            }
            else {
                break;
            }
        }
        cout << endl << "Goodbye! Thank you and have a nice day." << endl;
        return 1;
    }
}
