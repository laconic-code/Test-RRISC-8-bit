/*
 * ALU.h
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#ifndef ALU_H_
#define ALU_H_

#include "../word.h"

class ALU {
public:
	ALU();
	virtual ~ALU();
	void add(word& r1, word& r2, word& dst);
	void complement(word& r1, word& dst);
};

#endif /* ALU_H_ */
