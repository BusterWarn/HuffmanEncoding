/*
* Huffman compression program.
*
* Compresses file based on frequency analysis of letters used in input file.
* Builds a trie based on this analysis and then encodes / decodes desired file.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*
* PROGRAM INPUTS / OUTPUT:
* param[in]: Command  - -encode or -decode.
* param[in]: file0 - name of file to be analysed (read).
* param[in]: file1 - name of file to be encoded (read).
* param[in]: file2 - name of file to be encoded (write).
* return: 0 if input(s) is incorrect, else 1.
*/


#include <stdio.h>
#include <stdlib.h>

#include "encode.h"
#include "decode.h"
#include "pqueue.h"
#include "huffTree.h"

#define EXTASCIILEN 256

/*
* description - Validates that input arguments in main func follows
* given structure.
* param[in]: argc - Number of input arguments.
* param[in]: argv - String array of input textfile names.
* return: 1 if files are valid, else 0.
*/
int fileValidation (int argc, char const *argv[]);


/*
* description: Analyses how often each char of extended ascii is used in file0.
* Allocates memory for int array.
* param[in]: file0 - Name of file0.
* return: Pointer to allocated array containing freq. results.
*/
int *freqAnalysis (char const *file0);


/*
* description: Enqueues pqueue with results of freq. analysis. Allocates
* memory for pqueue.
* param[in]: *freqTable - Pointer to allocated array containing freq. results.
* return: pqueue filled with weighted nodes. Lesser weight is heigher prio.
*/
pqueue *fillPqueue (int *freqTable);


/*
* description: Builds huffman tree with result of freq. analysis stored in
* pqueue. Allocates memory for huffTree.
* param[in]: *pq - pqueue filled with weighted nodes.
* return: Weighted huffTree.
*/
huffTree *fillhuffTree (pqueue* pq);


/*
* description: Help funtion for pqueue to compare to elements. Each element is
* a node. Node with lesser weight has higher prio.
* param[in]: nodeIn1 - Void pointer to first element in pqueue.
* param[in]: nodeIn2 - Void pointer to second element in pqueue.
* return: 0 if both nodes have same prio, 1 if nodeIn1 has higher prio, else -1
*/
int key_compare (void* nodeIn1, void* nodeIn2);
