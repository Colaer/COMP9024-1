/*
  listIteratorInt.c : list Iterator ADT implementation
  Written by ....
  Date: ....
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

typedef struct Node {

    int value;
    struct Node *pre_node;
    struct Node *next_node;

    // implement struct here ..

} Node;

typedef struct IteratorIntRep {
    //int items;
    Node *first;
    Node *pre;
    Node *next;
    Node *last_call;
    int can_delete;
    // implement struct here ..

} IteratorIntRep;


static Node *newNode(int v)
{
    Node *new;
    new = malloc(sizeof(Node));
    assert(new != NULL);
    new->value = v;
    new->pre_node = new->next_node = NULL;
    return new;
}

/*

  Your local functions here, if any....


 */


IteratorInt IteratorIntNew(){
    IteratorInt it = malloc(sizeof (struct IteratorIntRep));
    assert(it!=NULL);
    //it->items=0;
    it->first=NULL;
    it->pre=NULL;
    it->next=NULL;
    it->last_call=NULL;
    it->can_delete=0;
    // implement this function

    return it;  // you need to change this...
}

void reset(IteratorInt it){

    it->pre=NULL;
    it->next=it->first;
    // implement this function

}


int add(IteratorInt it, int v){
    assert(it != NULL);
    Node *new = newNode(v);
    assert(new != NULL);
    if (it->pre==NULL){
        it->first=new;
        if (it->next!=NULL){
            it->next->pre_node=new;
            new->next_node=it->next;
        }
        it->pre=new;
        return 1;
    } else{
        it->pre->next_node=new;
        new->pre_node=it->pre;
        if (it->next!=NULL){
            it->next->pre_node=new;
            new->next_node=it->next;
        }
        it->pre=new;
        return 1;
    }
    return 0;
    // implement this function

    // you need to change this...
}


int hasNext(IteratorInt it){

    // implement this function

    return it->next!=NULL;;  // you need to change this...
}

int hasPrevious(IteratorInt it){

    // implement this function

    return it->pre!=NULL;  // you need to change this...
}


int *next(IteratorInt it){
    if (it->next==NULL)
        return NULL;
    it->pre=it->next;
    it->next=it->next->next_node;
    it->last_call=it->pre;
    it->can_delete=1;
    // implement this function

    return &it->pre->value;  // you need to change this...
}

int *previous(IteratorInt it){
    if (it->pre ==NULL)
        return NULL;
    it->next=it->pre;
    it->pre=it->pre->pre_node;
    it->last_call=it->next;
    it->can_delete=1;
    // implement this function

    return &it->next->value;  // you need to change this...
}


int deleteElm(IteratorInt it){
    if (it->last_call==NULL)
        return 0;
    if (it->can_delete==0)
        return 0;
    if (it->first==NULL)
        return 0;
    Node *temp_node=it->first;
    if (it->last_call==temp_node){
        it->first=it->first->next_node;
        it->first->pre_node=NULL;
    }else{
        for (; temp_node!=NULL &&  temp_node != it->last_call; ) {
            temp_node=temp_node->next_node;
        }
        temp_node->pre_node->next_node=temp_node->next_node;
        if (temp_node->next_node)
            temp_node->next_node->pre_node=temp_node->pre_node;
    }
    free(it->last_call);
    it->can_delete=0;
    if (it->last_call==it->pre) {
        it->pre = it->pre->pre_node;
    }
    if (it->last_call==it->next)
        it->next=it->next->next_node;
    return 1;
    // implement this function

    //return 0;  // you need to change this...
}


int set(IteratorInt it, int v){
    if (it->last_call==NULL)
        return 0;
    if (it->first==NULL)
        return 0;
    it->last_call->value=v;
    // implement this function

    return 1;
}

int *findNext(IteratorInt it, int v){
    if (it->first==NULL)
        return NULL;
    Node *cur=it->next;
    if (cur==NULL)
        return NULL;
    for (;cur!=NULL;) {
        if (cur->value==v)
            break;
        cur=cur->next_node;
    }
    if (cur){
        it->pre=cur;
        it->next=cur->next_node;
        it->last_call=cur;
        it->can_delete=1;
    }


    // implement this function
    if (cur)
        return &cur->value;
    else
        return NULL;
}

int *findPrevious(IteratorInt it, int v){
    if (it->first==NULL)
        return NULL;
    Node *cur=it->pre;
    if (cur==NULL)
        return NULL;
    for (; cur!=NULL;) {
        if (cur->value==v)
            break;
        cur=cur->pre_node;
    }
    if (cur){
        it->next=cur;
        it->pre=cur->pre_node;
        it->last_call=cur;
        it->can_delete=1;
    }
    if (cur)
        return &cur->value;
    else
        return NULL;

    // implement this function

    //return 0;
}

void freeIt(IteratorInt it){
    it->pre=NULL;
    it->next=it->first;

    while(it->next!=NULL){
        it->next->value=*next(it);
        free(it->pre);
    }
    it->first=NULL;
    free(it);
    // implement this function
   // return;

}





