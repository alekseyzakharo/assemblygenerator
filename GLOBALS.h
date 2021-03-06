#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <string>
#include <deque>

using namespace std;

const int VARBYTESIZE = 16;

struct symbolEntry
{
    string id;
    string tabid;
    string name;
    string type;
    string scope;
    string isArray;
    string arrSize;
    string isInited;
    string i;
    string b;
    symbolEntry(string id, string tabid, string name, string type, string scope, string isArray, string arrSize, string isInited, string i, string b)
    {
        this->id = id;
        this->tabid = tabid;
        this->name = name;
        this->type = type;
        this->scope = scope;
        this->isArray = isArray;
        this->arrSize = arrSize;
        this->isInited = isInited;
        this->i = i;
        this->b = b;
    }
};

struct instructEntry
{
    string id;
    string res;
    string opcode;
    string op1;
    string op2;
    instructEntry(string id, string res, string opcode, string op1, string op2)
    {
        this->id = id;
        this->res = res;
        this->opcode = opcode;
        this->op1 = op1;
        this->op2 = op2;
    }

};

struct symtableEntry
{
    string id;
    string parent;
    symtableEntry(string id, string parent)
    {
        this->id = id;
        this->parent = parent;
    }
};

struct localVariable{
    string name;
    string offset;

    localVariable(string name, string offset)
    {
        this->name = name;
        this->offset = offset;
    }
};

struct Method{
    int size;
    string name;
    deque<localVariable> list;

    Method(string name)
    {
        size = 0;
        this->name = name;
    }

    string FindOffset(string name)
    {
        int size = list.size();
        for(int i = 0;i<size;i++)
        {
            if(list.at(i).name.compare(name) == 0)
            {
                return list.at(i).offset;
            }
        }
        return "";
    }

    string FindName(string offset)
    {
        int size = list.size();
        for(int i = 0;i<size;i++)
        {
            if(list.at(i).offset.compare(offset) == 0)
            {
                return list.at(i).name;
            }
        }
        return "";
    }

};

enum OPCODES {ADD, SUB, MUL, DIV, READ, WRITE, ASSIGN, PARAM, CALL, RET};

#endif