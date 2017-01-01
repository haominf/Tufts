// Hashing.cpp
// COMP 15 PROJ 2  
// Purpose: Hashing Class is used to index a word into a hash table and index a
//          into a vector.
// By: Haomin Feng (hfeng03)  
// Date: Nov 25 2016

#include <iostream>
#include <functional>   
#include <stdio.h>
#include <ctype.h>
#include "Hashing.h"

using namespace std; 

/* Purpose: constructor to initialize the inital size of the hash table, and set
 *          the load factor.
 * Parameter: none
 * Return: none
 */
Hashing::Hashing()
{
    LoadFactor = 1.9;
    vector<Word> www;
    for (int i = 0; i < InitSize; i++) {
        WordBucket.push_back(www);
    }
    currentSize = InitSize;
    numWords = 0;
}

/* Default destructor
*/
Hashing::~Hashing()
{
}

/* Purpose: Check if the hash table is full, and yes, resize the hash table. 
 *          otherwise, do nothing.
 * Parameter: none
 * Return: none
 */
void Hashing::CheckToExpand()
{
    // check if it needs expansion
    if (float(numWords / currentSize) > LoadFactor) { 
        vector<vector<Word>> copy = WordBucket;
        WordBucket.clear();
        vector<Word> www;
        // initialize the expanded hash table
        for (int i = 0; i < currentSize*2; i++) {
            WordBucket.push_back(www);
        }
        currentSize *= 2;
        rehash(copy);
    }
}

/* Purpose: Rehash the keys from the old hash table to the bigger hash table
 * Parameter: a reference to the copy of the old hash table
 * Return: none
 */
void Hashing::rehash(vector<vector<Word>> &copy)
{
    numWords = 0;
    size_t copySize = copy.size();
    for (size_t i = 0; i < copySize; i++) {  
        size_t chainSize = copy[i].size();
        for (size_t j = 0; j < chainSize; j++) {
            Word w = copy[i][j];
            addWord(w);
        }
    }
}


/* Purpose: call for the built-in hash function to hash a word, and then use the
 *          hash value divided by the hash table size to get the index
 * Parameter: a string of the word to hash
 * Return: an int of the index in the hash table
 */
int  Hashing::get_HashIndex(string s)
{
    size_t hash = hashFunction(s);
    int index = hash % currentSize;
    return index;
}

/* Purpose: add a Word Struct into the hash table with the hash value obtained
 * Parameter: a Word Struct
 * Return: none
 */
void Hashing::addWord(Word word)
{
    string value = get_LowerCase(word.value);
    int index = get_HashIndex(value);
    WordBucket[index].push_back(word);
    numWords++;
}

/* Purpose: add a File Struct into the File vector
 * Parameter: a File Struct
 * Return: none
 */
void Hashing::addFile(File file)              
{ 
    FileSequence.push_back(file);
}

/* Purpose: change the Upper-case word into lower-case, so it has the same hash 
 *          value as its lower-case equivalent. (Used for insensitive search)
 * Parameter: a string of the word
 * Return: a converted string of word
 */
string Hashing::get_LowerCase(string s)
{
    for (int i = 0; i < int(s.length()); i++) {
        if (s[i] >= 'A' and s[i] <= 'Z') {
            s[i] = tolower(s[i]);
        }
    }
    return s;
}

/* Purpose: Return the File from the FileSequence according to a given index
 * Parameter: an int of index
 * Return: a File Struct
 */
File Hashing::get_File(int index)
{
    return FileSequence[index];
}

/* Purpose: Return the chain of a certain WordBucket in the Hash Table
 * Parameter: an int of index
 * Return: a vector of Word structs
 */
vector<Word> Hashing::get_Chain(int index)
{
    return WordBucket[index];
}



