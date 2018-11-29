#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <string>

using namespace std;

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


#endif