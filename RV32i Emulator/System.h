#pragma once
#include <iostream>
#include <fstream>

#include "CPU.h"
#include "MEMORY.h"
#include "RVenums.h"


struct System {
	CPU cpu;
	MEMORY memory;


	// --------------------------------- GETTERS / SETTERS -----------------------------
	uint32_t* getRegisters() {
		return cpu.registers;
	}

	int getNumRegisters() {
		return sizeof(cpu.registers) / sizeof(cpu.registers[0]);
	}

	// --------------------------------- SYSTEM FUNCTIONS -----------------------------------

	void loadProgram(std::string filepath) // this will load the set of instructions from external .bin file
	{
		// open .bin file given in "filepath" 
		std::ifstream file;
		file.open(filepath, std::ios::binary | std::ios::ate); // ate = at the end
		if (!file)
		{
			std::cout << "Load Program Error: File not found\n";
			return;
		}

		std::cout << "Loading Program to Memory...\n";

		std::streamsize fileSize = file.tellg(); // get current position, it's already at the end.
		file.seekg(0, std::ios::beg); // move the pointer back to beginning

		// point to the destination memory
		uint8_t *destination = &(memory.data[memory.codeSectionIdx]);

		if (file.read(reinterpret_cast<char*>(destination), fileSize)) // load the whole file at once
		{
			std::cout << "Program loaded successfully: Loaded" << fileSize << "bytes.\n";
		}
		else
		{
			std::cout << "Load Program Error: Failed to load the program.\n";
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
			return true;
		}
		return false;
	}

	bool decode(uint32_t instruction, uint32_t& decodedInstruction) // the instruction, and the variable to store the resulting type. returns the parameters
	{	// side note: when pipeline is implemented, the instructionBuffer be added into parameters

		// "instruction is in the format where opcode is in the first 8 bits;"
		// 
		// in logicaly way, the least significant 7 bits are opcode. i.e, 0b...10011011. Here 0011011 is opcode. 
		// when it is changed to little endian format, it becomes, 0b10011011...
		// here, the most significant [1:7] bits are opcode i.e 0011011. THe very first bit '1' at position [0] is the not of opcode, but other information. 
		// SO, I'm gonna convert the instruction back to logical format. Little Endian -> Actual Format, where opcode is at Least Significant 7 bits.

		// NOW: Opcode is at least 7 significant bits : Following logical order

		uint8_t opcode = 0;
		// extract opcode
		opcode = (instruction) & 0b01111111;



		switch (opcode)
		{
			case InstructionType::Rtype: //if R-Type
			{
				//extract other fn bits, like fn3 and fn7
				uint32_t fn3 = (instruction >> 12) & 7;
				uint32_t fn7 = (instruction >> 25) & 127;
				uint8_t operationType = 0;



				switch (fn3)
				{   // Determing Operation Type here based on fn and fn7
				case 0b001:
					operationType = SLL;
					break;
				case 0b010:
					operationType = SLT;
					break;
				case 0b011:
					operationType = SLTU;
					break;
				case 0b100:
					operationType = XOR;
					break;
				case 0b110:
					operationType = OR;
					break;
				case 0b111:
					operationType = SRA;
					break;
				case 0b000:
					if (fn7 == 0b0000000)
						operationType = ADD;
					else if (fn7 == 0b0100000)
						operationType = SUB;
					break;
				case 0b101:
					if (fn7 == 0b0000000)
						operationType = SRL;
					else if (fn7 == 0b0100000)
						operationType = SRA;
					break;
				}

				//extract params, each 5bits
				uint8_t rd = (instruction >> 7) & 31;
				uint8_t rs1 = (instruction >> 15) & 31;
				uint8_t rs2 = (instruction >> 20) & 31;

				//store Operation+Params in buffer
				uint32_t temp = 0;
				temp |= rs2;
				temp <<= 8;
				temp |= rs1;
				temp <<= 8;
				temp |= rd;
				temp <<= 8;
				temp |= operationType;

				// now  LSByte is operationType, then rd, rs1 and LSbyte is rs2. 
				decodedInstruction = temp; // Purpose DONE here
				// when converted to 8bit mapping, it will be like this:
				// params[0] = operationTYpe, params[1] = rd, params[2] = rs1, params[3] = rs2
			}
			return true;
		}
		
	}

	bool execute(uint32_t decodedInstruction)
	{
		// get instruction from buffer
		// read the Operation Bits
		uint8_t operation = (decodedInstruction);

		

		
		switch (operation)
		{
		case Operation::ADD: // ADD operation
			{
				//extract related parameters
				uint8_t* params = reinterpret_cast<uint8_t*>(&decodedInstruction);
				// params[0] = operationTYpe, params[1] = rd, params[2] = rs1, params[3] = rs2
				//now execute
				if (params[1] != 0) // write to R0 should be ignored. R0 remains 0.
				{
					cpu.registers[params[1]] = cpu.registers[params[2]] + cpu.registers[params[3]];
				}
				

			}
		return true;
		case Operation::SUB: // SUBtract operation
		{
			//extract related parameters
			uint8_t* params = reinterpret_cast<uint8_t*>(&decodedInstruction);

			//now execute
			cpu.registers[params[1]] = cpu.registers[params[2]] - cpu.registers[params[3]];

		}
		return true;
		} 

		
	}
};