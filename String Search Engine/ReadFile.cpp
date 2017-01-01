// ReadFile.cpp
// COMP 15 PROJ 2  
// Purpose: ReadFile Class is used to open the file, read in its words and 
//          index them into a hash table. The file information is stored inside
//          a vector of File Structs.
// By: Haomin Feng (hfeng03)  
// Date: Nov 25 2016

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include<vector>

#include "ReadFile.h"

using namespace std;

/* default constructor
*/
ReadFile::ReadFile()
{
    hashing = NULL;
}

/* Purpose: constructor to take in a pointer of a Hashing class, so the words
 *          and the lines of a file can be stored into that Hashing Class
 * Parameter: a pointer to a Hashing Class
 * Return: none
 */
ReadFile::ReadFile(Hashing *h)
{
    hashing = h;
    fileindex = 0;
}

/* default destructor
*/
ReadFile::~ReadFile()
{
}

/* Purpose: open the file, read in its lines, and parse into words, and store 
 *          them into the hash table, and the vector.
 * Parameter: a string of the filename, a string of its path
 * Return: none
 */
void ReadFile::run(string filename, string path)
{
    ifstream infile;
    infile.open(path + "/" + filename);  
    if (infile.fail()) {  
        cerr << "Unable to read " << filename << endl;   
    }
    else {
        int lineNum = 0;
        string line;
        File f = StructFile(filename, path);
        // read in lines 
        while (getline(infile, line)) {
            lineNum++;
            // store each line into an array of lines
            f.lines.push_back(line);
            // parse the line into single words
            ParseLine(line, fileindex, lineNum);
        }
        hashing->addFile(f);
        fileindex++;
    }
    infile.close(); 
}

/* Purpose: store the file information into a File Struct
 * Parameter: a string of the filename, a string of the path
 * Return: a File Struct
 */
File ReadFile::StructFile(string filename, string path)
{
    File file;
    file.filename = filename;
    file.path = path;
    return file;
} 

/* Purpose: Parse each line into single words so we can index each word into the
 *          hash table
 * Parameter: a string of the line to be parsed, a string of the filename, and 
 *            an int of the line number
 * Return: none
 */
void ReadFile::ParseLine(string line, int Findex, int lineNum)
{
    string word;
    istringstream iss(line);
    while( iss >> word ) {
        Word w = StructWord(word, Findex, lineNum);
        hashing->CheckToExpand();
        hashing->addWord(w);
    }
}

/* Purpose: store the word information into a Word Struct
 * Parameter: a string of the filename, a string of the word, and an int of the 
 *            line number its in
 * Return: a Word Struct
 */
Word ReadFile::StructWord(string word, int Findex, int lineNum)
{
    Word w;
    w.value = word;
    w.fileindex = Findex;
    w.line = lineNum;
    return w;
}


