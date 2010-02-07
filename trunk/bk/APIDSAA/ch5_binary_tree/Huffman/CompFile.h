// Module Name: CompFile.h
// Objective: provide the struct definition for YM compress file format
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#ifndef __YM_HEADER__
#define __YM_HEADER__

typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;
typedef __int64 qword;

static const word YM_MAGIC = 0x4d59; // 'YM'
static const word YM_VERSION = 0x0100; // 1

struct YM_FILE_HEADER {
	word Magic;
	word Version;
	word HeaderSize;

	dword FileSize;
	qword BitSize; // only here count by bit
	word TableSize;
};

#endif
