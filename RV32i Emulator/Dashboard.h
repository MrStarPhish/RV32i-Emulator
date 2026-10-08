#pragma once

#include <iostream>
#include "System.h"
#include "ConsoleBufferEssentials.h" // import BUFFER and other essential functions



struct Region { // A rectangular region on the console screen. i.e Register DIsplay, Memory Display
	uint16_t x, y;
	uint16_t width, height;
};

struct Dashboard {
	Region registerRegion;
	System* system;

	void loadSystem(System &sys)
	{
		system = &sys;
	}

	void printError(const std::string& message) {
		gotoxy(3, 30); // dummy location
		std::cout << "[ERROR] " << message << std::endl;
	}

	void error_SystemNotLoaded() {
		printError("System Not Loaded");
	}

	void bufferRegisters() 
	{
		if (!system) {
			error_SystemNotLoaded();
			return;
		}

		uint32_t* registers = system->getRegisters();
		int numRegisters = system->getNumRegisters();
		for (int i = 0; i < numRegisters; ++i) {
			int x = registerRegion.x;
			int y = registerRegion.y + i;
			std::string regStr = "x" + std::to_string(i) + ": " + std::to_string(registers[i]);
			bufferString(x, y, regStr, DEFAULT, BLACK);
		}
	}

	void render()
	{
		if (!system) {
			error_SystemNotLoaded();
			return;
		}
		renderBuffer();
	}
};