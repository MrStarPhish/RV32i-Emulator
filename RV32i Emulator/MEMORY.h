#pragma once
#include<iostream>

const int MAX_MEMORY_SIZE = 4096; // bytes

struct MEMORY {
	unsigned int size;
	uint8_t *data;

	int codeSectionIdx = 0;

	MEMORY(int size = 4096) {

		init();
		
		for (int i = 0; i < size; ++i) {
			data[i] = 0;
		}
	}

	void init() {
		if (size < 1 || size>MAX_MEMORY_SIZE)
		{
			size = 4096;
		}

		data = new uint8_t[size];
		
	}

	bool read8(uint32_t address, uint8_t& value) // reads the specified byte
	{
		if (address < size) {
			value = data[address];
			return true;
		}
		else {
			std::cout << "Memory read error: address out of bounds\n";
			return false;
		}
	}

	bool read32(uint32_t address, uint32_t &value) // reads the specified 4bytes in accordance to little endian format
	{
		if (address + 3 < size) {
			uint32_t temp = 0;
			// the memory is little-endian, so we reconstruct/interpret the 4 bytes in little-endian ordering to get the correct value
			temp |= data[address + 3];
			temp <<= 8;
			temp |= data[address + 2];
			temp <<= 8;
			temp |= data[address + 1];
			temp <<= 8;
			temp |= data[address];

			value = temp;
			return true;
		}
		else {
			std::cout << "Memory read error: address out of bounds\n";
			return false;
		}
	}

	void write32(uint32_t address, uint32_t value) // similar to read32, we write 4 bytes in little endian format.
	{   // i.e, write32(0, 0x12345678) will write 0x78 at address 0, 0x56 at address 1 and so on.
		if (address + 3 < size) {
			data[address] = value & 0xFF;
			data[address + 1] = (value >> 8) & 0xFF;
			data[address + 2] = (value >> 16) & 0xFF;
			data[address + 3] = (value >> 24) & 0xFF;
		}
		else {
			std::cout << "Memory write error: address out of bounds\n";
		}
	}

	void printData(int x) // print x bytes memory elements
	{
		for (int i = 0; i < x; i++)
		{
			printf("%x ", data[i]);
		}
		std::cout << "\n";
	}
};
