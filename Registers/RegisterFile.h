/*
 * RegisterFile.h
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#ifndef REGISTERS_REGISTERFILE_H_
#define REGISTERS_REGISTERFILE_H_

#include "../word.h"

class RegisterFile {
public:
	static const int REGISTER_COUNT = 8;
	word registers[REGISTER_COUNT];

	RegisterFile();
	virtual ~RegisterFile();
};

#endif /* REGISTERS_REGISTERFILE_H_ */
