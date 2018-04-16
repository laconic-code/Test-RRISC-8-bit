/*
 * InstructionCache.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */
#include <cstdio>
#include "InstructionCache.h"

InstructionCache::InstructionCache() {
	this->program_counter = 0;
	for (int i = 0; i < this->INSTRUCTION_BYTES; i++) {
		this->instructions[i] = 0;
	}
}

InstructionCache::~InstructionCache() {
	// TODO Auto-generated destructor stub
}

bool InstructionCache::has_next() {
	return this->program_counter != this->END_OF_PROGRAM;
}

double_word InstructionCache::next_instruction() {
	double_word next;
	int instruction_index = this->program_counter * 2;
	// TODO: verify this is correct, it probably isn't
	next.msb = this->instructions[instruction_index];
	next.lsb = this->instructions[instruction_index + 1];
	this->program_counter += 1;
	return next;
}
