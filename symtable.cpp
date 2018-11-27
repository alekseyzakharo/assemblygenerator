#include "symtable.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

const string fileName = "symtable.csv";

ifstream symtableFile;

using namespace std;


Symtable::Symtable()
{
    Symtable("");
}

Symtable::Symtable(string fileLocation)
{
    openAndRead(fileLocation);
}

void Symtable::openAndRead(string fileLocation)
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
    symtableFile.open(symbolfile);
    if(symtableFile.is_open())
    {
        while(getline(symtableFile,line))
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
            int parent;
            stringstream(record.at(1)) >> parent;
            Insert(id, parent);
        }
    }
    else
    {
        cout<<fileName + " Failed to Open. Closing.\n";
        exit(1);
    }
    symtableFile.close();
}

void Symtable::Insert(int id,int parent)
{
    list.push_back(symtableEntry(id, parent));
}

void Symtable::Print()
{
    cout<<"id   parent   \n";
    for(symtableEntry n: list)
    {
        printf("%d %d\n", n.id, n.parent);
    }
}