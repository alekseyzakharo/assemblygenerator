#include "assembler.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

ofstream assemblerFile;



Assembler::Assembler()
{
    Assembler("");
}

Assembler::Assembler(string csvLoc)
{
    symbol = new Symbols(csvLoc);
    instruct = new Instructions(csvLoc);
    symtable = new Symtable(csvLoc); 

    stringIterator = 0;
}


void Assembler::PrintCSVContent()
{
    symbol->Print();
    instruct->Print();
    symtable->Print();
}

void Assembler::Build()
{
    //print the header
    PrintHeaderInfo();
    printf("\t.global main\n");
    printf("\t.data\n\n");
    DeclareStrings();

    cout<<endl<<endl<<endl<<endl;
}


void Assembler::PrintHeaderInfo()
{
    printf("#-----------------------------------------------------------------------------\n");
    printf("# Created By: Aleksey Zakharov 301295506 \n");
    printf("#-----------------------------------------------------------------------------\n");
}


void Assembler::DeclareGlobals()
{

}


void Assembler::DeclareStrings()
{
    for(symbolEntry s: symbol->list)
    {
        if(s.type.compare("STR") == 0)
        {
            //create unique string identifier
            string uniqueID = "s" + to_string(stringIterator++);
            cout<< uniqueID <<": .ascii " << s.name << endl; 

            //replace newly created string identifier into instructions 
            for(instructEntry n: instruct->list)
            {
                if(n.op1.compare(s.id))
                {
                    n.op1 = uniqueID;
                }
                else if(n.op2.compare(s.id))
                {
                    n.op2 = uniqueID;
                }
                else if(n.res.compare(s.id))
                {
                    n.res = uniqueID;
                }
            }
        }
    }
}