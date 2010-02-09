// Module Name: hwFile.h
// Objective: provide the common file utilitis for hime windows library
// Author: jcyang[at]ymail.com
// Date: 7.Feb.2010
// Revision: alpha
// Platform: Win32

#ifndef __HIMEW_FILE__
#define __HIMEW_FILE__

#include <windows.h>
#include <tchar.h>

LPCTSTR hwGetFileName(LPCTSTR lpFilePath) {
	DWORD dwPathLen = _tcslen(lpFilePath);
	DWORD dwStartPos = dwPathLen - 1;
	DWORD dwEndPos = dwPathLen - 1;

	while (((long)dwStartPos >= 0) && (lpFilePath[dwStartPos--] != TEXT('\\')));
	++dwStartPos; 
	DWORD dwFileNameLen = dwEndPos - dwStartPos + 2;
	LPTSTR lpFileName = new TCHAR[dwFileNameLen];
	for (DWORD pos = dwStartPos; pos <= dwEndPos; ++pos) 
		lpFileName[pos - dwStartPos] = lpFilePath[pos];
	lpFileName[dwFileNameLen] = TEXT('0');
	return lpFileName;
}

#endif
