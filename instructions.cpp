#include "instructions.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

const string fileName = "instructions.csv";

ifstream instructFile;

using namespace std;


Instructions::Instructions()
{
    Instructions("");
}

Instructions::Instructions(string fileLocation)
{
    openAndRead(fileLocation);
}

void Instructions::openAndRead(string fileLocation)
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
    instructFile.open(symbolfile);
    if(instructFile.is_open())
    {
        while(getline(instructFile,line))
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
            int res;
            stringstream(record.at(1)) >> res;
            string opcode = record.at(2);
            int op1;
            stringstream(record.at(3)) >> op1;
            int op2;
            stringstream(record.at(4)) >> op2;
            Insert(id, res, opcode, op1, op2);
        }
    }
    else
    {
        cout<<fileName + " Failed to Open. Closing.\n";
        exit(1);
    }
    instructFile.close();
}

void Instructions::Insert(int id, int res, string opcode, int op1, int op2)
{
    list.push_back(instructEntry(id, res, opcode, op1, op2));
}

void Instructions::Print()
{
    cout<<"id   res   opcode   op1  op2   \n";
    for(instructEntry n: list)
    {
        printf("%d %d %s %d %d\n", n.id, n.res, n.opcode.c_str(), n.op1, n.op2);
    }
}