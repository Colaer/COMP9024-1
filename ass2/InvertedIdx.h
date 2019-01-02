/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdbool.h>
#include "ListStr.h"

typedef char *Item;      // item is just a key

typedef struct Node *Tree;

Tree newTree();// create an empty Tree
Tree new2Node(Item it,char *url);
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)
void showTreeR(Tree t, int depth);
void printInorder(Tree t);
void Nodetofile(Tree tree,FILE *f);
void Treetofile(Tree tree,FILE *f);

bool TreeSearch(Tree, Item);   // check whether an item is in a Tree
Tree TreeInsert(Tree, Item, char *url);   // insert a new item into a Tree



