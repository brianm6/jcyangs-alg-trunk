// Module Name: HuffmanApp.cc
// Objective: demonstrate the application of huffman coding tree 
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Platform: Win32
// Revision: alpha

#include <windows.h>
#include <stdio.h>
#include "HuffmanTree.h"

BOOL compress(LPCTSTR infile, LPCTSTR outfile, 
			  PDWORD pdwSrcFileSize, PDWORD pdwDestFileSize) {

	HANDLE hInFile = CreateFile(infile, GENERIC_READ, 
					FILE_SHARE_READ | FILE_SHARE_WRITE, 
					NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	HANDLE hOutFile = CreateFile(outfile, GENERIC_WRITE, 
					FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL, CREATE_NEW, NULL, NULL);
	if (hInFile = INVALID_HANDLE_VALUE || hOutFile == INVALID_HANDLE_VALUE)
		return FALSE;

	// assume file size < 2GB 
	DWORD dwInFileSize = GetFileSize(hInFile, NULL);
	*pdwFileSrcSize = dwInFileSize;
	
	// TODO: decide the proper value for output file mapping 
	HANDLE hInFileMap = CreateFileMapping(hInFile, NULL, 
						PAGE_READONLY, 0, dwInFileSize, NULL);
	HANDLE hOutFileMap = CreateFileMapping(hOutFile, NULL, 
						PAGE_WRITEONLY, 0, dwInFileSize * 1.23, NULL);
	if (hInFileMap == NULL || hOutFileMap == NULL)
		return FALSE;
	
	// build the charset-weight table
	PBYTE pData = MapViewOfFile(hInFileMap, FILE_MAP_READ, 0, 0, dwInFileSize);
	CHAR tbCharset[256];
	for (int i = 0; i < 256; i++)
		tbCharset[i] = i;
	DWORD tbWeight[256] = {0};
	for (DWORD i = 0; i < dwInFileSize, i++)
		tbWeight[pData[i]]++;
	
	// create the huffman coding tree
	HuffmanTree tree(tbCharset, tbWeight, 256);
	
	
}
int wmain(int argc, LPCTSTR argv[]) {
	if (argc != 3) {
		printf("Usage: HuffmanApp -c | -d srcFileName destFileName \n");
		return -1;
	} 

	TCHAR opt = argv[1][1];
	if (opt == TEXT('c') || opt == TEXT('C')) {
		DWORD dwSrcSize, dwDestSize;
		if (compress(argv[2], argv[3], &dwSrcSize, &dwDestSize)) {
			printf("Compress succeed! source file : %ld KBs dest file : %ld KBs", dwSrcSize, dwDestSize);
			return 0;
		} else {
			printf("Compress failed!");
			return -1;
		}
	} else if (opt == TEXT('d') || opt == TEXT('D')) {
		DWORD dwSrcSize, dwDestSize;
		if (decompress(argv[2], argv[3], &dwSrcSize, &dwDestSize)) {
			printf("DeCompress succeed! source file : %ld KBs dest file : %ld KBs", dwSrcSize, dwDestSize);
			return 0;
		} else {
			printf("DeCompress failed");
			return -1;
		}
	}
}
	

