/*
* bitString: Dynamiclly stores bits. bitString takes 0 and 1's represented as
* chars and convert these, when a full byte is collected, into an unsigned char
*
* bitString can also read unsigned chars and convert them into a byte.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*/


#include "bitString.h"


/*
* description: Creates empty bitString. Allocates memory for bitString.
* return: empty bitString.
*/
bitString *bitStringEmpty () {

	bitString *bs = malloc(sizeof(bitString));
	bs -> bits = NULL;
	bs -> encode = NULL;
	bs -> length = 0;
	bs -> nrOfBits = 0;

	return bs;
}


/*
* description: Deallocates all memory allocated by bitString, including
* the bitString itself.
* param[in]: bs - The bitString.
*/
void bitStringKill (bitString *bs) {

	free(bs -> bits);
	free(bs -> encode);
	free(bs);
}


/*
* description: Add bits to bitString. If bitString reaches 8 bits (1 byte) or
* more, bitString will encode these.
* param[in]: bs - The bitString.
* param[in]: bits - Pointer to char array where the bits are stored as either
* '1' or '0'.
* param[in]: nrOfBits - Number of bits added to bitString.
*/
void bitStringAddBits (bitString *bs, char *bits, int newBits) {

	newBits = newBits + bs -> nrOfBits;
	bs -> bits = realloc(bs -> bits, sizeof(char) * newBits);

	for (int i = 0; i < newBits - bs -> nrOfBits; i++) {

		bs -> bits[bs -> nrOfBits + i] = bits[i];
	}
	bs -> nrOfBits = newBits;

	encodeBytes(bs);
}


/*
* description: Adds an encoded byte to bitString.
* param[in]: bs - The bitString.
* param[in]: byte - The encoded byte.
*/
void bitStringAddByte (bitString *bs, unsigned char byte) {


	bs -> length++;
	bs -> encode = realloc(bs -> encode, sizeof(char) * bs -> length);
	bs -> encode[bs -> length - 1] = byte;
}


/*
* description: Reads encoded byte in bitString and points it back.
* param[in]: bs - The bitString.
* param[in]: byte - Pointer to char array of atleast size 8. Array will be
* changed to which byte was read.
* param[in]: byteNr - Index of stored encoded byte in bitString.
*/
void bitStringReadByte (bitString *bs, char *byte, int byteNr) {

	int encodedByte = bs -> encode[byteNr];
	intToByte(byte, encodedByte);
}


/*
* description: Gets all bits put to bitString encoded as unsigned char array.
* If there are not enough bits to create full bytes, padding (0's) will be
* added to end of the bits.
* param[in]: bs - The bitString.
* return: pointer to allocated memory of unsigned char array containing the
* encoded bits.
*/
unsigned char *bitStringGetEncode (bitString *bs) {

	addPadding(bs);
	encodeBytes(bs);
	return bs -> encode;
}


/*
* description: Gets size of the bitString. This is the length of the encoded
* char array.
* param[in]: bs - The bitString.
* return: Size of the bitString.
*/
int bitStringGetSize (bitString *bs) {

	return bs -> length;
}


/* SUPPORT FUNCTION FOR BITSTRING
* description: Encodes all possible bytes in bitString. If number of bits < 7;
* nothing will happen. Else, all bites that fill a byte will be encoded.
* param[in]: bs - The bitString
*/
void encodeBytes (bitString *bs) {

	int rest = bs -> nrOfBits % 8;
	int bytes = bs -> nrOfBits - rest;

	if (bytes >= 8) {

		int i = 0;
		int j = 0;
		unsigned char tempEncode[bytes];

		while (i < bytes) {

			tempEncode[j] = byteToInt(&bs -> bits[i]);

			i = i + 8;
			j++;
		}

		//     Reallocating memory for newly encoded text
		bs -> encode = realloc(bs -> encode, bs -> length + j);

		//     Adding tempEncode to encoded text
		//Using k since i and j already used
		for (int k = 0; k < j; k++) {

			bs -> encode[bs -> length + k] = tempEncode[k];
		}
		bs -> length = bs -> length + j;

		//     Deleting already encoded bits
		//Using l since i, j and k already used
		for (int l = 0; l < rest; l++) {

			bs -> bits[l] = bs -> bits [bytes + l];
		}
		bs -> bits = realloc(bs -> bits, rest);
		bs -> nrOfBits = rest;
	}
}


/* SUPPORT FUNCTION FOR BITSTRING
* description: If number of bits in bitString does not fill a full byte,
* padding (0's) will be added to end such that a byte can be filled.
* param[in]: bs - The bitString.
*/
void addPadding (bitString *bs) {

	int bitsToGo = bs -> nrOfBits % 8;

	if(bitsToGo > 0) {

		bitsToGo = 8 - bitsToGo;
	}

	if (bitsToGo > 0) {

		bs -> bits = realloc(bs -> bits, sizeof(char) * (bs -> nrOfBits + bitsToGo));
		for (int i = 0; i < bitsToGo; i++) {

			bs -> bits[bs -> nrOfBits + i] = '0';
		}
	}
	bs -> nrOfBits = bs -> nrOfBits + bitsToGo;
}


/* SUPPORT FUNCTION FOR BITSTRING
* description: Turns an integer from base 10 into a base 2 byte
* using euklides algorithm.
* param[in]: byte - Pointer to char array to store the 8 "bits".
* param[in]: base - Integer with base 10. Must not be larger than 255.
*/
void intToByte (char *byte, int base) {

	for (int i = 7; i >= 0; i--) {

		if (base > 0) {

			int remainder = base % 2;
			byte[i] = (char)(remainder + '0');
			base = (base - remainder) / 2;
		} else {
			byte[i] = '0';
		}
	}
}


/* SUPPORT FUNCTION FOR BITSTRING
* description: Turns a base 2 integer represented as a byte in a char array
* into an integer.
* param[in]: byte - Char array containing the 8 "bits".
* return: - The integer converted to base 10.
*/
int byteToInt (char *byte) {

	int intChar = 0;
	for (int i = 7; i >= 0; i--) {

		int bit = byte[i] - '0';
		int base = powerOf(2, 7 - i);
		intChar = intChar + (base * bit);
	}
	return intChar;
}


/* SUPPORT FUNCTION FOR BITSTRING
* description: Computes the a exponentiation of integers.
* param[in]: base - Base of the Exponentiation.
* param[in]: expontent - Expontent of the Exponentiation.
* return: The Exponentiation as an integer.
*/
int powerOf (int base, int exponent) {

	int Exponentiation = 1;
	for (int i = 0; i < exponent; i++) {

		Exponentiation = Exponentiation * base;
	}
	return Exponentiation;
}
