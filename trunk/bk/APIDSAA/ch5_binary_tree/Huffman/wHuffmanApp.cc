// Module Name: wHuffmanApp.cc
// Objective: demonstrate the application of huffman coding tree 
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Platform: Win32
// Revision: alpha
#define _UNICODE
#define UNICODE

#include <windows.h>
#include <windef.h>
#include <tchar.h>
#include <stdio.h>
#include <cmath>
#include "HuffmanTree.h"
#include "BitSet.h"
#include "BitWrap.h"
#include "hwFile.h"
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
	if (hInFile == INVALID_HANDLE_VALUE || hOutFile == INVALID_HANDLE_VALUE) {
		printf("CreateFile infile outfile failed! %s", GetErrMsg());
		return FALSE;
	}

	DWORD dwInFileSizeHigh;
	DWORD dwInFileSizeLow = GetFileSize(hInFile, &dwInFileSizeHigh);
	QWORD qwInFileSize = dwInFileSizeHigh << 32 | dwInFileSizeLow;
	*pqwSrcFileSize = qwInFileSize;
	
	// create the file mapping
	HANDLE hInFileMap = CreateFileMapping(hInFile, NULL, 
						PAGE_READONLY, 0, 0, NULL);
	if (hInFileMap == NULL) {
		printf("CreateFileMapping infile failed! %s", GetErrMsg());
		return FALSE;
	}
	
	// map view of the entire file 
	PBYTE idata = (BYTE*)MapViewOfFile(hInFileMap, FILE_MAP_READ, 0, 0, 0);

	// build the charset-weight table
	DWORD owtTb[256] = {0};
	for (DWORD i = 0; i < qwInFileSize; i++)
		owtTb[idata[i]]++;
	
	UCHAR charTb[256];
	int charpos[256] = { 0 };
	DWORD wtTb[256];
	int tbsize = 0;
	for (int i = 0; i < 256; i++) {
		if (owtTb[i] != 0) {
			charTb[tbsize] = (char)i;
			charpos[i] = tbsize;
			wtTb[tbsize] = owtTb[i];
			tbsize++;
		}
	}

	// create the huffman coding tree
	HuffmanTree tree((const uchar*)charTb, (const uint*)wtTb, tbsize);

	// retrive code and len table
	BitSet** tbCode = tree.getCodeTable();
	DWORD* lenTb = (DWORD*)tree.getLenTable();

	// calculate various size
	QWORD qwOutFileSize = 0;
	QWORD qwOutFileBits = 0;
	WORD wLenTableSize = tbsize;
	WORD wCharSetTable = tbsize;
	WORD wCodeTableSize = 0;
	WORD wFilePathSize = _tcslen(hwGetFileName(infile)) * 2 + 4; // add tail null
	const WORD wOtherFieldSize = sizeof(QWORD) * 4 + 2 * sizeof(WORD);
		// include FileHeaderSize,FileOrignalSize,FileCompressedSize, FileBitCount, FileStartOffset, FileCompressTableLen

	for (uint i = 0; i < tbsize; i++) {
		qwOutFileBits += wtTb[i] * lenTb[i];
		wCodeTableSize += lenTb[i]; 
	}
	wCodeTableSize = ceil(double(wCodeTableSize / 8));

	WORD wFileHeaderSize = wFilePathSize + wCodeTableSize + wLenTableSize + wCharSetTable + wOtherFieldSize;


	qwOutFileSize = ceil((double)qwOutFileBits / 8) + wFileHeaderSize; 
	*pqwDestFileSize = qwOutFileSize;

	// create the file map view
	HANDLE hOutFileMap = CreateFileMapping(hOutFile, NULL, PAGE_READWRITE,
									qwOutFileSize >> 32,(DWORD)qwOutFileSize, NULL);
    if (hOutFileMap == NULL) {
		printf("CreateFileMapping outfile failed! %s" , GetErrMsg());
		return FALSE;
	}
	CloseHandle(hOutFile);
	
	PBYTE odata = (PBYTE)MapViewOfFile(hOutFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (odata == NULL) {
		printf("MapViewOfFile outfile failed! %s", GetErrMsg());
		return FALSE;
	}

	// fill in the file header
	*(PWORD)odata = wFileHeaderSize;

	memcpy(odata + 2, infile, wFilePathSize - 4);
	memset(odata + wFilePathSize - 2, 0, 4);

	*(PQWORD)(odata + wFilePathSize + 2) = qwInFileSize;
	*(PQWORD)(odata + wFilePathSize + 10) = qwOutFileSize;
	*(PQWORD)(odata + wFilePathSize + 18) = qwOutFileBits;
	*(PQWORD)(odata + wFilePathSize + 26) = wFileHeaderSize; // qwFileStartOffset
	*(PWORD)(odata + wFilePathSize + 34) = tbsize;
	
	int charset_offset = wFilePathSize + 36;
	int lentable_offset = charset_offset + tbsize;
	for (int i = 0; i < tbsize; i++) {
		odata[charset_offset + i] = charTb[i];
		odata[lentable_offset + i] = lenTb[i];
	}
	
	int codetable_offset = lentable_offset + tbsize;
	BitWrap outBitArr(odata + codetable_offset); // now at code table
	uint64_t cbitpos = 0;
	for (uint i = 0; i < tbsize; i++) {
		uint codelen = lenTb[i];
		for (uint j = 0; j < codelen; j++) 
			outBitArr.set(cbitpos++, tbCode[i]->get(j));
	}

	outBitArr.reset(odata + wFileHeaderSize);
	
	// tree.showCodeTb();
	QWORD bitpos = 0;
	for (QWORD i = 0; i < qwInFileSize; i++)  {
		// cout << idata[i] << "   " << charpos[idata[i]] << "   " << tbCode[charpos[idata[i]]]->toString() << endl;
		outBitArr.set(bitpos, *tbCode[charpos[idata[i]]]);
		bitpos += lenTb[charpos[idata[i]]];
	}
		
	CloseHandle(hInFile);

	UnmapViewOfFile(idata);
	UnmapViewOfFile(odata);

	CloseHandle(hInFileMap);
	CloseHandle(hOutFileMap);

	return TRUE; 
}


