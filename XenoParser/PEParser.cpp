#include "PEParser.h"

#define GetPE( pe, object ) \
    ( pe->GetIs32( ) ? pe->GetNtHeader32( )->object : pe->GetNtHeader64( )->object ) 

PEParser::PEParser( )
{
}

PEParser &PEParser::GetInstance( )
{
    static PEParser instance;
    return instance;
}

bool PEParser::DoParse( PortableExecutable *pPortableExecutable )
{
    if ( !pPortableExecutable->GetModule( ) )
    {
        printf( "Can't read file\n" );
        return false;
    }

    if ( !pPortableExecutable->GetIsValidPE( ) )
    {
        printf( "Invalid PE\n" );
        return false;
    }

    printf( "Image Base:            0x%X\n", GetPE( pPortableExecutable, OptionalHeader.ImageBase ) );
    printf( "Entry Point:           0x%X\n", GetPE( pPortableExecutable, OptionalHeader.ImageBase ) + GetPE( pPortableExecutable, OptionalHeader.AddressOfEntryPoint ) );

    printf( "Raw Size:              0x%X\n", pPortableExecutable->GetModuleSize( ) );
    printf( "Virtual Size:          0x%X\n", GetPE( pPortableExecutable, OptionalHeader.SizeOfImage ) );

    printf( "Architecture:          %s\n", pPortableExecutable->GetIs32( ) ? "x86" : "x64" );
    printf( "Compiler:              %s\n", this->GetCompiler( pPortableExecutable ) );
    printf( "Subsystem:             %s\n", this->GetSubystem( pPortableExecutable ) );
    printf( ".NET:                  %s\n", pPortableExecutable->GetDataDir( IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ).Size > 0 ? "true" : "false" );

    return true;
}

char *PEParser::GetSubystem( PortableExecutable *pPortableExecutable )
{
    switch ( GetPE( pPortableExecutable, OptionalHeader.Subsystem ) )
    {
    case IMAGE_SUBSYSTEM_UNKNOWN:
        return "Unknown";
    case IMAGE_SUBSYSTEM_NATIVE:
        return "Device Driver";
    case IMAGE_SUBSYSTEM_WINDOWS_GUI:
        return "Windows GUI";
    case IMAGE_SUBSYSTEM_WINDOWS_CUI:
        return "Windows Console App";
    // ...
    default:
        return "?";
    }
}

char *PEParser::GetCompiler( PortableExecutable *pPortableExecutable )
{
    struct CompilerInfo
    {
        int majVer;
        int minVer;
        char *compiler;
    };

    const CompilerInfo compiler[] =
    {
        { 15, 0, "Visual Studio '15'" },
        { 14, 0, "Visual Studio 2015" },
        { 12, 0, "Visual Studio 2013" },
        { 11, 0, "Visual Studio 2012" },
        { 10, 0, "Visual Studio 2010" },
        { 9, 0, "Visual Studio 2008" },
        { 8, 0, "Visual Studio 2005" },
        { 7, 1, "Visual Studio .NET 2003" },
        { 7, 0, "Visual Studio .NET 2002" },
        { 6, 0, "Visual Studio 6.0" },
        { 5, 0, "Visual Studio 97" },
        { 2, 25, "Delphi" },
        { 2, 56, "MinGW" },
        { 1, 71, "Fasm" }
    };

    for ( const CompilerInfo& comp : compiler )
    {
        if ( comp.majVer == GetPE( pPortableExecutable, OptionalHeader.MajorLinkerVersion ) && comp.minVer == GetPE( pPortableExecutable, OptionalHeader.MinorLinkerVersion ) )
        {
            return comp.compiler;
        }
    }

    // Free dis later on, but since this is one time use, fuck it.
    char *buffer = new char[64];
    sprintf( buffer, "Unknown (Maj: %i, Min: %i)", GetPE( pPortableExecutable, OptionalHeader.MajorLinkerVersion ), GetPE( pPortableExecutable, OptionalHeader.MinorLinkerVersion ) );

    return buffer;
}