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
	
	//std::cout << "If you're seeing this message, then Dashboard failed to render." << std::endl;
	//gotoxy(0, 0);

	system.init();
	std::cout << "System Initialized\n" << std::endl;
	system.initShm();

	 //-- Sample Setup
	system.cpu.registers[1] = 12;
	system.cpu.registers[2] = 10;

	system.run();

	//------------------------------ Dashbaord Initialization 

	//Dashboard dashboard;
	////dashboard.loadSnapshot(*system.snapshot);
	//StateSnapshot dummyEmptySnapshot;
	//dashboard.loadSnapshot(dummyEmptySnapshot);
	//dashboard.initialize();

	//////----------------  Dashboard loop

	//dashboard.run();
	
	

	
	char c = _getch();
	return 0;
}