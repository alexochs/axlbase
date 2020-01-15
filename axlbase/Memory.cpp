#include "pch.h"

void Memory::BytePatch(BYTE* dst, BYTE* src, DWORD size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void Memory::Nop(BYTE* dst, DWORD size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memset(dst, 0x90, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

uintptr_t Memory::FindDMAAddy(uintptr_t ptr, std::vector<DWORD> offsets)
{
    uintptr_t address = ptr;
    for (DWORD i = 0; i < offsets.size(); ++i)
    {
        address = *(uintptr_t*)address;
        address += offsets[i];
    }
    return address;
}

bool Memory::Hook(void* fnHook, void* fnFunc, DWORD size)
{
    //jump is 5 bytes in size, need at least 5 bytes
    if (size < 5)
        return false;

    //change protection and nop that shit
    DWORD oldProtection;
    VirtualProtect(fnHook, size, PAGE_EXECUTE_READWRITE, &oldProtection);
    memset(fnHook, 0x90, size);

    //calculate relative address and place jump
    DWORD relativeAddress = ((DWORD)fnFunc - (DWORD)fnHook) - 5;
    *(BYTE*)fnHook = 0xE9;
    *(DWORD*)((DWORD)fnHook + 1) = relativeAddress;

    //restore protection and return
    VirtualProtect(fnHook, size, oldProtection, &oldProtection);
    return true;
}
