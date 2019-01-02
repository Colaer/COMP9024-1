/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "ListStr.h"

// data structures representing DLListStr

//typedef struct ListNode {
//	char   value[100];  // value of this list item (string)
//	LNode next;
//	               // pointer to next node in list
//}ListNode;

typedef struct ListRep {
	int  nitems;// count of items in list
	LNode first;
	LNode last;
} ListRep;

// create a new DLListNode (private function)
LNode newLNode(char *val)
{
	LNode new= malloc(sizeof(struct ListNode));
	assert(new != NULL);
	strcpy(new->value, val);  // for int, new->value = it;
	new->next = NULL;
	return new;
}

// create a new empty DLListStr
List new2List()
{
	List L = malloc(sizeof (struct ListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}


/* 
   pre-reqisite: L is ordered (increasing) with no duplicates
   post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
*/
void insertSetOrd(List L, char *val){
    char g[100];
    strcpy(g,val);
    assert(L!=NULL);
    LNode new=newLNode(val);
    assert(new!=NULL);
    if (L->first==NULL){
        L->first=L->last=new;
    }
    else {
        LNode tempnode=L->first;
        for (; tempnode; tempnode=tempnode->next) {
            if (strcmp(tempnode->value,g)==0)
                return;
        }
		L->last->next=new;
		L->last=new;
	}
    L->nitems++;

	/* 
	   implement this function to
	   insert val in L  (in order), no duplicates (set)

	*/
    if (L->nitems>=2) {
        //qsortList(L->first, L->last);
        bubblesort(L->first);
    }
}
void bubblesort(struct ListNode *start){
    int swapped;
    struct ListNode *ptr1 = start;
    struct ListNode *lptr = NULL;

    /* Checking for empty list */
    if (ptr1 == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
//            if (ptr1->data > ptr1->next->data)
            if (strcmp(ptr1->value,ptr1->next->value)>0)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
void swap(struct ListNode *a, struct ListNode *b)
{
    char temp[100];
    strcpy(temp,a->value);
//    int temp = a->data;
    strcpy(a->value,b->value);
//    a->data = b->data;
    strcpy(b->value,temp);
//    b->data = temp;
}

//void qsortList(LNode head,LNode tail){
////	if(head != tail && head->next != tail)
//    char l[10];
//    strcpy(l,tail->value);
//    char m[10];
//    strcpy(m,head->value);
//    char n[10];
//    strcpy(n,head->next->value);
//    if (strcmp(m,l)!=0 && strcmp(n,l)!=0)
//	{
//		struct ListNode *mid = partitionList(head, tail);
//		qsortList(head, mid);
//		qsortList(mid->next, tail);
//	}
//}

//LNode partitionList(LNode low, LNode high){
//	char  key[100];
//    //key= low->value;
//    strcpy(key, low->value);
//    struct  ListNode* loc = low;
//	for(LNode i = low->next; i != high; i = i->next)
////		if(i->value < key)
//		if (strcmp(i->value,key)<0)
//        {
//			loc = loc->next;
//            char a[100];
//            strcpy(a, i->value);
//            char b[100];
//            strcpy(b, loc->value);
//            strcpy(loc->value,a);
//            strcpy(i->value,b);
////			swap(i->value, loc->value);
//		}
//    char c[100];
//    char d[100];
//    strcpy(c,loc->value);
//    strcpy(d,low->value);
//    strcpy(loc->value,d);
//    strcpy(low->value,c);
//	//swap(loc->value, low->value);
//	return loc;
//}

//void swap(char *str1, char *str2)
//{
//    char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
//    strcpy(temp, str1);
//    strcpy(str1, str2);
//    strcpy(str2, temp);
//    free(temp);
//}
//void swap1(char **str1_ptr, char **str2_ptr)
//{
//    char *temp = *str1_ptr;
//    *str1_ptr = *str2_ptr;
//    *str2_ptr = temp;
//}

void showLL(List L){
	LNode tempnode=L->first;
	while(tempnode){
		printf("%s ",tempnode->value);
		tempnode=tempnode->next;
	}
    printf("\n");
}



// display items from a DLListStr, comma separated
void free2LL(List L) {
	assert(L!=NULL);
	LNode cur,pre;
	cur=L->first;
	if (cur != NULL) {
		pre=cur;
		cur=cur->next;
		free(pre);
	}
	free(L);
}

LNode first_node(List L){
    return L->first;
}
LNode next_node(LNode N){
    return N->next;
}
char *url2(LNode N){
    return N->value;
}
int L_elements(List L){
    return L->nitems;
}


