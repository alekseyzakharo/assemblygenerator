#ifndef _ASSEMBLY_H
#define _ASSEMBLY_H

#include "symbols.h"
#include "instructions.h"
#include "symtable.h"


class Assembler
{
    public:
        Assembler();
        Assembler(string csvLoc);

        void PrintCSVContent();
        void Build();

    private:
        //csv list objects
        Symbols *symbol;
        Instructions *instruct;
        Symtable *symtable;

        deque<Method> mList;

        OPCODES op;

        int stringIterator;
        int labelIterator;
        int paramCounter;

        void PrintHeaderInfo();

        void DeclareGlobals();
        //this function searches for strings in symbol list, gives each a unique id
        //then searches the instruction list and replaces string id's with newly
        //created unique id's so that when we parse instructions we have references
        void DeclareStrings();
        void ReplaceNameInInstructions(string id, string newID);
        void RemoveAssignInstruct();

        void LoadMethodVariables();

        void FixLabels();

        void CreateGotoLabels();

        void ParseInstructions();

        void GetCommandLineArgs();//????????????????????

        void PrintLabel(string label);

        //assembly instructions generation
        void AddSub(bool isAdd, instructEntry s);
        void MulDiv(bool isMul, instructEntry s);
        void Goto(instructEntry s);
        void ConditionalJump(int cond, instructEntry s);
        void ReadWrite(bool isRead, instructEntry s);
        void Assign(instructEntry s);
        void Param(instructEntry s);
        void Call(instructEntry s);
        void Ret(instructEntry s);

        string getNewString();
        string getNewLabel();

        bool is_number( std::string token );
        
        //returns original name of variable
        string FindVarName(string offset);

};



#endif