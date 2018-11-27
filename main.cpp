#include <iostream>
#include "symbols.h"
#include "instructions.h"
#include "symtable.h"

using namespace std;

int main(){

    Symbols s("");
    Instructions i("");
    Symtable st("");


    s.Print();
    i.Print();
    st.Print();
}