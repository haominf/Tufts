// Hashing.h
// COMP 15 PROJ 2 
// Purpose: this header file includes the Word Strcuct, the File Struct, and the
//          declaration of the Hashing Class
// By: Haomin Feng (hfeng03) 
// Date: Nov 25 2016

#ifndef HASHING_H
#define HASHING_H

#include<vector>
#include<string>
#include <functional>

struct Word 
{
    std::string value;  
    int fileindex;  // the index of the file in the file vector
    int  line;
};

struct File 
{
    std::string filename;
    std::string path;
    std::vector<std::string> lines;
};

class Hashing
{
    public:

        Hashing();

        ~Hashing();

        int get_HashIndex(std::string s);

        void addWord(Word word); 

        void addFile(File file);

        void CheckToExpand();

        std::string get_LowerCase(std::string s);  

        // get File from the File Vector
        File get_File(int index);

        // get a vector of Words from the hash table
        std::vector<Word> get_Chain(int index);

    private:

        void rehash(std::vector<std::vector<Word>> &copy);

        float LoadFactor;

        static const int InitSize = 2000;

        int numWords;

        int currentSize;

        std::hash<std::string> hashFunction;

        // to store the File structs
        std::vector<File> FileSequence; 

        // hash table
        std::vector<std::vector<Word>> WordBucket;  
};

#endif

