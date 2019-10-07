#ifndef PORTABLEEXECTUABLE_H
#define PORTABLEEXECTUABLE_H

#include <Windows.h>
#include <vector>

class PortableExecutable
{
public:

    PortableExecutable( BYTE *pMoudle, DWORD dwSize );
    PortableExecutable( wchar_t *pFilePath );

    BYTE *GetModule( );
    DWORD GetModuleSize( );
    bool GetIsValidPE( );

    bool GetIs32( );
    bool GetIs64( );

    struct ExportEntry
    {
        intptr_t m_Address;
        WORD m_Ordinal;
        char m_Name[128];
    };

    struct ImportEntry
    {
        intptr_t m_Address;
        WORD m_Ordinal;
        char m_Name[128];
        char m_Module[128];
    };

    std::vector<ExportEntry> GetExports( );
    std::vector<ImportEntry> GetImports( );

    IMAGE_DOS_HEADER *GetDosHeader( );
    IMAGE_NT_HEADERS32 *GetNtHeader32( );
    IMAGE_NT_HEADERS64 *GetNtHeader64( );

    IMAGE_DATA_DIRECTORY GetDataDir( DWORD dwIndex );

    IMAGE_SECTION_HEADER *GetEnclosingSectionHeader( DWORD dwRVA );
    void *GetPtrFromRVA( DWORD dwRVA );

private:

    bool Init( BYTE *pModule, DWORD dwSize );

    DWORD m_ModuleSize;
    BYTE *m_pModule;

    IMAGE_DOS_HEADER* m_DosHeader;
    IMAGE_NT_HEADERS32* m_NtHeader32;
    IMAGE_NT_HEADERS64* m_NtHeader64;

    bool m_IsValidPE;
};


#endif