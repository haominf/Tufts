// FSTreeTraversal.h
// COMP 15 PROJ 2
// Purpose: this is the header file of FSTreeTraversal.cpp
// By: Haomin Feng (hfeng03)
// Date: Nov 15 2016

#ifndef FSTREETRAVERSAL_H
#define FSTREETRAVERSAL_H    

#include <string>
#include "FSTree.h"
#include "DirNode.h"
#include "Hashing.h"
#include "ReadFile.h"

void FSTreeTraversal(DirNode *r, std::string pathName, ReadFile *rs);
void CreateFSTree(std::string directory, Hashing *H);

#endif