BOOL decompress(LPCTSTR infile, LPCTSTR outfile, 
				PQWORD pqwSrcFileSize, PQWORD pqwDestFileSize) {
 	// Load file into memory
	HANDLE hInFile = CreateFile(infile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	HANDLE hOutFile = CreateFile(outfile, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hInFile == INVALID_HANDLE_VALUE || hOutFile == INVALID_HANDLE_VALUE) {
		printf("Cannot create in/out file;%s\n", GetErrMsg());
		return FALSE;
	}

	HANDLE hInFileMap = CreateFileMapping(hInFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hInFileMap == NULL) {
		printf("Cannot create infile file-mapping;%s\n", GetErrMsg());
		CloseHandle(hOutFile);
		return FALSE;
	}

	PBYTE idata = (PBYTE)MapViewOfFile(hInFileMap, FILE_MAP_READ, 0, 0, 0);
	if (idata == NULL) {
		printf("map view of infile map failed;%s\n", GetErrMsg());
		CloseHandle(hOutFile);
		CloseHandle(hInFileMap);
		return FALSE;
	}

	// Set source file size
	DWORD dwInFileSizeHigh = 0;;
	QWORD qwInFileSize = GetFileSize(hInFile, &dwInFileSizeHigh);
	qwInFileSize |= dwInFileSizeHigh << 32;
	*pqwSrcFileSize = qwInFileSize;
	
	CloseHandle(hInFile);
	// build the compress table
	
	PBYTE idata_bak = idata;
	PDWORD tdata = (PDWORD)(idata + 2);
	while (*tdata != 0) {
		idata = idata + 2;
		tdata = (PDWORD)idata;
	}
	*pqwDestFileSize = *(PQWORD)++tdata; // orginal file size
	QWORD qwOutFileSize = *pqwDestFileSize;
	QWORD qwFileBitCount = *(PQWORD)(tdata + 4);
	QWORD qwFileStartOffset = *(PQWORD)(tdata + 6);
	WORD wCodeTableLen = *(PWORD)(tdata + 8);
	WORD tablesize = wCodeTableLen;

	BitSet** codeTb = new BitSet*[tablesize];
	PBYTE charTb = new uchar[tablesize];
	int* lenTb = new int[tablesize];

	PBYTE chartb = (PBYTE)(tdata + 8) + 2;
	PBYTE lentb = chartb + tablesize;
	BitWrap codetb(lentb + tablesize);

	DWORD codebitpos = 0;
	for (uint i = 0; i < tablesize; i++) {
		charTb[i] = chartb[i];
		lenTb[i] = lentb[i];
		codeTb[i] = codetb.getBitSet(codebitpos, lenTb[i]);
		codebitpos += lenTb[i];
	}

	// sort char-length-code table
	for (uint i = 0; i < tablesize - 1; i++) {
		int minpos = i; 
		for (int j = i + 1; j < tablesize; j++) {
			if (lenTb[j] < lenTb[minpos])
				minpos = j;
		}
		if (minpos != i) {
			swap<int>(lenTb[i], lenTb[minpos]);
			swap<uchar>(charTb[i], charTb[minpos]);
			swap<BitSet*>(codeTb[i], codeTb[minpos]);
		}
	}

	 cout << "table size = " << tablesize << endl;	
	 for (uint i = 0; i < tablesize; i++) 
		cout << i << "   " << charTb[i] << "   " << lenTb[i] <<  "   :  " << codeTb[i] << endl;

	// create the out file mapping
	HANDLE hOutFileMap = CreateFileMapping(hOutFile, NULL, PAGE_READWRITE, 
			qwOutFileSize >> 32, (DWORD)qwOutFileSize, NULL);
	if (hOutFileMap == NULL) {
		printf("Create ouput file mapping failed!%s\n", GetErrMsg());
		CloseHandle(hOutFile);
		CloseHandle(hInFileMap);
		return FALSE;
	}
	
	CloseHandle(hOutFile);
	
	PBYTE odata = (PBYTE)MapViewOfFile(hOutFileMap, FILE_MAP_WRITE, 0, 0, 0);
	if (odata == NULL) {
		printf("Map out file view failed!%s\n", GetErrMsg());
		CloseHandle(hOutFile);
		CloseHandle(hInFileMap);
		CloseHandle(hOutFileMap);
		return FALSE;
	}

	// start to decompress the compressed file
	idata = idata_bak + qwFileStartOffset;
	BitWrap inBitArr(idata);

	QWORD bitpos = 0;
	QWORD outpos = 0;

	while (bitpos < qwFileBitCount) {
		uint clen = 0;
		uchar ch;
		for (uint i = 0; i < tablesize; i++) {
		   ch = charTb[i];
		   clen = lenTb[i];
		   BitSet* inBitSet = inBitArr.getBitSet(bitpos, clen);
		   if (inBitSet->equal(*codeTb[i])) {
			   delete inBitSet;
			   break;
		   }
		   delete inBitSet;
		}

		bitpos += clen;
		odata[outpos++] = ch;
	}

	// Clean up
	UnmapViewOfFile(idata);
	UnmapViewOfFile(odata);

	CloseHandle(hOutFileMap);
	CloseHandle(hInFileMap);

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
			printf("Compress succeed! source file : %.2f KBs dest file : %.2f KBs\n", (double)qwSrcFileSize / 1024, (double)qwDestFileSize / 1024);
			printf("Compress percentage is  : %.0f%%\n", (double)qwDestFileSize / qwSrcFileSize * 100);
			return 0;
		} else {
			printf("Compress failed! %s", GetErrMsg());
			return -1;
		}
	} else if (opt == TEXT('d') || opt == TEXT('D')) {
		QWORD qwSrcFileSize, qwDestFileSize;
		if (decompress(argv[2], argv[3], &qwSrcFileSize, &qwDestFileSize)) {
			printf("DeCompress succeed! source file : %.2f KBs dest file : %.2f KBs\n", (double)qwSrcFileSize / 1024, (double)qwDestFileSize / 1024);
			printf("Compress percentage is : %.0f%%\n", (double)qwSrcFileSize / qwDestFileSize * 100);
			return 0;
		} else {
			printf("DeCompress failed");
			return -1;
		}
	}
}
