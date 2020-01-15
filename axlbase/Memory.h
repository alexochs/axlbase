#pragma once

class Memory
{
public:
	uintptr_t baseAddress;
	DWORD someOffset;

	//overwrite size bytes with src starting at dst
	void BytePatch(BYTE* dst, BYTE* src, DWORD size);

	//nop size bytes starting at dst
	void Nop(BYTE* dst, DWORD size);

	//find a dynamic memory allocation address (multipointer)
	uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<DWORD> offsets);

	//nops size bytes at fnHook and places jump to our function
	bool Hook(void* fnHook, void* fnFunc, DWORD size);
};

