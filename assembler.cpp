#include "assembler.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

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
    labelIterator = 0;
    paramCounter = 0;
}


void Assembler::PrintCSVContent()
{
    symbol->Print();
    cout<<endl;
    instruct->Print();
    cout<<endl;
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

    LoadMethodVariables();
    //at this point we have the instruction list that has all symbols replaced
    //by the correct literal value for them

    FixLabels();

    CreateGotoLabels();

    cout<<endl<<endl;

    printf("\t.text\n\n");

    ParseInstructions();

    //cout<<endl<<endl<<endl<<endl;

    // for(int i = 0;i<mList.size();i++)
    // {
    //     Method s = mList.at(i);
    //     cout<<"METHOD: "<<s.name << " TOTALSIZE: " << to_string(s.size)<<endl;
    //     for(int j = 0;j<s.list.size();j++)
    //     {
    //         cout<<s.list.at(j).name<<" "<<s.list.at(j).offset<<endl;
    //     }
    //     cout<<endl;
    // }

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
            string uniqueID = getNewString();
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
    int i = 0;
    while(i < instruct->list.size())
    {
        instructEntry n = instruct->list.at(i);
        
        if(n.op1.compare(id) == 0)
        {              
            instruct->SetOp1(n.id, newID);
            continue;
        }
        if(n.op2.compare(id) == 0)
        {
            instruct->SetOp2(n.id, newID);
            continue;
        }
        if(n.res.compare(id) == 0 && !(n.opcode.compare("LT") == 0 ) && !(n.opcode.compare("GT") == 0) && !(n.opcode.compare("LE") == 0) && !(n.opcode.compare("GE") == 0 ) && !(n.opcode.compare("EQ") == 0) && !(n.opcode.compare("NE") == 0 ) && !(n.opcode.compare("GOTO") == 0))
        {
            instruct->SetRes(n.id, newID);
        }
        i++;
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

void Assembler::LoadMethodVariables()
{
    for(int i = 0 ;i < symbol->list.size();i++)
    {
        symbolEntry methodLabel = symbol->list.at(i);
        if(methodLabel.type.compare("LABEL") == 0)
        {
            mList.push_back(Method(methodLabel.name));
            i++;
            while(i < symbol->list.size())
            {
                symbolEntry s = symbol->list.at(i);
                if(s.scope.compare("LABEL") == 0)
                {
                    i--; //the for loop will add one so we need to decrement
                    break;
                }
                else if(s.scope.compare("LOCAL") == 0)
                {
                    mList.back().size += VARBYTESIZE;
                    string offset = "-" + to_string(mList.back().size) + "(%rbp)";
                    mList.back().list.push_back(localVariable(s.name,offset));
                    ReplaceNameInInstructions(s.id, offset);
                }
                else if(s.scope.compare("CONST") == 0)
                {
                    ReplaceNameInInstructions(s.id, "$"+s.name);
                }
                i++;
            }
        }
    }
}

void Assembler::FixLabels()
{
    for(int i = 0; i < instruct->list.size() ; i++)
    {
        instructEntry s = instruct->list.at(i);
        if(s.opcode.compare("LABEL") == 0)
        {
            instruct->SetRes(s.id, symbol->GetName(s.res));
        }
    }
}

void Assembler::CreateGotoLabels()
{
    int i = 0;
    int size = instruct->list.size();
    string labelStr;
    while(i < size)
    {
        instructEntry s = instruct->list.at(i);
        if(is_number(s.res))
        {
            if(s.opcode.compare("LT") == 0 || s.opcode.compare("GT") == 0 || s.opcode.compare("LE") == 0 || s.opcode.compare("GE") == 0 || s.opcode.compare("EQ") == 0 || s.opcode.compare("NE") == 0 || s.opcode.compare("GOTO") == 0)
            {
                labelStr = getNewLabel();
                instruct->SetRes(s.id, labelStr);
                instruct->InsertLabel(s.res, labelStr);
                i = 0;
            }
        }
        i++;   
    }
}   


void Assembler::ParseInstructions()
{
    int size = instruct->list.size();
    for(int i = 0;i < size;i++)
    {
        instructEntry s = instruct->list.at(i);


        if(s.opcode.compare("LABEL") == 0)
        {
            PrintLabel(s.res);
            if(s.res.compare("main") == 0)
            {
                GetCommandLineArgs();
            }
        }
        else if(s.opcode.compare("ADD") == 0)
        {
            AddSub(true, s);
        }
        else if(s.opcode.compare("SUB") == 0)
        {
            AddSub(false, s);
        }
        else if(s.opcode.compare("MUL") == 0)
        {
            MulDiv(true, s);
        }
        else if(s.opcode.compare("DIV") == 0)
        {
            MulDiv(false, s);
        }
        else if(s.opcode.compare("GOTO") == 0)
        {
            Goto(s);
        }
        else if(s.opcode.compare("LT") == 0)
        {
            ConditionalJump(0, s);
        }
        else if(s.opcode.compare("GT") == 0)
        {
            ConditionalJump(1, s);
        }
        else if(s.opcode.compare("LE") == 0)
        {
            ConditionalJump(2, s);
        }
        else if(s.opcode.compare("GE") == 0)
        {
            ConditionalJump(3, s);
        }
        else if(s.opcode.compare("EQ") == 0)
        {
            ConditionalJump(4, s);
        }
        else if(s.opcode.compare("NE") == 0)
        {
            ConditionalJump(5, s);
        }
        else if(s.opcode.compare("READ") == 0)
        {
            ReadWrite(true, s);
        }
        else if(s.opcode.compare("WRITE") == 0)
        {
            ReadWrite(false, s);
        }
        else if(s.opcode.compare("ASSIGN") == 0)
        {
            Assign(s);
        }
        else if(s.opcode.compare("PARAM") == 0)
        {
            Param(s);
        }
        else if(s.opcode.compare("CALL") == 0)
        {
            Call(s);
        }
        else if(s.opcode.compare("RET") == 0)
        {
            Ret(s);
        }
    }
}

void Assembler::GetCommandLineArgs()
{
    string argc = "";
    string argv = "";
    int size = mList.size();
    for(int i = 0 ; i < size ; i++)
    {
        if(mList.at(i).name.compare("main") == 0)
        {
            argv = mList.at(i).FindOffset("argv");
            argc = mList.at(i).FindOffset("argc");
            break;
        }
    }
    
    cout<<"\t"<<"mov\t%rdi, "<<argc<<endl;
    cout<<"\t"<<"mov\t%rsi, "<<argv<<endl;
}


void Assembler::PrintLabel(string label)
{
    cout<<label<<":"<<endl;
}

void Assembler::AddSub(bool isAdd, instructEntry s)
{
    cout<<"\t"<<"mov\t"<<s.op1<<", %rax"<<endl;
    cout<<"\t"<<"mov\t"<<s.op2<<", %rbx"<<endl;
    if(isAdd)
    {
        cout<<"\t"<<"add\t%rax, %rbx"<<endl;
    }
    else
    {
        cout<<"\t"<<"sub\t%rax, %rbx"<<endl;
    }
    cout<<"\t"<<"mov\t"<<"%rbx, "<<s.res<<endl;
}

void Assembler::MulDiv(bool isMul, instructEntry s)
{
    cout<<"\t"<<"mov\t"<<s.op1<<", %rax"<<endl;
    cout<<"\t"<<"mov\t"<<s.op2<<", %rbx"<<endl;
    if(isMul)
    {
        cout<<"\t"<<"mul\t%rbx"<<endl;
    }
    else
    {
        cout<<"\t"<<"idiv\t%rbx"<<endl;
    }
    cout<<"\t"<<"mov\t"<<"%rax, "<<s.res<<endl;
}

void Assembler::Goto(instructEntry s)
{
    cout<<"\t"<<"jmp\t"<<s.res<<endl;
}

void Assembler::ConditionalJump(int cond, instructEntry s)
{
    cout<<"\t"<<"mov\t"<<s.op1<<", %rax"<<endl;
    cout<<"\t"<<"mov\t"<<s.op2<<", %rbx"<<endl;
    cout<<"\t"<<"cmp\t%rax, %rbx"<<endl;
    switch(cond)
    {
        case 0: //less than
            cout<<"\t"<<"jl "<<s.res<<endl;
        break;
        case 1: //greather than
            cout<<"\t"<<"jg "<<s.res<<endl;
        break;
        case 2: //less than or equal to
            cout<<"\t"<<"jle "<<s.res<<endl;
        break; 
        case 3: //greather than or equal to
            cout<<"\t"<<"jge "<<s.res<<endl;
        break;
        case 4: //equal
            cout<<"\t"<<"je "<<s.res<<endl;
        break;
        case 5: //ne
            cout<<"\t"<<"jne "<<s.res<<endl;
        break;
        default:
        break;
    }
}

void Assembler::ReadWrite(bool isRead, instructEntry s)
{
    string offset = "";
    string varName = FindVarName(s.op2);
    if(varName.compare("OFFSETTMP") == 0)
    {
        instructEntry tmp = instruct->GetByRes(s.op2);
        if(!tmp.op1.empty() && !tmp.op2.empty())
        {
            string str1 = tmp.op1.substr(1, tmp.op1.size());
            string str2 = tmp.op2.substr(1, tmp.op2.size());
            int a = 0; 
            int b = 0;
            stringstream(str1)>>a;
            stringstream(str2)>>b;
            offset = to_string(a*b);
        }
    }

    if(isRead)
    {
        //cout<<"\t"<<"mov "<<s.op2<<", %rax"<<endl; //offset into rax
        cout<<"\t"<<"mov\t"<<s.op1<<", %rbx"<<endl; 
        cout<<"\t"<<"mov\t"<<offset<<"(%rbx), "<<"%rax"<<endl;
        cout<<"\t"<<"mov\t"<<"%rax, "<<s.res<<endl; 
    }
    else
    {
        //cout<<"\t"<<"mov "<<s.op2<<", %rax"<<endl; //offset into rax
        cout<<"\t"<<"mov\t"<<s.res<<", %rbx"<<endl; 
        cout<<"\t"<<"mov\t"<<s.op1<<", %rax"<<endl;
        cout<<"\t"<<"mov\t%rax, "<<offset<<"(%rbx)"<<endl;
    }
}

void Assembler::Assign(instructEntry s)
{
    cout<<"\t"<<"mov\t"<<s.op1<<", %rax"<<endl;
    cout<<"\t"<<"mov\t%rax, "<<s.res<<endl;
}

void Assembler::Param(instructEntry s)
{
    string reg;
    switch(paramCounter)
    {
        case 0:
            cout<<"\t"<<"mov\t"<<s.op1<<", "<<"%rdi"<<endl;
        break;
        case 1:
            cout<<"\t"<<"mov\t"<<s.op1<<", "<<"%rsi"<<endl;
        break;
        case 2:
            cout<<"\t"<<"mov\t"<<s.op1<<", "<<"%rdx"<<endl;
        break;
        case 3:
            cout<<"\t"<<"mov\t"<<s.op1<<", "<<"%rcx"<<endl;
        break;
        case 4:
            cout<<"\t"<<"mov\t"<<s.op1<<", "<<"%r8"<<endl;
        break;
        case 5:
            cout<<"\t"<<"mov\t"<<s.op1<<", "<<"%r9"<<endl;
        break;
        default: //unspecified behaviour after 6 parameters
        break;
    }
    paramCounter++;
}

void Assembler::Call(instructEntry s)
{
    paramCounter = 0;
    cout<<"\t"<<"call\t"<<s.op1<<endl;
}

void Assembler::Ret(instructEntry s)
{
    if(!is_number(s.op1))
    {
        cout<<"\t"<<"mov\t"<<s.op1<<", "<<"%rax"<<endl;
    }
    cout<<"\t"<<"ret"<<endl;
}

string Assembler::getNewString()
{
    return "s" + to_string(stringIterator++);
}

string Assembler::getNewLabel()
{
    return "L" + to_string(labelIterator++);
}

bool Assembler::is_number( std::string token )
{
    return std::regex_match( token, std::regex( ( "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?" ) ) );
}

string Assembler::FindVarName(string offset)
{
    string tmp = "";
    int size = mList.size();
    for(int i =0;i<size;i++)
    {
        Method m = mList.at(i);
        string tmp = m.FindName(offset);
        if(!tmp.empty())
        {
            return tmp;
        }
    }
    return tmp;
}

