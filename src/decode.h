/*
* Support program for huffman.c
* Reads encoded file and decodes it. Write the decoded file based on huffman
* tree.
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
* description: Control flow for program. Does function calls and Deallocates
* memory.
* param[in]: file1 - Name of encoded file to be read and decoded.
* param[in]: file2 - Name of file to be written as decode.
* param[in]: tree - Huffman tree that can decode the encode.
*/
void decodeFile (char const *file1, char const *file2, huffTree *tree);


/*
* description: Gets length of file (nr of chars);
* param[in]: file - Name of file.
* return: length of file.
*/
int getFileLength (char const *file);


/*
* description: Reads encoded file and puts all text into char array allocated
* in heap.
* param[in]: file1 - Name of encoded file.
* param[in]: textLength - Length of encoded file.
* return: Pointer to allocated char array.
*/
bitString *readEncode (char const *file1, int textLength);


/*
* description: Reads bitString and decodes bits to chars. Writes decoded
* characthers to file.
* param[in]: fil2 - Name of file to write decode.
* param[in]: tree - The huffTree to read huffman table from.
* param[in]: bs - The bitString.
*/
void decodeBits (char const *file2, huffTree *tree, bitString *bs);


/*
* description: Locates key in huffTree. Keeps track of how many bits have been
* used, and if the set of given bits is not enough to find a leaf.
* param[in]: subRoot - Beginning node to traverse through.
* param[in]: bs - The bitString where pathway is stored.
* param[in]: byte - Current buffer of 8 bits to use as path.
* param[in]: currentByte - Which encoded byte bs is reading from.
* param[in]: currentBit - Position in buffer of bits.
* return: Key of the leaf that is found.
*/
unsigned char findKey (treeNode *subRoot, bitString *bs, char *byte,
						int *currentByte, int *currentBit);
