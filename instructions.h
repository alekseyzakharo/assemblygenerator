#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "GLOBALS.h"
#include <deque>
#include <vector>

using namespace std;

class Instructions{

    public:
        deque<instructEntry> list;

        Instructions();
        Instructions(string fileLocation);

        void Print();

        void SetRes(string id, string res);
        void SetOp1(string id, string op1);
        void SetOp2(string id, string op2);

        void Remove(string id);

        instructEntry GetByRes(string res);
        
        void InsertLabel(string id, string labelName);

    private:

        void openAndRead(string fileLocation);
        void Insert(string id, string res, string opcode, string op1, string op2);
};



#endif