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
            
            string id, tabid, name, type, scope, isArray, arrSize, isInited, i, b;
            id = record.at(0);
            tabid = record.at(1);
            name = record.at(2);
            type = record.at(3);
            scope = record.at(4);
            isArray = record.at(5);
            arrSize = record.at(6);
            isInited = record.at(7);
            i = record.at(8);
            b = record.at(9);

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

void Symbols::Insert(string id, string tabid, string name, string type, string scope, string isArray, string arrSize, string isInited, string i, string b)
{
    list.push_back(symbolEntry(id, tabid, name, type, scope, isArray, arrSize, isInited, i, b));
}

void Symbols::Print()
{
    cout<<"id   tabid   name    type    scope   isArray arrSize isInited    i   b\n";
    for(symbolEntry n: list)
    {
        cout<<n.id<<" "<<n.tabid<<" "<<n.name<<" "<<n.type<<" "<<n.scope<<" "<<n.isArray<<" "<<n.arrSize<<" "<<n.isInited<<" "<<n.i<<" "<<n.b<<endl;
    }
}
