/*
 * ALU.cpp
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#include "ALU.h"


ALU::ALU() {
	// TODO Auto-generated constructor stub

}

ALU::~ALU() {
	// TODO Auto-generated destructor stub
}

void ALU::add(word& r1, word& r2, word& dst) {
  dst = (r1 + r2) & 0xFF;
}

void ALU::complement(word& r1, word& dst) {
  dst = !r1;
}
