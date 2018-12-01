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

        int stringIterator;

        void PrintHeaderInfo();

        void DeclareGlobals();
        void ReplaceNameInInstructions(string id, string newID);
        void RemoveAssignInstruct();

        //this function searches for strings in symbol list, gives each a unique id
        //then searches the instruction list and replaces string id's with newly
        //created unique id's so that when we parse instructions we have references
        void DeclareStrings();

        void GetCommandLineArgs();//????????????????????

        void PrintLabel(string label);
        void GlobalAssignment();



};



#endif