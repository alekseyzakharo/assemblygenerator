#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <string>

using namespace std;

struct symbolEntry
{
    int id;
    int tabid;
    string name;
    string type;
    string scope;
    bool isArray;
    int arrSize;
    bool isInited;
    int i;
    bool b;
    symbolEntry(int id, int tabid, string name, string type, string scope, bool isArray, int arrSize, bool isInited, int i, bool b)
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
    int id;
    int res;
    string opcode;
    int op1;
    int op2;
    instructEntry(int id, int res, string opcode, int op1, int op2)
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
    int id;
    int parent;
    symtableEntry(int id, int parent)
    {
        this->id = id;
        this->parent = parent;
    }
};


#endif