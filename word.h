/*
 * word.hpp
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#ifndef WORD_H_
#define WORD_H_

typedef unsigned char word;

struct double_word {
#ifdef LOW_ENDIAN
    word lsb,msb;
#else
    word msb,lsb;
#endif
};


#endif /* WORD_H_ */
