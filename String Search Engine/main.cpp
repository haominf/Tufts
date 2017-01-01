#include <iostream>
#include <string>

#include "Hashing.h"
#include "ReadFile.h"
using namespace std;

int main()
{
    Hashing h;
    Hashing *haha = &h;
    ReadFile f(haha);
    f.run("haha.txt", "comp/15/");
    return 0;
}
