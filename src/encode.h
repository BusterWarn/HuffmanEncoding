/*
* Support program for huffman.c
* Reads given file and writes ecode based on huffman table.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffTree.h"
#include "bitString.h"


/*
* description: Control flow for function. Does function calls and Deallocates
* memory.
* param[in]: file1 - Name of file to be read and encoded.
* param[in]: file2 - Name of file to be written as encoded file.
* param[in]: tree - Tree that contains huffman table.
*/
void encodeFile (char const *file1, char const *file2, huffTree *tree);


/*
* description: Reads file and turns it into encoded bitString.
* param[in]: file1 - Name of file to be read.
* param[in]: tree - Tree that contains huffman table.
* return: bitString containing encoded file1 as bits.
*/
bitString *encodeFileToBitString (char const *file1, huffTree *tree);


/*
* description: Counts how many bits there are in a string of bits. String must
* contain NULLBYTE.
* param[in]: bits - Pointer to array of bits.
* return: Number of bits in string.
*/
int getBitLength (char *bits);


/*
* description: Writes the encoded file.
* param[in]: file2 - Name of file to be written.
* param[in]: size - size in number of charachters to be written.
*/
void writeEncode (char const *file2, unsigned char *text, int size);
