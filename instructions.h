#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "GLOBALS.h"
#include <string>
#include <vector>

using namespace std;

class Instructions{

    public:
        vector<instructEntry> list;

        Instructions();
        Instructions(string fileLocation);

        void Print();

        void SetRes(string id, string res);
        void SetOp1(string id, string op1);
        void SetOp2(string id, string op2);
       

    private:

        void openAndRead(string fileLocation);
        void Insert(string id, string res, string opcode, string op1, string op2);
};



#endif