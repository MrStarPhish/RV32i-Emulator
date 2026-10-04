#pragma once
#include <iostream>
#include <fstream>

#include "CPU.h"
#include "MEMORY.h"

using namespace std;

struct System {
	CPU cpu;
	MEMORY memory;

	void loadProgram(string filepath) // this will load the set of instructions from external .bin file
	{
		// open .bin file given in "filepath" 
		ifstream file;
		file.open(filepath, ios::binary | ios::ate); // ate = at the end
		if (!file)
		{
			cout << "Load Program Error: File not found\n";
			return;
		}

		cout << "Loading Program to Memory..." << endl;

		streamsize fileSize = file.tellg(); // get current position, it's already at the end.
		file.seekg(0, ios::beg); // move the pointer back to beginning

		// point to the destination memory
		uint8_t *destination = &(memory.data[memory.codeSectionIdx]);

		if (file.read(reinterpret_cast<char*>(destination), fileSize)) // load the whole file at once
		{
			cout << "Program loaded successfully: Loaded"<< fileSize <<"bytes." << endl;
		}
		else
		{
			cout << "Load Program Error: Failed to load the program.\n";
		}


		
	} 
	bool fetch(uint32_t &instruction) // returns the instruction as it is from the memory, in the format where opcode is in the first 8 bits;
	{
		// logical opcode: 0x12345678 , 78 containing the opcode
		// memory opcode: 0x78563412 , 78 containing the opcode <-- this is what is being returned.

		uint32_t temp = 0;
		if (memory.read32(cpu.pc, temp))
		{
			cpu.pc += 4;
			instruction = temp;
			cout << temp << endl;
			return true;
		}
		return false;
	}

	uint32_t decode(uint32_t instruction) // the instruction, and the variable to store the resulting type. returns the parameters
	{
		// instruction is in the format where opcode is in the first 8 bits;
		// in logicaly way, the least significant 7 bits are opcode. i.e, 0b...10011011. Here 0011011 is opcode. 
		// when it is changed to little endian format, it becomes, 0b10011011...
		// here, the most significant [1:7] bits are opcode i.e 0011011. THe very first bit '1' at position [0] is the not of opcode, but other information. 
		// SO, I'm gonna convert the instruction back to logical format. Little Endian -> Actual Format, where opcode is at Least Significant 7 bits.

		uint8_t opcode = 0;
		



	}

	void execute(uint8_t type, uint32_t instruction)
	{
		// R-Type
		//0-6bit opcode
		//7-11 Rd
		//11-15 fn3
		//15-19 Rs1
		//20-24 Rs2
		//25-31 fn7
	}
};