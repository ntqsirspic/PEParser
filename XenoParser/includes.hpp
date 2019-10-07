#ifndef PARSER_GUARD_H
#define PARSER_GUARD_H

#include "defines.hpp"

//I srsly wanted to cut myself when i saw this code...
//I'm sorry, but I had to add my own classes, I couldn't do this with your code anymore ._.

/*

//classes and structs
struct Compiler
{
    int majVer;
    int minVer;
    char *compiler;
    char *pManaged;
};

class Console {
public:
    void AllocConsole( )
    {
        SetConsoleTitleW( L"xenocidewiki's PE Parser" );
        GetWindowRect( hConsole, &s );
        MoveWindow( hConsole, s.left, s.top, 800, 600, TRUE );
    }

    int checkFile( )
    {
        if ( hFile == INVALID_HANDLE_VALUE )
        {
            std::cout << "Unable to open the file" << std::endl;
            return FALSE;
        }
        return TRUE;
    }

    void printInfo( )
    {
        //General Information
        std::cout << std::endl << "Entry Point: " << "0x" << std::uppercase << std::hex << optionalHeader.AddressOfEntryPoint << std::endl;
        std::cout << "Image Base: " << "0x" << std::uppercase << std::hex << optionalHeader.ImageBase << std::endl;
        std::cout << "File Size: " << GetFileSize( hFile, NULL ) << " Bytes" << std::endl;
        std::cout << "Size of Codenz: " << "0x" << std::uppercase << optionalHeader.SizeOfCode << std::endl;
        std::cout << std::endl << "Architecture: ";
    }
}console;

class fileHandling
{
public:
    void mapFile( )
    {
        hMemObject = CreateFileMappingW( hFile, NULL, PAGE_READONLY, NULL, NULL, NULL );
        hBase = MapViewOfFile( hMemObject, FILE_MAP_READ, NULL, NULL, NULL );
    }

    bool validPE( )
    {
        return ntHeaders->Signature == IMAGE_NT_SIGNATURE;
    }

    void GetCompilerByLinker( int majVer, int minVer, bool pManaged ) 
    {
        // Extended dis a lil bit
        const Compiler compiler[] =
        {
            { 15, 0, "Visual Studio '15'", pManaged ? " (.NET)" : " (C++)" },
            { 14, 0, "Visual Studio 2015", pManaged ? " (.NET)" : " (C++)" },
            { 12, 0, "Visual Studio 2013", pManaged ? " (.NET)" : " (C++)" },
            { 11, 0, "Visual Studio 2012", pManaged ? " (.NET)" : " (C++)" },
            { 10, 0, "Visual Studio 2010", pManaged ? " (.NET)" : " (C++)" },
            { 9, 0, "Visual Studio 2008", pManaged ? " (.NET)" : " (C++)" },
            { 8, 0, "Visual Studio 2005", pManaged ? " (.NET)" : " (C++)" },
            { 7, 1, "Visual Studio .NET 2003", pManaged ? " (.NET)" : " (C++)" },
            { 7, 0, "Visual Studio .NET 2002", pManaged ? " (.NET)" : " (C++)" },
            { 6, 0, "Visual Studio 6.0", NULL },
            { 5, 0, "Visual Studio 97", NULL },
            { 2, 25, "Delphi", NULL },
            { 2, 56, "MinGW", NULL },
            { 1, 71, "Fasm", NULL },
        };

        for ( const Compiler& comp : compiler )
        {
            if ( comp.majVer == majVer && comp.minVer == minVer )
            {
                cout << "Compiler: " << comp.compiler << comp.pManaged;
                return;
            }
        }

        cout << "Unknown Linker ( Major: " << "0x" << majVer << ", Minor: " << "0x" << minVer << " )";
    }

    int checkArchitecture( string arch )
    {
        switch ( optionalHeader.Magic )
        {
        case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
            arch = "x86";
            break;
        case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
            arch = "x64";
            break;
        default:
            arch = "?";
            break;
        }

        std::cout << arch;
        return 0;
    }

    void getInfo( )
    {
        // Not sure where you got this from, however, this does not match with the actual 
        // winnt definitions
        // PROCESSOR_INTEL_386 (386) != 0x14c (332)


        //Target Machine
        cout << endl << "Target Machine: ";
        switch ( fileHeader.Machine )
        {
        case 0x0:
            std::cout << "Any Machine Type";
            break;
        case 0x184:
            std::cout << "Alpha AXP";
            break;
        case 0x1c0:
            std::cout << "ARM";
            break;
        case 0x284:
            std::cout << "Alpha AXP 64-bit";
            break;
        case 0x14c:
            std::cout << "Intel 386";
            break;
        case 0x200:
            std::cout << "Intel IA64";
            break;
        case 0x268:
            std::cout << "Motorola 68000 series";
            break;
        case 0x266:
            std::cout << "MIPS16";
            break;
        case 0x366:
            std::cout << "MIPS with FPU";
            break;
        case 0x466:
            std::cout << "MIPS16 with FPU";
            break;
        case 0x1f0:
            std::cout << "Power PC, little endian";
            break;
        case 0x162:
            std::cout << "MIPS R3000";
            break;
        case 0x166:
            std::cout << "MIPS little endian";
            break;
        case 0x168:
            std::cout << "R10000";
            break;
        case 0x1a2:
            std::cout << "Hitachi SH3";
            break;
        case 0x1a6:
            std::cout << "Hitachi SH4";
            break;
        case 0x1c2:
            std::cout << "THUMB";
            break;
        default:
            std::cout << "---";
            break;
        }

        //File Type
        cout << endl << "File Type: ";
        if ( fileHeader.Characteristics & IMAGE_FILE_DLL )
            cout << "DLL";
        else
            cout << "Executable File";

        //Subsystem


        //File Subsystem + Optional Stuff
        cout << endl << "File Subsystem: ";
        switch ( optionalHeader.Subsystem )
        {
        case 1:
            cout << "Device Driver";
            break;
        case 2:
            cout << "Windows GUI";
            break;
        case 3:
            cout << "Windows CLI";
            break;
        case 7:
            cout << "Posix";
            break;
        case 9:
            cout << "Windows CE";
            break;
        case 10:
            cout << "EFI";
            break;
        case 11:
            cout << "EFI Driver (Boot Serivices)";
            break;
        case 12:
            cout << "EFI Driver (Runtime Services)";
            break;
        default:
            cout << "Unknown";
            break;
        }

        cout << endl << endl << "Number of Sections: " << fileHeader.NumberOfSections << endl;
        std::cout << "Number of Entries in Symbol Table: " << fileHeader.NumberOfSymbols << endl;
        std::cout << "Size of Optional Header: " << "0x" << std::hex << fileHeader.SizeOfOptionalHeader << endl;
    }

    //Can do better for sure D:
    void getCompiler( ) 
    {
        if ( optionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC )
        {
            ntHeaders64 = ( PIMAGE_NT_HEADERS64 )( ( uintptr_t )( dosHeader )+( dosHeader->e_lfanew ) );
            optionalHeader64 = ntHeaders64->OptionalHeader;
            bool managed = optionalHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size > 0 && optionalHeader64.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress != 0;
            GetCompilerByLinker( optionalHeader64.MajorLinkerVersion, optionalHeader64.MinorLinkerVersion, managed );
        }
        else
        {
            ntHeaders32 = ( PIMAGE_NT_HEADERS32 )( ( uintptr_t )( dosHeader )+( dosHeader->e_lfanew ) );
            optionalHeader32 = ntHeaders32->OptionalHeader;
            bool managed = optionalHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].Size > 0 && optionalHeader32.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress != 0;
            GetCompilerByLinker( optionalHeader32.MajorLinkerVersion, optionalHeader32.MinorLinkerVersion, managed );
        }
    }
}file;

class parseHeaders 
{
public:
    void getDosHeader( ) 
    {
        dosHeader = static_cast< PIMAGE_DOS_HEADER >( hBase ); // either stick to c styled or c++ styled cast, but dont mix them >.<
    }

    void getNtHeader( ) 
    {
        getDosHeader( );
        ntHeaders32 = ( PIMAGE_NT_HEADERS32 )( ( uintptr_t )( dosHeader )+( dosHeader->e_lfanew ) );
        ntHeaders64 = ( PIMAGE_NT_HEADERS64 )( ( uintptr_t )( dosHeader )+( dosHeader->e_lfanew ) );
    }

    void getImgFileHeader( ) 
    {
        fileHeader = ntHeaders->FileHeader;
    }

    void getOptionalHeader( ) 
    {
        optionalHeader = ntHeaders->OptionalHeader;
    }

    PIMAGE_SECTION_HEADER getSectionHeader( ) 
    {
    }

    int getImports( ) 
    {
    }

}Headers;
*/

#endif

