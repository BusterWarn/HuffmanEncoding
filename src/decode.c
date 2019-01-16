/*
* Support program for huffman.c
* Reads encoded file and decodes it. Write the decoded file based on huffman
* tree.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*/


#include "decode.h"


/*
* description: Control flow for program. Does function calls and Deallocates
* memory.
* param[in]: file1 - Name of encoded file to be read and decoded.
* param[in]: file2 - Name of file to be written as decode.
* param[in]: tree - Huffman tree that can decode the encode.
*/
void decodeFile (char const *file1, char const *file2, huffTree *tree) {

	int textLength = getFileLength(file1);
	bitString *bs = readEncode(file1, textLength);

	decodeBits(file2, tree, bs);

	bitStringKill(bs);
}


/*
* description: Gets length of file (nr of chars);
* param[in]: file - Name of file.
* return: length of file.
*/
int getFileLength (char const *file) {

	FILE *fp = fopen(file, "rb");
	int length = 0;

	while (fgetc(fp) >= 0) {

		length++;
	}

	fclose(fp);
	return length;
}


/*
* description: Reads encoded file and puts all text into char array allocated
* in heap.
* param[in]: file1 - Name of encoded file.
* param[in]: textLength - Length of encoded file.
* return: Pointer to allocated char array.
*/
bitString *readEncode (char const *file1, int textLength) {

	FILE *fp = fopen(file1, "rb");
	bitString *bs = bitStringEmpty();

	for (int i = 0; i < textLength; i++) {

		int currentChar = fgetc(fp);
		bitStringAddByte(bs, currentChar);
	}
	fclose(fp);
	return bs;
}


/*
* description: Reads bitString and decodes bits to chars. Writes decoded
* characthers to file.
* param[in]: fil2 - Name of file to write decode.
* param[in]: tree - The huffTree to read huffman table from.
* param[in]: bs - The bitString.
*/
void decodeBits (char const *file2, huffTree *tree, bitString *bs) {

	FILE *fp = fopen(file2, "w");

	int currentByte = 0; //Position of which encoded byte is read.
	int currentBit = 8; //Position in buffer of 8 bits. Set to 8 for reset in
						// while loop.
	unsigned char decodedByte = 0; // What key is found from huffTree.

	while (decodedByte != 4) {

		char byte[8]; //Buffer of 8 bits
		treeNode *subRoot = huffTreeGetRoot(tree);

		//If buffer has been worked through, load 8 new bits.
		if (currentBit == 8) {

			bitStringReadByte(bs, byte, currentByte);
			currentByte++;
			currentBit = 0;
		}

		decodedByte = findKey(subRoot, bs, byte, &currentByte, &currentBit);
		if (decodedByte != 4) {

			fputc(decodedByte, fp);
		}
	}
	fclose(fp);
}


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
						int *currentByte, int *currentBit) {

	while (!nodeIsLeaf(subRoot)) {

		//If buffer has been worked through, load 8 new bits.
		if (*currentBit >= 8) {

			bitStringReadByte(bs, byte, *currentByte);
			(*currentByte)++;
			*currentBit = 0;
		}
		if (byte[*currentBit] == '0') {

			subRoot = nodeGetLeftChild(subRoot);
		} else {

			subRoot = nodeGetRightChild(subRoot);
		}
		(*currentBit)++;
	}
	return nodeGetKey(subRoot);
}
