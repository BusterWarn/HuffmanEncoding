/*
* Huffman compression program.
*
* Compresses file based on frequency analysis of letters used in input file.
* Builds a trie based on this analysis and then encodes / decodes desired file.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*/


#include "huffman.h"

/*
* description: Control flow of program.
* param[in]: Command  - -encode or -decode.
* param[in]: file0 - name of file to be analysed (read).
* param[in]: file1 - name of file to be encoded (read).
* param[in]: file2 - name of file to be encoded (write).
* return: 0 if input(s) is incorrect, else 1.
*/
int main (int argc, char const *argv[]) {

	if (fileValidation(argc, argv) == 0) {

		printf(" - quitting program\n");
		return 0;
	}

	//Making freq. analysis and building tree via pqueue.
	int* freqTable = freqAnalysis(argv[2]);
	pqueue *pq = fillPqueue(freqTable);
	huffTree *tree = fillhuffTree(pq);
	huffTreeTraverse(tree);

	//Encode or decode depending on command
	if (strcmp(argv[1], "-encode") == 0) {

		printf("Encoding...\n");
		encodeFile(argv[3], argv[4], tree);
		printf("Encoding complete!\n\n");
	} else {

		printf("Decoding...\n");
		decodeFile(argv[3], argv[4], tree);
		printf("Decode complete!\n\n");
	}

	free(freqTable);
	huffTreeKill(tree);
	pqueue_kill(pq);
	return 1;
}


/*
* description - Validates that input arguments in main func follows
* given structure.
* param[in]: argc - Number of input arguments.
* param[in]: argv - String array of input textfile names.
* return: 1 if files are valid, else 0.
*/
int fileValidation (int argc, char const *argv[]) {

	int valid = 1;
	FILE *fp;

	//If number of input arguments is else than 5.
	if (argc != 5) {

		fprintf(stderr, "Could not execute, too few/many arguments");
		valid = 0;
	}

	//If command is else than -encode or -decode.

	if (valid == 1) {

		if (strcmp(argv[1], "-encode") != 0 && strcmp(argv[1], "-decode") != 0) {

			fprintf(stderr, "'%s' is not a valid argument", argv[1]);
			valid = 0;
		}
	}

	//Rest of function checks that files 1-3 can be read or written to.

	if (valid == 1) {

		fp = fopen(argv[2], "r");
		if (fp == NULL) {

			fprintf(stderr, "Could not open %s", argv[2]);
			valid = 0;
		}
		fclose(fp);
	}

	if (valid == 1) {

		fp = fopen(argv[3], "r");
		if (fp == NULL) {

			fprintf(stderr, "Could not open %s", argv[3]);
			valid = 0;
		}
		fclose(fp);
	}

	if (valid == 1) {

		fp = fopen(argv[4], "w");
		if (fp == NULL) {

			fprintf(stderr, "Could not open %s", argv[4]);
			valid = 0;

		}
		fclose(fp);
	}

	return valid;
}


/*
* description: Analyses how often each char of extended ascii is used in file0.
* Allocates memory for int array.
* param[in]: file0 - Name of file0.
* return: Pointer to allocated array containing freq. results.
*/
int *freqAnalysis (char const *file0) {

	FILE *fp = fopen(file0, "r");
	int *freqTable = malloc(sizeof(int) * EXTASCIILEN);

	for (int i = 0; i < EXTASCIILEN; i++) {

		freqTable[i] = 0;
	}
    int currentChar = 0;

    while ((currentChar = fgetc(fp)) >= 0) {

		freqTable[currentChar]++;
    }

	fclose(fp);
	return freqTable;
}


/*
* description: Enqueues pqueue with results of freq. analysis. Allocates
* memory for pqueue.
* param[in]: *freqTable - Pointer to allocated array containing freq. results.
* return: pqueue filled with weighted nodes. Lesser weight is heigher prio.
*/
pqueue *fillPqueue (int *freqTable) {

	treeNode *tempNode;
	pqueue *pq = pqueue_empty(key_compare);
	for (int i = 0; i < EXTASCIILEN; i++) {

		tempNode = nodeNewLeaf(freqTable[i], (unsigned char)i);
		pqueue_insert(pq, tempNode);
	}

	return pq;
}


/*
* description: Builds huffman tree with result of freq. analysis stored in
* pqueue. Allocates memory for huffTree.
* param[in]: *pq - pqueue filled with weighted nodes.
* return: Weighted huffTree.
*/
huffTree *fillhuffTree (pqueue* pq) {

	huffTree *tree;

	while (!pqueue_is_empty(pq)) {

		treeNode *tempNode1;
		treeNode *tempNode2;
		treeNode *newNode;

		tempNode1 = pqueue_inspect_first(pq);
		pqueue_delete_first(pq);

		if (!pqueue_is_empty(pq)) {

			tempNode2 = pqueue_inspect_first(pq);
			pqueue_delete_first(pq);
		} else {

			tempNode2 = nodeNewLeaf(0, '\0');
		}
		newNode = nodeNewNode(tempNode1, tempNode2);

		if (!pqueue_is_empty(pq)) {

			pqueue_insert(pq, newNode);
		} else {

			tree = huffTreeEmpty(newNode, EXTASCIILEN);
		}
	}
	return tree;
}


/*
* description: Help funtion for pqueue to compare to elements. Each element is
* a node. Node with lesser weight has higher prio.
* param[in]: nodeIn1 - Void pointer to first element in pqueue.
* param[in]: nodeIn2 - Void pointer to second element in pqueue.
* return: 0 if both nodes have same prio, 1 if nodeIn1 has higher prio, else -1
*/
int key_compare (void *nodeIn1, void *nodeIn2) {

	treeNode *node1 = nodeIn1;
	treeNode *node2 = nodeIn2;

	int largest = 0;

	if (node1 -> weight > node2 -> weight) {

		largest = 1;

	} else if (node2 -> weight > node1 -> weight) {

		largest = -1;
	}

	return largest;
}
