#include<iostream>
#include<conio.h>
#include<windows.h.>

#include "System.h"
#include "Dashboard.h"
#include "ConsoleBufferEssentials.h"
#include"StateSnapshot.h" // remove later

int main()
{
	System system;
	std::cout << "Press any key to load test.bin\n" << std::endl;
	_getch();
	system.loadProgram("test.bin");

	system.init();
	std::cout << "System Initialized\n" << std::endl;
	system.initShm();
	std::cout << "Press any key to start program.\n" << std::endl;
	// Test Setup
	system.cpu.registers[1] = 12;
	system.cpu.registers[2] = 10;

	system.run();
	
	char c = _getch();
	return 0;
}