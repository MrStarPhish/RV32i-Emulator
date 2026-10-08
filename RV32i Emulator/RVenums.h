#pragma once
#include<iostream>

enum Operation: std::uint8_t {
	ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND, ADDI, SLLI, SLTI, SLTIU, XORI, SRLI, SRAI, ORI, ANDI
};

enum InstructionType : std::uint8_t {
	Rtype = 0b0110011, Itype, Stype, Jtype
};

enum ReadResult : std::uint8_t {
	SUCCESS
};

