#include <windows.h>
#include <stdio.h>

int main()
{
	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);

	printf("%u", sinf.dwAllocationGranularity);

	return 0;
}
