/*
 * Decode.h
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#ifndef DECODE_DECODE_H_
#define DECODE_DECODE_H_

#include "../InstructionCache/InstructionCache.h"
#include "../ALU/ALU.h"
#include "../Registers/RegisterFile.h"

class Decode {
public:
	InstructionCache& icache;
	RegisterFile& registers;
	ALU& alu;

	Decode(InstructionCache* icache, RegisterFile* registers, ALU* alu);
	virtual ~Decode();

	void execute(double_word instruction);
};

#endif /* DECODE_DECODE_H_ */
