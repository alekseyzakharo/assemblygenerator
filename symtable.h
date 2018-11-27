#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include "GLOBALS.h"
#include <vector>
#include <string>

class Symtable
{
    public:
        Symtable();
        Symtable(string fileLocation);

        void Print();

    private:
        vector<symtableEntry> list;

        void openAndRead(string fileLocation);
        void Insert(int id, int parent);

};

#endif