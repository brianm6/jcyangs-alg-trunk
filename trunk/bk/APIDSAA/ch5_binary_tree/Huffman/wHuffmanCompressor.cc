// Module Name: wHuffmanCompressor.cc
// Objective: implementate the pure huffman compressor 
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
#include "EncodeHuffmanTree.h"
#include "DecodeHuffmanTree.h"
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
	EncodeHuffmanTree tree((const uchar*)charTb, (const uint*)wtTb, tbsize);

	// tree.showTree();
	// calculate various size
	vector<uchar> serialStr = tree.serialize();
	// for (int i = 0; i < serialStr.size(); i++) 
	//	cout << (int)serialStr[i] << "   ";

	QWORD qwOutFileSize = 0;
	QWORD qwOutFileBits = 0;
	WORD wHuffmanTreeSize = serialStr.size();
	LPCTSTR lpFileName = hwGetFileName(infile);
	WORD wFileNameSize = _tcslen(lpFileName) * 2 + 4; // add tail null
	const WORD wOtherFieldSize = sizeof(QWORD) * 4 + 2 * sizeof(WORD);
		// include FileHeaderSize,FileOrignalSize,FileCompressedSize, FileBitCount, FileStartOffset, FileCompressTableLen
	WORD wFileHeaderSize = wFileNameSize + wOtherFieldSize + wHuffmanTreeSize;

	uint* lenTb = tree.getLenTb();
	BitSet** codeTb = tree.getCodeTb();

	for (uint i = 0; i < tbsize; i++) 
		qwOutFileBits += wtTb[i] * lenTb[i];
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
	memcpy(odata + 2, lpFileName, _tcslen(lpFileName) * 2);
	memset(odata + 2 +  _tcslen(lpFileName) * 2, 0, 4);
	*(PQWORD)(odata + wFileNameSize + 2) = qwInFileSize;
	*(PQWORD)(odata + wFileNameSize + 10) = qwOutFileSize;
	*(PQWORD)(odata + wFileNameSize + 18) = qwOutFileBits;
	*(PQWORD)(odata + wFileNameSize + 26) = wFileHeaderSize; // qwFileStartOffset
	// cout << wHuffmanTreeSize << endl;
	*(PWORD)(odata + wFileNameSize + 34) = wHuffmanTreeSize;

	for (int i = 0; i < serialStr.size(); ++i) 
		odata[wFileNameSize + 36 + i] = serialStr[i]; 

	// tree.showCodeTb();
	BitWrap outBitArr(odata + wFileHeaderSize);
	QWORD bitpos = 0;
	for (QWORD i = 0; i < qwInFileSize; i++)  {
		// cout << idata[i] << "   " << charpos[idata[i]] << "   " << tbCode[charpos[idata[i]]]->toString() << endl;
		outBitArr.set(bitpos, *codeTb[charpos[idata[i]]]);
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

	// dump the information in the file header
	PBYTE idata_bak = idata;
	idata += 2;
	PDWORD tdata = (PDWORD)idata;
	while (*tdata != 0) {
		idata = idata + 2;
		tdata = (PDWORD)idata;
	}
	*pqwDestFileSize = *(PQWORD)++tdata; // orginal file size
	QWORD qwOutFileSize = *pqwDestFileSize;
	QWORD qwFileBitCount = *(PQWORD)(tdata + 4);
	QWORD qwFileStartOffset = *(PQWORD)(tdata + 6);
	WORD wHuffmanTreeSize = *(PWORD)(tdata + 8);
	
	// create the decode huffman tree
	PBYTE destr = (PBYTE)(tdata + 8) + 2;

	DecodeHuffmanTree tree(destr, wHuffmanTreeSize);
	
	// tree.showTree();
	// tree.showStateTable();
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

	// cout << inBitArr.getBitSet(bitpos, 256)->toString() << endl;
	tree.decode(idata, odata, qwFileBitCount); 
	
/*	while (bitpos < qwFileBitCount) {
		uint clen;
		uchar ch;

		uint bitlen = 256;
		if (qwFileBitCount - bitpos	< bitlen)
			bitlen = qwFileBitCount - bitpos;
		
		ch = tree.decode((inBitArr.getBitSet(bitpos, bitlen))->toString(), clen);
		cout << qwFileBitCount - bitpos << endl;;
		bitpos += clen;
		odata[outpos++] = ch;
	} */

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
	LARGE_INTEGER liStart, liEnd;
	LARGE_INTEGER liFreq;
	QueryPerformanceFrequency(&liFreq);

	if (opt == TEXT('c') || opt == TEXT('C')) {
		QWORD qwSrcFileSize, qwDestFileSize;
		QueryPerformanceCounter(&liStart);
		if (compress(argv[2], argv[3], &qwSrcFileSize, &qwDestFileSize)) {
			QueryPerformanceCounter(&liEnd);
			printf("Compress succeed! source file : %.2f KBs dest file : %.2f KBs\n", (double)qwSrcFileSize / 1024, (double)qwDestFileSize / 1024);
			printf("Compress percentage is  : %.0f%%\n", (double)qwDestFileSize / qwSrcFileSize * 100);
			printf("Compress time is : %.0fs\n", ((double)liEnd.QuadPart - liStart.QuadPart) / liFreq.QuadPart);
			return 0;
		} else {
			printf("Compress failed! %s", GetErrMsg());
			return -1;
		}
	} else if (opt == TEXT('d') || opt == TEXT('D')) {
		QWORD qwSrcFileSize, qwDestFileSize;
		QueryPerformanceCounter(&liStart);
		if (decompress(argv[2], argv[3], &qwSrcFileSize, &qwDestFileSize)) {
			QueryPerformanceCounter(&liEnd);
			printf("DeCompress succeed! source file : %.2f KBs dest file : %.2f KBs\n", (double)qwSrcFileSize / 1024, (double)qwDestFileSize / 1024);
			printf("Compress percentage is : %.0f%%\n", (double)qwSrcFileSize / qwDestFileSize * 100);
			printf("DeCompress time is : %.0fs\n", ((double)liEnd.QuadPart - liStart.QuadPart) / liFreq.QuadPart);
			return 0;
		} else {
			printf("DeCompress failed");
			return -1;
		}
	}
}
