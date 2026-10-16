#pragma once

#include<iostream>

struct StateSnapshot {
	
	bool isDashboardOn;
	bool regUpdate, controlUpdate, stackUpdate, memoryUpdate;

	//reg section
	int numRegisters;
	uint32_t registers[32];

	// control section
	uint32_t pc; 

	//stack section
	uint32_t stackChunk[8]; // 8bytes relative to sp

	//memory section
	uint32_t memoryStart; // starting address of memory chunk
	uint8_t memoryChunk[4 * 24]; // 8 rows, each row having 3*4 bytes

	StateSnapshot() {
		isDashboardOn = regUpdate = controlUpdate = stackUpdate = memoryUpdate = false;

		numRegisters = 32; // default 32
		for (int i = 0; i < 32; i++)
		{
			registers[i] = 0;
		}
		pc = 0;
		for (int i = 0; i < 8; i++)
		{
			stackChunk[i] = 0;
		}
		memoryStart = 0;
		for (int i = 0; i < 4 * 24; i++)
		{
			memoryChunk[i] = 0;
		}
	}

	uint32_t* getRegisters()
	{
		return registers;
	}

	int getNumRegisters()
	{
		return numRegisters;
	}
};