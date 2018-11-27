#include "symbols.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

//static declations
static string bts(bool val);

const string fileName = "symbols.csv";

ifstream symbolFile;

using namespace std;

Symbols::Symbols()
{
    Symbols("");
}

Symbols::Symbols(string fileLocation)
{
    openAndRead(fileLocation);
}

void Symbols::openAndRead(string fileLocation)
{
    string symbolfile = fileName;
    string line, str;
    if(fileLocation.size() > 0)
    {
        if(fileLocation.back() == '/')
        {
            symbolfile = fileLocation + fileName;
        }
        else
        {
            symbolfile = fileLocation + "/" + fileName;
        }
    }
    symbolFile.open(symbolfile);
    if(symbolFile.is_open())
    {
        while(getline(symbolFile,line))
        {
            istringstream ss(line);
            vector<string> record;
            while(getline(ss,str, ','))
            {
                record.push_back(str);
            }
            //get str values from the record vector
            //insert into the list
            int id;
            stringstream(record.at(0)) >> id;
            int tabid;
            stringstream(record.at(1)) >> tabid;
            string name = record.at(2);
            string type = record.at(3);
            string scope = record.at(4);
            bool isArray;
            istringstream(record.at(5)) >> isArray;
            int arrSize;
            stringstream(record.at(6)) >> arrSize;
            bool isInited;
            istringstream(record.at(7)) >> isInited;
            int i;
            stringstream(record.at(8)) >> i;
            bool b;
            istringstream(record.at(9)) >> b;

            Insert(id, tabid, name, type, scope, isArray, arrSize, isInited, i, b);
        }
    }
    else
    {
        cout<<fileName + " Failed to Open. Closing.\n";
        exit(1);
    }
    symbolFile.close();
}

void Symbols::Insert(int id, int tabid, string name, string type, string scope, bool isArray, int arrSize, bool isInited, int i, bool b)
{
    list.push_back(symbolEntry(id, tabid, name, type, scope, isArray, arrSize, isInited, i, b));
}

void Symbols::Print()
{
    cout<<"id   tabid   name    type    scope   isArray arrSize isInited    i   b\n";
    for(symbolEntry n: list)
    {
        printf("%d %d %s %s %s %s %d %s %d %s\n", n.id, n.tabid, n.name.c_str(), n.type.c_str(), n.scope.c_str(), bts(n.isArray).c_str(), n.arrSize, bts(n.isInited).c_str(), n.i, bts(n.b).c_str());
    }
}

//bool to string
static string bts(bool val)
{
    if(val)
    {
        return "true";
    }
    return "false";
}