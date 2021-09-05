#include <iostream>
#include <winternl.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <fstream>

#define SHUTDOWN_PRIVILEGE 19
#pragma comment(lib, "ntdll.lib")

using namespace std;

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enabled, BOOLEAN CurrentThread, PBOOLEAN StatusPointer);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStat, ULONG NumberOfParametrs, ULONG UnicodeStringParametrMask, PULONG_PTR Parametrs, ULONG Response, PULONG Response2);

int BSODMemoryCrash() {
	BOOLEAN IsAdmin = FALSE;
	ULONG ErrResponse = 0;
	RtlAdjustPrivilege(SHUTDOWN_PRIVILEGE, TRUE, FALSE, &IsAdmin);
	cout << "MEMORY_ACCESS_VIOLATION" << endl;
	NtRaiseHardError(STATUS_ACCESS_VIOLATION, 0, 0, NULL, 6, &ErrResponse);
	cout << "Failed crashing!" << endl;
	return 0;
}

void IsCrash() {
	ifstream file("0");
	if (!file.is_open()) {
		BSODMemoryCrash();
	}
}

int main() {
	IsCrash();
	return 0;
}