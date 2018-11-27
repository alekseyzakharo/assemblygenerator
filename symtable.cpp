#include "symtable.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Symtable::Symtable()
{
    Symtable("");
}

Symtable::Symtable(string fileLocation)
{
    openAndRead(fileLocation);
}

