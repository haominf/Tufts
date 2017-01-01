// Search.cpp
// COMP 15 PROJ 2  
// Purpose: Search Class is used to do Sensitive Seach and Insensitive Search, 
//          with the help of the hash table stored in a Hashing Class
// By: Haomin Feng (hfeng03)  
// Date: Nov 25 2016

#include <iostream>
#include <string>
#include<vector>

#include "Search.h"

using namespace std;

/* default constructor
*/
Search::Search()
{
    hashing = NULL;
}

/* Purpose: constructor to take a pointer to a Hashing Class, and use that 
 *          Hashing Class to find the values stored in the hash table
 * Parameter: a pointer to the Hashing Class
 * Return: none
 */
Search::Search(Hashing *h)
{
    hashing = h;
}

/* default destructor
*/
Search::~Search()
{
}

/* Purpose: a sensitive search of a string. For example, "we" and "We" are 
 *          treated as different strings
 * Parameter: a string to search for
 * Return: none
 */
void Search::SensitiveSearch(string s)
{
    string convert = hashing->get_LowerCase(s);
    int index = hashing->get_HashIndex(convert);
    int found = SearchHelper(index, s, convert, 1);
    if (found == 0) {
        cout << s << " Not Found. Try with @insensitive or @i." << endl;
    }
}

/* Purpose: Search Helper/Modular Function. If it is sensitive search, the 
 *          sentinel will be 1; if it is insensitive search, the sentinel will
 *          be 2.
 * Parameter: an int of the bucket index, a string of query, a string of the 
 *            converted query, an int of the sentinel 
 * Return: an int of how many times the query is found
 */
int Search::SearchHelper(int index, string query, string convert, int sentinel)
{
    int found = 0;
    int printedFile = -1;
    int printedLine = -1;
    // traverse the bucket of the calculated index
    vector<Word> Chain = hashing->get_Chain(index);
    if (Chain.size() != 0) {
        for (size_t i = 0; i < Chain.size(); i++) {
            string value = Chain[i].value;
            string convert_ = hashing->get_LowerCase(value);
            if ((sentinel == 1 and query == Chain[i].value)
                    or (sentinel == 2 and convert == convert_)) {
                bool isPrinted = false;
                // check if the word on the same line is already printed
                if (printedFile == Chain[i].fileindex
                        and printedLine == Chain[i].line) {
                    isPrinted = true;
                }
                if (!isPrinted) {
                    found++;
                    // store the info of the printed word
                    printedFile = Chain[i].fileindex;
                    printedLine = Chain[i].line;
                    Word w = Chain[i];
                    FindFile(w);
                }
            }
        }
    }
    return found;
}

/* Purpose: Find the File Struct associated with the Word Struct and print out 
 *          the search result
 * Parameter: a Word Struct
 * Return: none
 */
void Search::FindFile(Word w)
{
    File f = hashing->get_File(w.fileindex);
    cout << f.path << "/" << f.filename << ":" << w.line 
        << ": " << f.lines[w.line - 1] << endl;
}

/* Purpose: a insensitive search of a string. For example, "we" and "We" would 
 *          be treated as the same words. (All the words will be converted to
 *          lower-case letters)
 * Parameter: a string of word to seach
 * Return: none
 */
void Search::InsensitiveSearch(string s)
{
    string convert = hashing->get_LowerCase(s);
    int index = hashing->get_HashIndex(convert); 
    int found = SearchHelper(index, s, convert, 2);
    if (found == 0) {
        cout << s << " Not Found." << endl;
    }
}   








