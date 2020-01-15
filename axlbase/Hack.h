#pragma once

class Hack
{
private:
	uintptr_t* somePointer;

	bool bDetach = false;

public:
	Memory mem;

	//init
	void Init();

	//main loop
	void Run();

	//listen for input
	void KeyListener();
};

