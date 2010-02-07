// Module Name: wHuffmanApp.cc
// Objective: demonstrate the application of huffman coding tree 
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Platform: Win32
// Revision: alpha

#include <windows.h>
#include <windef.h>
#include <tchar.h>
#include <stdio.h>
#include <bitset>
#include <cmath>
#include "HuffmanTree.h"
#include "BitSet.h"
#include "YmFile.h"
#include "wError.h"

typedef unsigned long long QWORD;
typedef QWORD* PQWORD;

BOOL compress(LPCTSTR infile, LPCTSTR outfile, 
			  PQWORD pqwSrcFileSize, PQWORD pqwDestFileSize) {

	HANDLE hInFile = CreateFile(infile, GENERIC_READ, 
					FILE_SHARE_READ | FILE_SHARE_WRITE, 
					NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	HANDLE hOutFile = CreateFile(outfile, GENERIC_WRITE | GENERIC_READ, 
					FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL, CREATE_ALWAYS, NULL, NULL); // TODO: CREATE_ALWAYS --> CREATE_NEW	
	if (hInFile == INVALID_HANDLE_VALUE || hOutFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dwInFileSizeHigh;
	DWORD dwInFileSizeLow = GetFileSize(hInFile, &dwInFileSizeHigh);
	QWORD qwInFileSize = dwInFileSizeHigh << 32 | dwInFileSizeLow;
	*pqwSrcFileSize = qwInFileSize;
	
	// create the file mapping
	HANDLE hInFileMap = CreateFileMapping(hInFile, NULL, 
						PAGE_READONLY, 0, 0, NULL);
	if (hInFileMap == NULL)
		return FALSE;
	
	// map view of the entire file 
	PBYTE idata = (BYTE*)MapViewOfFile(hInFileMap, FILE_MAP_READ, 0, 0, 0);

	// build the charset-weight table
	UCHAR charTb[256];
	for (int i = 0; i < 256; i++)
		charTb[i] = i;
	DWORD wtTb[256] = {0};
	for (DWORD i = 0; i < qwInFileSize; i++)
		wtTb[idata[i]]++;

	// create the huffman coding tree
	HuffmanTree tree((const uchar*)charTb, (const uint*)wtTb, 256);
	
	// retrive code and len table
	BitSet** codeTb = tree.getCodeTable();
	DWORD* lenTb = (DWORD*)tree.getLenTable();

	// create the compressed file
	QWORD qwOutFileSize = 0;
	QWORD qwOutFileBits = 0;
	const WORD wLenTableSize = 256;
	OWRD wCodeTableSize = 0;

	for (uint i = 0; i < 256; i++) {
		qwOutFileBits += wtTb[i] * lenTb[i];
		wCodeTableSize += codeTb[i];
	}
	wCodeTableSize = ceil(double(wCodeTableSize / 8));

	qwOutFileSize = ceil((double)qwOutFileBits / 8) + wCodeTableSize + wLenTableSize + 10; 

	hOutFileMap = CreateFileMapping(hOutFile, NULL, PAGE_READWRITE,
									(DWORD)qwOutFileSize >> 32,(DWORD)qwOutFileSize, NULL);
    if (hOutFileMap == NULL)
		return FALSE;
	
	PBYTE odata = MapViewOfFile(hOutFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (odata == NULL)
		return FALSE;

	WORD wStartOffset = 8 + wLenTableSize + wCodeTableSize;
	memcpy(odata, qwSrcFileSize, 8);
	memcpy(odata + 8, wStartOffset, 2);
	for (uchar i = 0; i < 256; i++)
	BitWrap outBitArr(odata);
	
	for (QWORD bitpos = 
		for (DWORD i = 0; i < dwBytesInBlock; i++) {
			uint codelen = lenTb[idata[i]];
			int codepos;  
			DWORD datapos;

			for (dpos = 0, cpos = 0; dpos < clen; 
						dpos++, cpos++) 
				outBitArr.set(dpos, codeTb[idata[i]]->get(cpos));
			dpos += clen;
		}

		idata += dwBytesInBlock;
		qwInFileSize -= dwBytesInBlock;
	}

	// fill in the file header

	return TRUE; 
}

BOOL decompress(LPCTSTR infile, LPCTSTR outfile, 
				PDWORD pdwSrcFileSize, PDWORD pdwDestFileSize) {

	return TRUE;
}

int _tmain(int argc, TCHAR* argv[]) {
	if (argc != 4) {
		printf("Usage: HuffmanApp -c | -d srcFileName destFileName \n");
		return -1;
	} 

	TCHAR opt = argv[1][1];

	if (opt == TEXT('c') || opt == TEXT('C')) {
		QWORD qwSrcFileSize, qwDestFileSize;
		if (compress(argv[2], argv[3], &qwSrcFileSize, &qwDestFileSize)) {
			printf("Compress succeed! source file : %I64d KBs dest file : %I64d KBs", qwSrcFileSize / 1024, qwDestFileSize / 1024);
			return 0;
		} else {
			printf("Compress failed! %s", getErrMsg());
			return -1;
		}
	} else if (opt == TEXT('d') || opt == TEXT('D')) {
		DWORD dwSrcSize, dwDestSize;
		if (decompress(argv[2], argv[3], &dwSrcSize, &dwDestSize)) {
			printf("DeCompress succeed! source file : %ld KBs dest file : %ld KBs", dwSrcSize / 1024, dwDestSize / 1024);
			return 0;
		} else {
			printf("DeCompress failed");
			return -1;
		}
	}
}
