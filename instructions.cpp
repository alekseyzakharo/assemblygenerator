#include "instructions.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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

void Instructions::SetRes(string id, string res)
{
    for(int i =0;i<list.size();i++)
    {
        if(list.at(i).id.compare(id) == 0)
        {
            instructEntry tmp = list.at(i);
            list.erase(list.begin()+i);
            tmp.res = res;
            list.insert(list.begin()+i,tmp);
            break;
        }
    }
}

void Instructions::SetOp1(string id, string op1)
{
    for(int i =0; i < list.size();i++)
    {
        if(list.at(i).id.compare(id) == 0)
        {
            instructEntry tmp = list.at(i);
            list.erase(list.begin()+i);
            tmp.op1 = op1;
            list.insert(list.begin()+i,tmp);
            break;
        }
    }
}

void Instructions::SetOp2(string id, string op2)
{
    for(int i =0;i<list.size();i++)
    {
        if(list.at(i).id.compare(id) == 0)
        {
            instructEntry tmp = list.at(i);
            list.erase(list.begin()+i);
            tmp.op2 = op2;
            list.insert(list.begin()+i,tmp);
            break;
        }
    }
}

void Instructions::Remove(string id)
{
    for(int i =0;i<list.size();i++)
    {
        if(list.at(i).id.compare(id) == 0)
        {
            list.erase(list.begin()+i);
        }
    }
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
            string id = record.at(0);
            string res = record.at(1);
            string opcode = record.at(2);
            string op1 = record.at(3);
            string op2 = record.at(4);
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

void Instructions::Insert(string id, string res, string opcode, string op1, string op2)
{
    list.push_back(instructEntry(id, res, opcode, op1, op2));
}

void Instructions::Print()
{
    cout<<"id   res   opcode   op1  op2   \n";
    for(instructEntry n: list)
    {
        cout<<n.id<<" "<<n.res<<" "<<n.opcode<<" "<<n.op1<<" "<<n.op2<<endl;
    }
}