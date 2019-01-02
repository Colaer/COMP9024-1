/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "InvertedIdx.h"
#include "ListStr.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
   Tree left, right;
   char  data[100];
   List  list;
} Node;

// make a new node containing data
Tree new2Node(Item it,char *url) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   strcpy(new->data, it);  // replace,   data(new) = it;
    new->list=new2List();
    insertSetOrd(new->list,url);
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%s\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}
//write tree to file
void Treetofile(Tree tree,FILE *f){
    if (tree==NULL)
        return;
    Treetofile(tree->left,f);
    Nodetofile(tree,f);
    Treetofile(tree->right,f);
}
//wirte data (data and List)from tree to file
void Nodetofile(Tree tree,FILE *f){
    if (tree==NULL)
        return;
    fprintf(f,"%s",tree->data);
    LNode temp;
    for (temp=first_node(tree->list); temp ; temp=temp->next) {
        fprintf(f," %s",url2(temp));
    }
    fprintf(f,"\n");
}

void printInorder(Tree t){
    if (t==NULL){
        return;
    }
    printInorder(t->left);
    printf("%s ",t->data);
    showLL(t->list);
    printInorder(t->right);
}
// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;

   else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
      return TreeSearch(left(t), it);
   
   else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
      return TreeSearch(right(t), it);

   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it,char *url) {
   if (t == NULL)
      t = new2Node(it,url);

   else if (strcmp(it, data(t)) < 0)   //replace, else if (it < data(t))
      left(t) = TreeInsert(left(t), it,url);

   else if (strcmp(it, data(t)) > 0)  //replace, else if (it > data(t))
      right(t) = TreeInsert(right(t), it,url);
   else{
       insertSetOrd(t->list,url);
   }
   return t;
}

