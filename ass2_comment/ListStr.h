// DLListStr.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2017 

#ifndef DLListStr_H
#define DLListStr_H

#include <stdio.h>
#include "ListStr.h"

// External view of DLListStr
// Implementation given in DLListStr.c
// Implements a DLListStr of string 

typedef struct ListRep *List;

typedef struct ListNode *LNode;
typedef struct ListNode {
    char   value[100];  // value of this list item (string)
    LNode next;
    // pointer to next node in list
}ListNode;


List new2List();
LNode newLNode(char *val);
void insertSetOrd(List L, char *val);
void qsortList(LNode head,LNode tail);
LNode partitionList(LNode low, LNode high);

void swap1(char **str1_ptr, char **str2_ptr);
void bubblesort(struct ListNode *start);
/* Function to swap data of two nodes a and b*/
void swap(struct ListNode *a, struct ListNode *b);
void showLL(List L);
void free2LL(List);


LNode first_node(List);
LNode next_node(LNode);
LNode pre_node(LNode);
char *url2(LNode);
int L_elements(List);

#endif
