#ifndef DEFINES_PARSER_H
#define DEFINES_PARSER_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <regex>
#include <vector>
#include <io.h>

// okay. really puked when i saw this. do u even oop
// i don't really want to modify too much of your code


PIMAGE_DOS_HEADER			dosHeader;
PIMAGE_NT_HEADERS			ntHeaders;
IMAGE_FILE_HEADER			fileHeader;
PIMAGE_THUNK_DATA			thunkData;
IMAGE_OPTIONAL_HEADER		optionalHeader;
PIMAGE_SECTION_HEADER		sectionHeader;
PIMAGE_IMPORT_DESCRIPTOR	importDescriptor;

//x64 stuff
PIMAGE_NT_HEADERS64			ntHeaders64;
IMAGE_OPTIONAL_HEADER64		optionalHeader64;
//x86 stuff
PIMAGE_NT_HEADERS32			ntHeaders32;
IMAGE_OPTIONAL_HEADER32		optionalHeader32;

HWND hConsole = GetConsoleWindow();
HANDLE hFile, hMemObject, hBase;
DWORD dwImpDir, dwSectionC, dwSec, dwRawOff;
RECT s;

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::smatch;
using std::regex;

#endif
