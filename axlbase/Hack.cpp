#include "pch.h"

/*
Hooking Example:                                                  (jmpBackAddy)
    - jump function should be __declspec(naked) with __asm { jmp [fnHook + size] } -- __declspec(naked): no additional bytes, naked function
    - initialize hook with Memory::Hook(fnHook, fnFunc, size)

Now everytime fnHook gets called we jump to fnFunc and execute our code
*/

void Hack::Init()
{
    //localplayer = (uintptr_t*)(mem.baseAddress + mem.localplayerOffset);
    //health = (uintptr_t*)(*localplayer + mem.healthOffset);
    //decAmmoFunc = (uintptr_t*)(mem.baseAddress + mem.decAmmoFuncOffset);
    //std::cout << "Localplayer: " << localplayer << " -> " << *localplayer << std::endl;
    //std::cout << "Health: " << health << " -> " << *health << std::endl;
    //std::cout << "Dec Ammo Func: " << decAmmoFunc << " -> " << *decAmmoFunc << std::endl;
}

void Hack::Run()
{
    bool bPatchedAmmoFunc = false;

    while (true)
    {
        KeyListener();
        if (bDetach)
            return;
    }
}

void Hack::KeyListener()
{
    if (GetAsyncKeyState(VK_DELETE) & 1)
        bDetach = true;
}