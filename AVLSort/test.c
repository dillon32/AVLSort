#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"
#include "AVLNode.h"
#include <string.h>

struct AVLTree *
createTree(){

	struct AVLTree * tree =
		(struct AVLTree *)malloc(sizeof(struct AVLTree *));

	tree->root = NULL;

	return tree;
}

/*createLeaf() will add a leaf node to the ABL tree*/
struct AVLNode *
createAVLNode(){

	struct AVLNode * AVLNode =
		(struct AVLNode *)malloc(sizeof(struct AVLNode *));

	AVLNode->left = NULL;
	AVLNode->right = NULL;
	AVLNode->value = NULL;

	return AVLNode;
}

/*leafHeight() will provide a leaf's height*/
int
nodeHeight(struct AVLNode * AVLNode){

	int left = 0;
	int right = 0;

	if(AVLNode->left){
		left = nodeHeight(AVLNode->left);
	}
	if(AVLNode->right){
		right = nodeHeight(AVLNode->right);
	}

	return right > left ? ++right : ++left;
}

/*balanceFactor() returns the balance of an
 *AVL node, which will be useful when "rotating"
 *nodes to create a true AVL tree.*/
int
balanceFactor(struct AVLNode * AVLNode){

	int balance = 0;

	if(AVLNode->left)
		balance += nodeHeight(AVLNode->left);
	if(AVLNode->right)
		balance -= nodeHeight(AVLNode->right);

	return balance;
}

/*The next four methods all involve specific
 *rotations for a given node. These mathods
 *do the "balancing" of the AVL tree.*/
struct AVLNode *
doubleLeftRotate(struct AVLNode * AVLNode){
	
	struct AVLNode * x = AVLNode;
	struct AVLNode * y = x->left;

	x->left = y->right;
	y->right = x;

	return y;
}

struct AVLNode *
leftRightRotate(struct AVLNode * AVLNode){

	struct AVLNode * x = AVLNode;
	struct AVLNode * y = x->left;
	struct AVLNode * z = y->right;

	x->left = z->right;
	y->right = z->left;
	z->left = y;
	z->right = x;

	return z;
}

struct AVLNode *
rightLeftRotate(struct AVLNode * AVLNode){

	struct AVLNode * x = AVLNode;
	struct AVLNode * y = x->right;
	struct AVLNode * z = y->left;

	x->right = z->left;
	y->left = z->right;
	z->right = y;
	z->left = x;

	return z;
}

struct AVLNode *
doubleRightRotate(struct AVLNode * AVLNode){

	struct AVLNode * x = AVLNode;
	struct AVLNode * y = x->right;

	x->right = y->left;
	y->left = x;

	return y;
}

/*balanceNode() will level out the
 *right and left heights of a node
 *using the previous methods to ensure
 *that the tree has log(n) efficiency*/
struct AVLNode *
balanceNode(struct AVLNode * AVLNode){

	struct AVLNode * newRoot =
		(struct AVLNode *)malloc(sizeof(struct AVLNode *));

	if(AVLNode->left)
		AVLNode->left = balanceNode(AVLNode->left);
	if(AVLNode->right)
		AVLNode->right = balanceNode(AVLNode->right);

	int balance = balanceFactor(AVLNode);

	if(balance >= 2){
		if(balanceFactor(AVLNode->left) <= -1)
			newRoot = leftRightRotate(AVLNode);
		else
			newRoot = doubleLeftRotate(AVLNode);
	} else if(balance <= -2){
		if(balanceFactor(AVLNode->right) >= 1)
			newRoot = rightLeftRotate(AVLNode);
		else
			newRoot = doubleRightRotate(AVLNode);
	} else
		newRoot = AVLNode;

	return newRoot;
}//end balanceNode()

void
balanceTree(struct AVLTree * tree){

	struct AVLNode * newRoot =
		(struct AVLNode *)malloc(sizeof(struct AVLNode *));

	newRoot = balanceNode(tree->root);

	if(newRoot != tree->root)
		tree->root = newRoot;
}

/*insertNode() will actuall insert a
 *a node into the AVL tree.*/

void
insertNode(struct AVLTree * tree, char * value){

	struct AVLNode * AVLNode = NULL;
	struct AVLNode * next = NULL;
	struct AVLNode * last = NULL;

	/*The first conditional determines if a
	 *root node has already been created.*/
	if(tree->root == NULL){
		AVLNode = createAVLNode();
		AVLNode->value = value;
		AVLNode->count++;

		tree->root = AVLNode;
	} else {
		next = tree->root;
		
		while(next!= NULL){
			last = next;
			if(strcmp(value, next->value) < 0){
				next = next->left;
			} else if(strcmp(value, next->value) > 0){
				next = next->right;
			} else{
				next->count++;
				return;
			}
		}//end while loop

		AVLNode = createAVLNode();
		AVLNode->value = value;

		if(strcmp(value, last->value) < 0)
			last->left = AVLNode;
		if(strcmp(value, last->value) > 0)
			last->right = AVLNode;
	}//end if/else block

	balanceTree(tree);
}//end insertNode()

/*printTree() will perform a in-order
 *traversal of the tree, printing the
 *left subtrees, then root, and then
 *right subtree.*/
void
printTree(struct AVLNode * AVLNode, int depth){

	int i = 0;

	if(AVLNode->left)
		printTree(AVLNode->left, depth + 2);

	for(i; i < depth; i++);
	printf("%s\n", AVLNode->value);

	if(AVLNode->right)
		printTree(AVLNode->right, depth + 2);
}

int
main(int argc, char ** argv){

	printf("This program will collect user-input words\nand sort them alphabetically using an AVL tree.\nUser must restrict input to words <=16 characters long.\n\n");

	struct AVLTree * tree = createTree();
	const char a[16];
	char * b;

	while(1)
	{
		printf("Enter word or enter digit to print sorted words:\n");
		b = (char *)malloc(16);
		scanf("%s", a);
		if(!isdigit(a[0])){
			strcpy(b, a);
			insertNode(tree, b);
		} else
			break;
	}

	printTree(tree->root, 0);
	
	return 0;
}
