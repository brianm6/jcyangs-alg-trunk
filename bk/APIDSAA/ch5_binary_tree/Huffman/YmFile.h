// Module Name: YmFile.h
// Objective: provide the struct definition for YM compress file format
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#ifndef __YM_FILE_HEADER__
#define __YM_FILE_HEADER__

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;
typedef unsigned long long qword;

static const word YM_MAGIC = 0x4d59; // 'YM'
static const word YM_VERSION = 0x0100; // 1
static const dword YM_PART_HEADER_SIZE = 8; 

struct YM_FILE_COMPRESS_TABLE {
	byte LengthTable[256];
	byte CodeTable[];
};

struct YM_DIRECTORY_TABLE {
	word DirHeaderCount;
	word FileHeaderCount;
	YM_DIRECTORY_TABLE* SubDirTable[];
};

struct YM_FILE_HEADER {
	word Magic;
	word Version;
	dword HeaderSize;

	YM_DIRECTORY_TABLE HeaderTable;
};

#endif
