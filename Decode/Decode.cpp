/*
 * Decode.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#include "Decode.h"

#include "../word.h"

Decode::Decode(InstructionCache* icache, RegisterFile* registers, ALU* alu) :
		icache(*icache), registers(*registers), alu(*alu) {
}

Decode::~Decode() {
	// TODO Auto-generated destructor stub
}

void Decode::execute(double_word instruction) {
	int opcode = instruction.msb >> 6;
	if (opcode == 0b00) {
		// add
		int r1_index = (instruction.msb & 0b00111000) >> 3;
		int r2_index = (instruction.msb & 0b00000111);
		int r3_index = instruction.lsb >> 5;

		word& r1 = this->registers.registers[r1_index];
		word& r2 = this->registers.registers[r2_index];
		word& r3 = this->registers.registers[r3_index];

		this->alu.add(r1, r2, r3);

	} else if (opcode == 0b01) {
		// not
		int r1_index = (instruction.msb & 0b00111000) >> 3;
		int r2_index = (instruction.msb & 0b00000111);

		word& r1 = this->registers.registers[r1_index];
		word& r2 = this->registers.registers[r2_index];

		this->alu.complement(r1, r2);

	} else if (opcode == 0b10) {
		// load immediate
		int r1_index = (instruction.msb & 0b00111000) >> 3;
		word& r1 = this->registers.registers[r1_index];

		r1 = instruction.lsb;

	} else {
	// jump if zero
		int r1_index = (instruction.msb & 0b00111000) >> 3;
		word& r1 = this->registers.registers[r1_index];

		if (r1 == 0) {
			this->icache.program_counter = instruction.lsb;
		}
	}
}
