#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include "GLOBALS.h"

class Symtable
{
    public:
        Symtable();
        Symtable(string fileLocation);

        Print();

    private:
        vector<symtableEntry> list;

        void openAndRead(string fileLocation);
        void Insert(int id, int parent);

};

#endif