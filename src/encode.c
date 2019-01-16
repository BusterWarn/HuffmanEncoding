/*
* Support program for huffman.c
* Reads given file and writes ecode based on huffman table.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*/


#include "encode.h"


/*
* description: Control flow for program. Does function calls and Deallocates
* memory.
* param[in]: file1 - Name of file to be read and encoded.
* param[in]: file2 - Name of file to be written as encoded file.
* param[in]: tree - Tree that contains huffman table.
*/
void encodeFile (char const *file1, char const *file2, huffTree *tree) {

	bitString *bs = encodeFileToBitString(file1, tree);
	unsigned char *text = bitStringGetEncode(bs);
	int size = bitStringGetSize(bs);
	writeEncode(file2, text, size);

	bitStringKill(bs);
}


/*
* description: Reads file and turns it into encoded bitString.
* param[in]: file1 - Name of file to be read.
* param[in]: tree - Tree that contains huffman table.
* return: bitString containing encoded file1 as bits.
*/
bitString *encodeFileToBitString (char const *file1, huffTree *tree) {

	FILE *fp = fopen(file1, "r");

	int currentChar = 0;
	bitString *bs = bitStringEmpty();

	while ((currentChar = fgetc(fp)) >= 0) {

		char *newBits = huffTreeGetKeyPath(tree, currentChar);
		int nrOfBits = getBitLength(newBits);
		bitStringAddBits(bs, newBits, nrOfBits);
	}
	char *eof = huffTreeGetKeyPath(tree, 4);
	int eofLength = getBitLength(eof);
	bitStringAddBits(bs, eof, eofLength);

	fclose(fp);
	return bs;
}


/*
* description: Counts how many bits there are in a string of bits. String must
* contain NULLBYTE.
* param[in]: bits - Pointer to array of bits.
* return: Number of bits in string.
*/
int getBitLength (char *bits) {
	int length = 0;
	while (bits[length] != '\0') {

		length++;
	}
	return length;
}


/*
* description: Writes the encoded file.
* param[in]: file2 - Name of file to be written.
* param[in]: size - size in number of charachters to be written.
*/
void writeEncode (char const *file2, unsigned char *text, int size) {

	FILE *fp = fopen(file2, "w");

	fwrite(text, sizeof(char), size, fp);

	fclose(fp);
}
