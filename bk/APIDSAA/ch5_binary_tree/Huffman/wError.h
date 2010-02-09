// Module Name: wError.h
// Objective: provide the win32 error handling helper function
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#include <windows.h>

LPCTSTR GetErrMsg() {
	DWORD dwErr = GetLastError();
	LPTSTR lpErrMsg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL, dwErr, 0, (LPTSTR)&lpErrMsg, 0, NULL);
	return lpErrMsg;
}
