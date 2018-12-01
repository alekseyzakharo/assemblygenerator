#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include "GLOBALS.h"
#include <deque>
#include <string>

class Symtable
{
    public:
        Symtable();
        Symtable(string fileLocation);

        void Print();

    private:
        deque<symtableEntry> list;

        void openAndRead(string fileLocation);
        void Insert(string id, string parent);

};

#endif