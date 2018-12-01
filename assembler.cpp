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

    DeclareGlobals();
    DeclareStrings();
    //remove assignment instructions above the first label
    RemoveAssignInstruct();
    //we know at this point that the next instructions is a label for a function



    cout<<endl<<endl;

    printf("\t.text\n\n");


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
    while(true)
    {
        symbolEntry s = symbol->list.front();
        if(s.type.compare("LABEL") == 0)
        {
            return;
        }
        else if(s.scope.compare("GLOBAL") == 0)
        {
            if(s.isArray.compare("true") == 0)
            {
                int arrSize;
                stringstream(s.arrSize)>>arrSize;
                string zeros = "";
                for(int i =0;i<arrSize-1;i++)
                {
                    zeros += "0, ";
                }
                zeros += "0";
                cout<<s.name<<": .quad "<<zeros<<endl;
            }
            else
            {
                cout<<s.name<<": .quad 0"<<endl;
            }
            ReplaceNameInInstructions(s.id,s.name);
        }
        else if(s.scope.compare("CONST") == 0)
        {
            //this one must be a global variable that the const is being set to
            symbolEntry n = symbol->list.at(1);
            
            cout<<n.name<<": .quad "<<s.name<<endl;
            
            ReplaceNameInInstructions(n.id,n.name);

            symbol->list.pop_front();
        }
        symbol->list.pop_front();
    }  
}


void Assembler::DeclareStrings()
{
    int i = 0;
    while(true)
    {
        if(i == symbol->list.size())
        {
            return;
        }
        symbolEntry s = symbol->list.at(i);
        if(s.type.compare("STR") == 0)
        {
            //create unique string identifier
            string uniqueID = "s" + to_string(stringIterator++);
            cout<< uniqueID <<": .ascii " << s.name << endl; 

            //replace newly created string identifier into instructions 
            ReplaceNameInInstructions(s.id,uniqueID);
            //remove the symbol from the list
            symbol->RemoveFromList(s.id);
            continue;
        }
        i++;
    }
}

void Assembler::ReplaceNameInInstructions(string id, string newID)
{
    for(instructEntry n: instruct->list)
    {
        if(n.op1.compare(id) == 0)
        {              
            instruct->SetOp1(n.id, newID);
        }
        else if(n.op2.compare(id) == 0)
        {
            instruct->SetOp1(n.id, newID);
        }
        else if(n.res.compare(id) == 0)
        {
            instruct->SetRes(n.id, newID);
        }
    
    }
}

void Assembler::RemoveAssignInstruct()
{
    while(true)
    {
        instructEntry s = instruct->list.front();
        if(s.opcode.compare("LABEL") == 0)
        {
            return;
        }
        if(s.opcode.compare("ASSIGN") == 0)
        {
            instruct->list.pop_front();
        }
    }
}

void GetCommandLineArgs()
{
    
}


void Assembler::PrintLabel(string label)
{
    cout<<label<<":"<<endl;
}

void Assembler::GlobalAssignment()
{
    
}