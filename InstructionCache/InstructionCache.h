/*
 * InstructionCache.h
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#ifndef INSTRUCTIONCACHE_INSTRUCTIONCACHE_H_
#define INSTRUCTIONCACHE_INSTRUCTIONCACHE_H_

#include "../word.h"

class InstructionCache {
public:
	static const int START_OF_PROGRAM = 0x00;
	static const int END_OF_PROGRAM = 0xFF;
	// this architecture is a bit odd in that each
	// instruction is a double word and our
	// program counter is an index to double words
	// rather than an index to words
	static const int INSTRUCTION_BYTES = 2 * 256;
	word instructions[INSTRUCTION_BYTES];
	word program_counter;

	InstructionCache();
	virtual ~InstructionCache();

	bool has_next();
	double_word next_instruction();
};

#endif /* INSTRUCTIONCACHE_INSTRUCTIONCACHE_H_ */
