// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

Hack hack;
DWORD WINAPI OnDetach(HMODULE hModule, FILE* f);

//called upon injection
DWORD WINAPI OnAttach(HMODULE hModule)
{
    //allocate console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "Allocated Console.\n";
    
    //get base address of ac_client.exe
    hack.mem.baseAddress = (uintptr_t)GetModuleHandle(L"???");
    std::cout << "??? is loaded at: " << hack.mem.baseAddress << std::endl;

    //intialize
    hack.Init();

    //initiate hack loop
    hack.Run();

    //call OnDetach and return
    OnDetach(hModule, f);
    return 0;
}

//free and eject
DWORD WINAPI OnDetach(HMODULE hModule, FILE* f)
{
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

//dll main entrypoint
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)OnAttach, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

