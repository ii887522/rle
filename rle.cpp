#include "rle.h"
#include <fstream>
#include <exception>
#include <sstream>
#include "consts.h"
#include "common.h"

using std::ifstream;
using std::ios;
using std::exception;
using std::stringstream;

RLE::RLE(const string& path) {
	// Open the file identified by the given path
	ifstream file{ path, ios::binary };

	// Read image width
	unsigned char widthBits[2];
	file.read(reinterpret_cast<char*>(widthBits), sizeof(widthBits));
	width = toU16(widthBits);

	// Read image height
	unsigned char heightBits[2];
	file.read(reinterpret_cast<char*>(heightBits), sizeof(heightBits));
	height = toU16(heightBits);

	// Read encoded pixels
	pixels.resize(width * height * (COMPONENT_COUNT + OCCURENCE_COUNT_SIZE));
	auto index{ 0 };
	for (; !file.eof(); index += COMPONENT_COUNT + OCCURENCE_COUNT_SIZE)
		file.read(reinterpret_cast<char*>(pixels.data() + index), COMPONENT_COUNT + OCCURENCE_COUNT_SIZE);

	// Shrink the pixels array to the actual size
	pixels.resize(index - COMPONENT_COUNT - OCCURENCE_COUNT_SIZE);
}
