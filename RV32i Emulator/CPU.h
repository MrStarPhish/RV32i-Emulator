#pragma once
#include<iostream>

using namespace std;

struct CPU {
	uint32_t registers[32];
	uint32_t pc;

	CPU() : pc(0)
	{
		for (int i = 0; i < 32; ++i) {
			registers[i] = 0;
		}
	}
};
