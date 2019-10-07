#ifndef PARSER_H
#define PARSER_H

#include <Windows.h>
#include <iostream>
#include "PortableExecutable.h"

class PEParser
{
public:
    PEParser( );

    static PEParser &GetInstance( );

    bool DoParse( PortableExecutable *pPortableExecutable );

private:
    char *GetCompiler( PortableExecutable *pPortableExecutable );
    char *GetSubystem( PortableExecutable *pPortableExecutable );
};

#endif
