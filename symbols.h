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

        vector<symbolEntry> list;

    private:
        

        //open symbols file and read enter values into vector list
        void openAndRead(string fileLocation);
        void Insert(string id, string tabid, string name, string type, string scope, string isArray, string arrSize, string isInited, string i, string b);

       
};
#endif