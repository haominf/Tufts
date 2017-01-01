// Search.h
// COMP 15 PROJ 2  
// Purpose: the header file of the Search Class
// By: Haomin Feng (hfeng03)  
// Date: Nov 25 2016

#ifndef SEARCH_H
#define SEARCH_H

#include "Hashing.h"

class Search
{
    public:

        Search();

        Search(Hashing *h);

        ~Search();

        void SensitiveSearch(std::string s);

        void InsensitiveSearch(std::string s);

    private:

        void FindFile(Word w);

        int SearchHelper(int index, std::string query, std::string convert, 
                int sentinel);

        // a pointer to the Hashing Class where the data is stored
        Hashing *hashing;

};

#endif



