#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "System.h"
#include "ConsoleBufferEssentials.h" // import BUFFER and other essential functions

std::string altName[32]= { "ze","ra","sp","gp","tp","t0","t1","t2","s0","s1",
"a0","a1","a2","a3","a4","a5","a6","a7","s2","s3","s4","s5", "s6", "s7","s8","s9","s10","s11","t3","t4", "t5","t6"        
}; // Alternate Names of each register


struct Region { // A rectangular region on the console screen. i.e Register DIsplay, Memory Display
	uint16_t x, y;
	uint16_t width, height;
};

struct Dashboard {
	Region headerRegion = { 0, 0, WIDTH-1, 2 }; 
	Region registerRegion = { 0, 2, (WIDTH-1)/3, 20 };
	Region controlRegion = { (WIDTH - 1) / 3 , 2, (WIDTH - 1) / 6, 20 };
	Region stackRegion = { ((WIDTH - 1) / 2)-1 , 2, ((WIDTH - 1) / 6) + 2, 20 };
	Region commandRegion = { 0, 42, WIDTH - 1, 2 };

	System* system;

	void loadSystem(System &sys)
	{
		system = &sys;
	}

	void initialize() {
		SetConsoleWindowSize(165, 45);
		SetConsoleBufferSize(165, 45);
		bufferBoundary();
	}

	void printError(const std::string& message) {
		gotoxy(3, 30); // dummy location
		std::cout << "[ERROR] " << message << std::endl;
	}

	void error_SystemNotLoaded() {
		printError("System Not Loaded");
	}

	

	void bufferRegionBoundaries()
	{
		bufferRegionBoundary(headerRegion);
		bufferRegionBoundary(registerRegion);
		bufferRegionBoundary(controlRegion);
		bufferRegionBoundary(stackRegion);
		bufferRegionBoundary(commandRegion);
	}

	void bufferRegionText()
	{
		bufferString(headerRegion.x + 3, headerRegion.y + 1, "RV32i Emulator Dashboard", CYAN, BLACK);
		bufferString(stackRegion.x + 11, stackRegion.y, "STACK", YELLOW, BLACK);
		bufferString(commandRegion.x + 120, commandRegion.y + 1, "INSERT COMMAND HERE | /cmds for more info", YELLOW, BLACK);
		bufferString(controlRegion.x + 6, controlRegion.y, "CONTROL SECTION", YELLOW, BLACK);
		bufferString(registerRegion.x + 23, registerRegion.y, "REGISTERS", YELLOW, BLACK);

		bufferString(registerRegion.x + 3, registerRegion.y + registerRegion.height-1, "/set <reg> <hex>", YELLOW, BLACK);
		bufferString(controlRegion.x + 3, controlRegion.y + controlRegion.height -1, "/step /undo /emit", YELLOW, BLACK);

	}

	void render()
	{
		if (!system) {
			error_SystemNotLoaded();
			return;
		}
		clearBuffer();

		bufferBoundary();
		bufferRegionBoundaries();
		bufferRegionText();

		bufferRegisters();
		bufferControlSection();
		bufferStack();

		renderBuffer();

	}
	// ------------------------------------------ HELPERS 


	std::string toHex32(uint32_t value) // Hex - > 0x00000000 format
	{
		std::ostringstream out;
		out << ""
			<< std::hex
			<< std::nouppercase
			<< std::setfill('0')
			<< std::setw(8)
			<< value;

		return out.str();
	}

	std::string toHex32_spaced(uint32_t value) // Hex -> 0x00 00 00 00 format
	{
		std::ostringstream out;
		
		out << ""
			<< std::hex
			<< std::nouppercase
			<< std::setfill('0')
			<< std::setw(2)
			<< ((value >> 24) & 0xFF) << " "
			<< std::setw(2)
			<< ((value >> 16) & 0xFF) << " "
			<< std::setw(2)
			<< ((value >> 8) & 0xFF) << " "
			<< std::setw(2)
			<< (value & 0xFF);

		return out.str();
	}

	// ------------------------------------------ ALL BUFFERRING HERE


	// ---- BACKGROUND 
	void bufferBoundary() {
		for (int i = 0; i < HEIGHT; i++)
		{
			if (i == 0 || i == HEIGHT - 1)
				for (int j = 0; j < WIDTH; j++)
				{
					buffer[(WIDTH * i) + j] = { '=' , ColorCode::DEFAULT };
				}
			else
			{
				buffer[(WIDTH * i)] = { '|' , ColorCode::DEFAULT };
				buffer[(WIDTH * i) + WIDTH - 1] = { '|' , ColorCode::DEFAULT };
			}
		}
	}

	void bufferRegionBoundary(Region& currRegion)
	{   // The boundary is drawn such way that the internal structure has currRegion.width-1 and height-1 hollow pixels


		// Top/Bottom boundary
		for (int i = 0; i < currRegion.width + 1; i++)
		{
			buffer[(WIDTH * currRegion.y) + currRegion.x + i] = { '=', ColorCode::DEFAULT };
			buffer[(WIDTH * (currRegion.y + currRegion.height)) + currRegion.x + i] = { '=', ColorCode::DEFAULT };
		}

		// Left-Right Boundary
		for (int i = 1; i < currRegion.height; i++)
		{
			buffer[(WIDTH * (i + currRegion.y)) + currRegion.x] = { '|', ColorCode::DEFAULT };
			buffer[(WIDTH * (i + currRegion.y)) + currRegion.x + currRegion.width] = { '|', ColorCode::DEFAULT };
		}
	}


