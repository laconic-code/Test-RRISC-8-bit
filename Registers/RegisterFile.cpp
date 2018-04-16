/*
 * RegisterFile.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#include "RegisterFile.h"

RegisterFile::RegisterFile() {
	for (int i = 0; i < this->REGISTER_COUNT; i++) {
		this->registers[i] = 0;
	}
}

RegisterFile::~RegisterFile() {
	// TODO Auto-generated destructor stub
}

