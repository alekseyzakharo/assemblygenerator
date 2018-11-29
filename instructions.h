#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "GLOBALS.h"
#include <string>
#include <vector>

using namespace std;

class Instructions{

    public:
        Instructions();
        Instructions(string fileLocation);

        void Print();

        vector<instructEntry> list;

    private:

        void openAndRead(string fileLocation);
        void Insert(string id, string res, string opcode, string op1, string op2);
};



#endif