	//------------------ REGISTER SECTION
	void bufferRegisters()
	{
		if (!system) {
			error_SystemNotLoaded();
			return;
		}

		uint32_t* registers = system->getRegisters();
		int numRegisters = system->getNumRegisters();
		int offset_x = 3;
		int offset_y = 2;
		int gap = 27;
		for (int i = 0; i < 16; ++i) {
			int x = registerRegion.x + offset_x;
			int y = registerRegion.y + i + offset_y;
			std::string regStr = "x" + std::string(i < 10 ? "0" : "") + std::to_string(i) + " (" + altName[i] + "): ";
			std::string regVal = toHex32_spaced(registers[i]);
			bufferString(x, y, regStr, DEFAULT, BLACK);
			bufferString(x + static_cast<int>(regStr.length()), y, regVal, GREEN, BLACK);

		} 
		for (int i = 16; i < numRegisters; ++i) {
			int x = registerRegion.x + gap + offset_x;
			int y = registerRegion.y + i - 16 + offset_y;
			std::string regStr = "x" + std::string(i < 10 ? "0" : "") + std::to_string(i) + " (" + altName[i] + "): ";
			if (i != 26 && i != 27) regStr += " "; // adjustment space
			std::string regVal = toHex32_spaced(registers[i]);
			bufferString(x, y, regStr, DEFAULT, BLACK);
			bufferString(x + static_cast<int>(regStr.length()), y, regVal, GREEN, BLACK);
		}
	}

	// ------------------- CONTROL SECTION


	void bufferControlSection() 
	{
		if (!system) {
			error_SystemNotLoaded();
			return;
		}

		uint32_t pc = system->cpu.pc;
		int offset_x = 3;
		int offset_y = 2;

		std::string pcStr = "PC: ";
		std::string pcVal = toHex32_spaced(pc);
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y, pcStr, DEFAULT, BLACK);
		bufferString(controlRegion.x + offset_x + static_cast<int>(pcStr.length()), controlRegion.y + offset_y, pcVal, GREEN, BLACK);

		std::string lastAddrStr = "LastAddr: ";
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 2, lastAddrStr, DEFAULT, BLACK);
		uint32_t lastAddr = 0xFFFFFFFF;
		lastAddr = 0x00000004;
		// get instruction here. If not found, display N/A
		if (lastAddr == 0xFFFFFFFF)
		{
			bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 3, "N/A", CYAN, BLACK);
		}
		else
		{
			std::string addrVal = toHex32_spaced(lastAddr);
			bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 3, addrVal, CYAN, BLACK);

			//and also show difference from old PC to next PC 
			int diffVal = pc - lastAddr;
			std::string diffStr = "(";
			diffStr += (diffVal > 0 ? "+" : "") + std::to_string(diffVal) + ")";
			bufferString(controlRegion.x + offset_x + 12 + static_cast<int>(pcStr.length()), controlRegion.y + offset_y, diffStr, CYAN, BLACK);
		}

		std::string instrStr = "Instruction: ";
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 5, instrStr, DEFAULT, BLACK);
		uint32_t instr = 0xFFFFFFFF;
		// get instruction here. If not found, display N/A
		if (instr == 0xFFFFFFFF)
		{
			bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 6, "N/A", CYAN, BLACK);
		}
		else
		{
			std::string instrVal = toHex32_spaced(instr);
			bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 6, instrVal, CYAN, BLACK);
		}

		std::string decodedStr = "Decoded: ";
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 8, decodedStr, DEFAULT, BLACK);
		std::string decodedVal = "N/A";
		// get instruction here. If not found, display N/A	
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 9, decodedVal, CYAN, BLACK);
		
		std::string executedStr = "Executed: ";
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 11, executedStr, DEFAULT, BLACK);
		uint32_t executed = 0; // no.of instructions executed
		// get instruction here. If not found, display N/A		
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 12, std::to_string(executed), CYAN, BLACK);

		std::string lastPCStr = "Last PC: ";
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 14, lastPCStr, DEFAULT, BLACK);
		uint32_t lastPC = 0; // last program counter value
		// get last PC here. If not found, display N/A		
		std::string lastPCVal = toHex32(lastPC);
		lastPCVal += " -> ";
		lastPCVal += toHex32(system->cpu.pc);
		bufferString(controlRegion.x + offset_x, controlRegion.y + offset_y + 15, lastPCVal, CYAN, BLACK);
	}


	// -------------------- STACK REGION

	void bufferStack()
	{
		if (!system) {
			error_SystemNotLoaded();
			return;
		}
		uint32_t sp = system->cpu.registers[2]; // stack pointer is in register x2
		sp = 0x00000010;
		int offset_x = 3;
		int offset_y = 2;
		std::string spStr = "SP: ";
		std::string spVal = toHex32_spaced(sp);
		bufferString(stackRegion.x + offset_x, stackRegion.y + offset_y, spStr, DEFAULT, BLACK);
		bufferString(stackRegion.x + offset_x + static_cast<int>(spStr.length()), stackRegion.y + offset_y, spVal, GREEN, BLACK);
		// Display the top 8 stack values
		for (int i = 0; i < 8; ++i) {
			uint32_t addr = sp + i * 4;
			uint32_t value;
			if (system->memory.read32(addr, value)) {
				std::string addrStr = toHex32_spaced(addr) + ": ";
				std::string valueStr = toHex32_spaced(value);
				bufferString(stackRegion.x + offset_x, stackRegion.y + offset_y + 2 + (i*2), addrStr, DEFAULT, BLACK);
				bufferString(stackRegion.x + offset_x + static_cast<int>(addrStr.length()), stackRegion.y + offset_y + 2 + (i * 2), valueStr, CYAN, BLACK);
			}
			else {
				bufferString(stackRegion.x + offset_x, stackRegion.y + offset_y + 2 + (i*2), "N/A", CYAN, BLACK);
			}
		}
	}
};