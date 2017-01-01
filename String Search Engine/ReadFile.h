// ReadFile.h
// COMP 15 PROJ 2  
// Purpose: the header file of the ReadFile Class
// By: Haomin Feng (hfeng03) 
// Date: Nov 25 2016

#ifndef READFILE_H
#define READFILE_H

#include "Hashing.h"

class ReadFile 
{
    public:

        ReadFile();

        ReadFile(Hashing *h);

        ~ReadFile();

        void run(std::string filename, std::string path);

    private:

        // a pointer to the Hashing Class where to store the data
        Hashing *hashing;

        File StructFile(std::string filename, std::string path) ;

        void ParseLine(std::string line, int Findex, int lineNum);

        Word StructWord(std::string word, int Findex, int lineNum);

        // the position(index) of the file in that File vector. For example, the
        // first file is stored in index 0; the second file in index 1; etc.
        int fileindex;
};

#endif



