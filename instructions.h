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

    private:
        vector<instructEntry> list;

        void openAndRead(string fileLocation);
        void Insert(int id, int res, string opcode, int op1, int op2);
};



#endif