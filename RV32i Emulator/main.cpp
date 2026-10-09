#include<iostream>
#include<conio.h>

#include "System.h"
#include "Dashboard.h"
#include "ConsoleBufferEssentials.h"


int main()
{
	System system;
	system.loadProgram("test.bin");
	
	std::cout << "If you're seeing this message, then Dashboard failed to render." << std::endl;
	gotoxy(0, 0);

	// -- Sample Program 
	//system.cpu.registers[1] = 5;
	//system.cpu.registers[2] = 3;

	//uint32_t instruction = 0;
	//system.fetch(instruction);
	//uint32_t decodedInstruction = 0;
	//system.decode(instruction, decodedInstruction);
	//system.execute(decodedInstruction);

	//cout << "Register 1: " << system.cpu.registers[1] << endl;
	//cout << "Register 2: " << system.cpu.registers[2] << endl;
	//cout << "Register 3: " << system.cpu.registers[3] << endl << endl;

	Dashboard dashboard;
	dashboard.loadSystem(system);
	//dashboard.bufferRegisters();
	dashboard.initialize();
	dashboard.render();
	

	
	char c = _getch();
	return 0;
}