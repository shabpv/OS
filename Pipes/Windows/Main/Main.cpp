#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

static void ErrorExit(const char* msg) {
    cout << msg << " ������: " << GetLastError() << endl;
    exit(1);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int N = 0;
    cout << "������� ��� ����� � ������ (N): ";
    cin >> N;
    cin.ignore();

    SECURITY_ATTRIBUTES saAttr = { 0 };
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    const int NUM_PROCESSES = 4;
    const int NUM_PIPES = NUM_PROCESSES + 1;
    HANDLE hRd[NUM_PIPES] = { NULL };
    HANDLE hWr[NUM_PIPES] = { NULL };

    for (int i = 0; i < NUM_PIPES; i++) {
        if (!CreatePipe(&hRd[i], &hWr[i], &saAttr, 0)) {
            ErrorExit("CreatePipe failed");
        }
    }

    wstring exes[NUM_PROCESSES] = { L"M.exe", L"A.exe", L"P.exe", L"S.exe" };

    PROCESS_INFORMATION pi[NUM_PROCESSES] = { 0 };
    STARTUPINFOW si[NUM_PROCESSES] = { 0 }; 

    for (int i = 0; i < NUM_PROCESSES; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(STARTUPINFOW);  
        si[i].dwFlags = STARTF_USESTDHANDLES;
        si[i].hStdInput = hRd[i];
        si[i].hStdOutput = hWr[i + 1];
        si[i].hStdError = GetStdHandle(STD_ERROR_HANDLE);  

        wstring cmd = exes[i];
        if (exes[i] == L"A.exe") {
            cmd += L" " + to_wstring(N);
        }

        if (!CreateProcessW(NULL, (LPWSTR)cmd.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si[i], &pi[i])) {
            ErrorExit("CreateProcessW failed");
        }
    }

    for (int i = 0; i < NUM_PIPES; i++) {
        if (i < NUM_PIPES - 1) CloseHandle(hRd[i]);
        if (i > 0) CloseHandle(hWr[i]);
    }

    string input = "1 2 3 4 5\n";
    DWORD dwWritten = 0;
    if (!WriteFile(hWr[0], input.c_str(), static_cast<DWORD>(input.length()), &dwWritten, NULL)) {
        ErrorExit("WriteFile failed");
    }
    CloseHandle(hWr[0]);

    char buffer[1024] = { 0 };
    DWORD dwRead = 0;
    if (ReadFile(hRd[NUM_PIPES - 1], buffer, sizeof(buffer) - 1, &dwRead, NULL)) {
        buffer[dwRead] = '\0';
        cout << "��������� ������ �������: " << buffer << endl;
    }
    else {
        ErrorExit("ReadFile failed");
    }
    CloseHandle(hRd[NUM_PIPES - 1]);

    for (int i = 0; i < NUM_PROCESSES; i++) {
        WaitForSingleObject(pi[i].hProcess, INFINITE);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}