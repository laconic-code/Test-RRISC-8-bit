/*
 * util.h
 *
 *  Created on: Apr 14, 2018
 *      Author: ben
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <limits.h>
#include <stddef.h>
#include <sys/types.h>
#include <cstdlib>
#include <fstream>
#include <string>


/*
 * read bytes_to_read from file_path into dst
 * returns bytes read
 * will throw exception on read failure
 */
int load_bytes(const std::string& file_path, char* dst,
		const uint& bytes_to_read) {
	char real_path[PATH_MAX];
	realpath(file_path.c_str(), real_path);

	// RAII
	std::ifstream infile = std::ifstream(real_path, std::ifstream::binary);

	if (!infile.good()) {
		char message[PATH_MAX * 2];
		std::sprintf(message, "file %s does not exist", real_path);
		throw std::invalid_argument(message);
	}

	infile.read(dst, bytes_to_read);
	return infile.gcount();
}


#endif /* UTIL_H_ */
