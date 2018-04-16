/*
 * main.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>
#include <bitset>

#include "ALU/ALU.h"
#include "Decode/Decode.h"
#include "InstructionCache/InstructionCache.h"
#include "Registers/RegisterFile.h"
#include "util.h"
#include "word.h"

class RegisterFile;

std::string as_binary(word value) {
	return std::bitset < 8 > (value).to_string();
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << argv[0] << " program/file/path"
				<< "  simulate a program using the RRISC instruction set";
	}

	InstructionCache* icache = new InstructionCache();
	RegisterFile* registers = new RegisterFile();
	ALU* alu = new ALU();
	Decode* decode = new Decode(icache, registers, alu);

	std::string program = std::string(argv[1]);
	load_bytes(program, (char*) icache->instructions,
			icache->INSTRUCTION_BYTES);

	while (icache->has_next()) {
		double_word instruction = icache->next_instruction();
		decode->execute(instruction);

		// this processor will run at 1 Mhz, so sleep for 1 millisecond
		// this is a terrible way to mimic this behavior
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	std::printf("register  hex  dec  bin       ascii\n");
	//           r0:       00   000  00000000  c
	for (int i = 0; i < registers->REGISTER_COUNT; i++) {
		std::printf("r%d:       %02x   %03d  %s  %c\n", i,
				registers->registers[i],
				registers->registers[i],
				as_binary(registers->registers[i]).c_str(),
				iscntrl(registers->registers[i]) ?
						' ' : registers->registers[i]);
	}

	delete icache;
	delete decode;
	delete registers;
	delete alu;
}


