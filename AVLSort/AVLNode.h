#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"

//Constructs a node for an AVL tree
struct AVLNode {
	char * value;
	int count;
	struct AVLNode * left;
	struct AVLNode * right;
};

