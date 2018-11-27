#ifndef _SYMBOLS_H
#define _SYMBOLS_H

#include "GLOBALS.h"
#include <vector>
#include <string>

using namespace std;


class Symbols
{
    public:
        Symbols();
        Symbols(string fileLocation);

        void Print();

    private:
        vector<symbolEntry> list;

        //open symbols file and read enter values into vector list
        void openAndRead(string fileLocation);
        void Insert(int id, int tabid, string name, string type, string scope, bool isArray, int arrSize, bool isInited, int i, bool b);

       
};
#endif