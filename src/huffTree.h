/*
* huffTree: trie designed specificlly to build a huffman tree and table. Tree
* consists of weighted nodes and should be built with help of a pqueue.
*
* Warning: Using huffTree outside it's designed specifications is not
* recommended and commenced at own risk.
*
* Author: Buster Hultgren Warn <dv17bhn@cs.umu.se>
* Final build: 2018-02-13
*/

#ifndef _huffTree_
#define _huffTree_

#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode {

	int weight;
	unsigned char key;
	struct treeNode* left;
	struct treeNode* right;
} treeNode;

typedef struct huffTree {

	int size;
	char **huffTable;
	struct treeNode* root;
} huffTree;


/*
* description: Creates empty huffTree. Allocates memory for huffTree.
* param[in]: root - The treeNode that is the root of huffTree.
* param[in]: size - amount of characthers huffman table should include.
* return: empty huffTree.
*/
huffTree *huffTreeEmpty (treeNode *root, int size);


/*
* description: Checks if huffTree has a root.
* param[in]: tree - the huffTree.
* return: 1 if tree is empty, else 0.
*/
int huffTreeIsEmpty (huffTree *tree);


/*
* description: Deallocates all memory that huffTable has allocated. This
* includes all nodes, strings in huffTable, huffTable, huffTree.
* param[in]: tree - huffTree to be freed.
*/
void huffTreeKill (huffTree *tree);


/*
* description: Gets root of tree.
* param[in]: tree - The huffTree.
* return: The root of the huffTree.
*/
treeNode *huffTreeGetRoot (huffTree *tree);


/*
* description: Builds huffman table from huffTree by traversing tree and
* collecting pathways. Traversion is dont postorder by depth.
* param[in]: tree - the huffTree.
*/
void huffTreeTraverse (huffTree *tree);


/*
* description: Gets pathway to node in huffTre containing specific key.
* param[in]: tree -The huffTree.
* param[in]: key - The key.
* return: Pointer to allocated pathway. Pathway is array of chars, each char
* being 0 or 1. Last char is always '\0'
*/
char *huffTreeGetKeyPath (huffTree *tree, int key);


/*
* description: Creates new weighted leaf with key.
* param[in]: weight - Weight of the leaf.
* param[in]: key - Key of the leaf.
* return: - Pointer to allocated leaf.
*/
treeNode *nodeNewLeaf (int weight, unsigned char key);


/*
* description: Adds to nodes into new node. Weight of node will be the
* combined weight of both nodes. Key of node will be '\0' (ignored).
* param[in]: node1 - First node, will become left child.
* param[in]: node2 - Second node, will become right child.
* return: Pointer to allocated new node.
*/
treeNode *nodeNewNode (treeNode *node1, treeNode *node2);


/*
* description: Gets key of specific node.
* param[in]: node - The node.
* return: The key.
*/
unsigned char nodeGetKey (treeNode *node);


/*
* description: Checks if node is leaf.
* param[in]: node - node to be checked.
* return: 1 if node is leaf, else 0.
*/
int nodeIsLeaf (treeNode *node);


/*
* description: Checks if node has left child.
* param[in]: node - Node to be checked.
* return: 1 if node has left child, else 0.
*/
int nodeHasLeftChild (treeNode *node);


/*
* description: Checks if node has right child.
* param[in]: node - Node to be checked.
* return: 1 if node has right child, else 0.
*/
int nodeHasRightChild (treeNode *node);


/*
* description: Fetches left child of node.
* param[in]: node - The parent node.
* return: The left child of parent node if it exists, else NULL;
*/
treeNode *nodeGetLeftChild (treeNode *node);


/*
* description: Fetches right child of node.
* param[in]: node - The parent node.
* return: The right child of parent node if it exists, else NULL;
*/
treeNode *nodeGetRightChild (treeNode *node);


//SUPPORT FUNCTIONS FOR USE ONLY IN HUFFTREE.C


/*support function for huffTreeTraverse!
* description: Traverses through one roots nodes recursivly. Sends back path
* for all leafs it visit to the huffTree function traverses through.
* param[in]: tree - The huffTree being traversed.
* param[in]: subRoot - Child of root to be traversed through. Child becomes
* new root in next recursive function call.
* param[in]: level - Current level of depth in huffTree that node is located
* on.
* param[in]: path - Current path in huffTree to reach node.
* param[in]: newPath - The path it takes from subRoot to child. If child is
* left, subRoot is 0, else 1.
*/

void nodeTraverse (huffTree *tree, treeNode *subRoot, int level,
	 					  char *path, char newPath);


/* support function for nodeTraverse!
* description: Adds pathway huffman table (in huffTree) for a key.
* param[in]: tree - The huffTree.
* param[in]: key - The key.
* param[in]: path - Pathway to the key. Note: pathway is allocated in stack
* and not heap.
*/
void huffTreeAddBitPath (huffTree *tree, int key, char *path);


/* support function for huffTreeKill!
* description: Traverse recursivly through nodes to deallocate them.
* param[in]: node - Root node of all nodes to be deallocated.
*/
void nodeKill (treeNode *node);


#endif // _huffTree_
