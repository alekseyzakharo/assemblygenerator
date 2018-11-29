#include <iostream>
#include <cstring>
#include "assembler.h"

using namespace std;

string DEFAULTNAME = "test.s";


int main(int argc, char * argv[]){

    Assembler *s;
    if(argc  == 2)
    {
        s = new Assembler(argv[1]);
    }
    else
    {
        s = new Assembler("");
    }


    s->Build();

    s->PrintCSVContent();

    return 0;
}