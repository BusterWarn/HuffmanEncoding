/*
* bitString: Dynamiclly stores bits. bitString takes 0 and 1's represented as
* chars and convert these, when a full byte is collected, into an unsigned char
*
* bitString can also read unsigned chars and convert them into a byte.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*/


#ifndef BITSTRING
#define BITSTRING

#include <stdio.h>
#include <stdlib.h>


typedef struct {

	int length;
	int nrOfBits;
	char *bits;
	unsigned char *encode;
} bitString;


/*
* description: Creates empty bitString. Allocates memory for bitString.
* return: empty bitString.
*/
bitString *bitStringEmpty ();


/*
* description: Deallocates all memory allocated by bitString, including
* the bitString itself.
* param[in]: bs - The bitString.
*/
void bitStringKill (bitString *bs);


/*
* description: Add bits to bitString. If bitString reaches 8 bits (1 byte) or
* more, bitString will encode these.
* param[in]: bs - The bitString.
* param[in]: bits - Pointer to char array where the bits are stored as either
* '1' or '0'.
* param[in]: nrOfBits - Number of bits added to bitString.
*/
void bitStringAddBits (bitString *bs, char *bits, int nrOfBits);



/*
* description: Adds an encoded byte to bitString.
* param[in]: bs - The bitString.
* param[in]: byte - The encoded byte.
*/
void bitStringAddByte (bitString *bs, unsigned char byte);


/*
* description: Reads encoded byte in bitString and points it back.
* param[in]: bs - The bitString.
* param[in]: byte - Pointer to char array of atleast size 8. Array will be
* changed to which byte was read.
* param[in]: byteNr - Index of stored encoded byte in bitString.
*/
void bitStringReadByte (bitString *bs, char *byte, int byteNr) ;


/*
* description: Gets all bits put to bitString encoded as unsigned char array.
* If there are not enough bits to create full bytes, padding (0's) will be
* added to end of the bits.
* param[in]: bs - The bitString.
* return: pointer to allocated memory of unsigned char array containing the
* encoded bits.
*/
unsigned char *bitStringGetEncode (bitString *bs);


/*
* description: Gets size of the bitString. This is the length of the encoded
* char array.
* param[in]: bs - The bitString.
* return: Size of the bitString.
*/
int bitStringGetSize (bitString *bs);



/* SUPPORT FUNCTION FOR BITSTRING
* description: Encodes all possible bytes in bitString. If number of bits < 7;
* nothing will happen. Else, all bites that fill a byte will be encoded.
* param[in]: bs - The bitString
*/
void encodeBytes (bitString *bs);


/* SUPPORT FUNCTION FOR BITSTRING
* description: If number of bits in bitString does not fill a full byte,
* padding (0's) will be added to end such that a byte can be filled.
* param[in]: bs - The bitString.
*/
void addPadding (bitString *bs);


/* SUPPORT FUNCTION FOR BITSTRING
* description: Turns an integer from base 10 into a base 2 byte
* using euklides algorithm.
* param[in]: byte - Pointer to char array to store the 8 "bits".
* param[in]: base - Integer with base 10. Must not be larger than 255.
*/
void intToByte (char *byte, int base);


/* SUPPORT FUNCTION FOR BITSTRING
* description: Turns a base 2 integer represented as a byte in a char array
* into an integer.
* param[in]: byte - Char array containing the 8 "bits".
* return: - The integer converted to base 10.
*/
int byteToInt (char *byte);


/* SUPPORT FUNCTION FOR BITSTRING
* description: Computes the a exponentiation of integers.
* param[in]: base - Base of the Exponentiation.
* param[in]: expontent - Expontent of the Exponentiation.
* return: The Exponentiation as an integer.
*/
int powerOf (int base, int exponent);


#endif //BITSTRING
