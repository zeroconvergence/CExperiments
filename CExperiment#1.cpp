#include <iostream>
#include <winternl.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>

#define SHUTDOWN_PRIVILEGE 19
#pragma comment(lib, "ntdll.lib")

using std::cout;
using std::endl;

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enabled, BOOLEAN CurrentThread, PBOOLEAN StatusPointer);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStat, ULONG NumberOfParametrs, ULONG UnicodeStringParametrMask, PULONG_PTR Parametrs, ULONG Response, PULONG Response2);

int CauseBSOD() {
	BOOLEAN IsAdmin = FALSE;
	ULONG ErrResponse = 0;
	RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &IsAdmin);
	cout << "An error has occurred" << endl;
	NtRaiseHardError(STATUS_ACCESS_VIOLATION, 0, 0, NULL, 6, &ErrResponse);
	cout << "" << endl;
	return 0;
}

int main() {
	CauseBSOD();
	return 0;
}