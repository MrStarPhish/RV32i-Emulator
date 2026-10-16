#pragma once
#include<iostream>

const int NUM_REGISTERS = 32;

struct CPU {
	uint32_t registers[NUM_REGISTERS];
	uint32_t pc;

	CPU() : pc(0)
	{
		for (int i = 0; i < 32; ++i) {
			registers[i] = 0;
		}
	}
};
