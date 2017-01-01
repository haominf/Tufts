// FSTreeTraversal.cpp
// COMP 15 PROJ 2
// Purpose: these functions are used to traverse the FSTree and then read in 
// every file and store words and file contents into two hash tables
// By: Haomin Feng (hfeng03)
// Date: Nov 15 2016

#include <iostream>
#include <string>
#include "FSTreeTraversal.h"

using namespace std;

/* CreateFSTree
 * Purpose: create a FSTree with the given directory and then call another
 *          helper function to traverse the tree and print out the file names
 * Parameter: a string of the highest directory name
 * Return: none
 */
void CreateFSTree(string directory, Hashing *H)
{
    FSTree tree(directory);
    DirNode *root = tree.getRoot();
    string path = directory;
    ReadFile RF(H);
    ReadFile *rs = &RF;
    FSTreeTraversal(root, path, rs);
}

/* FSTreeTraversal
 * Purpose: traverse the FSTree and print out the full paths of each file 
 *          in the tree
 * Parameter: a pointer to the DirNode (root), a string of pathName to 
 *            concatenate the names of the directories, and a pointer to the 
 *            shared instance of the ReadFile Class 
 * Return: none
 */
void FSTreeTraversal(DirNode *r, string pathName, ReadFile *rs)
{
    int numFiles = r->numFiles();
    // read in all the data from the files in the current directory
    for (int i = 0; i < numFiles; i++) {
        rs->run(r->getFile(i), pathName);
    }
    int numDirs = r->numSubDirs();
    // recursively traverse all the sub directories if there is any sub dir
    for (int i = 0; i < numDirs; i++) {
        DirNode *child = r->getSubDir(i);
        string temp = pathName + "/" + child->getName();
        FSTreeTraversal(child, temp, rs);
    }
}








