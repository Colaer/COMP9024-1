/*
  listIteratorInt.c : list Iterator ADT implementation
  Written by FUDI ZHENG
  Date: 2017/12/29
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"

// data structures representing Doubly linked list
typedef struct Node {

    int value;  // value of this list item (int)
    struct Node *pre_node;  // pointer previous node in list
    struct Node *next_node; // pointer to next node in list

} Node;

typedef struct IteratorIntRep {
    Node *first_node;    //first node in list
    Node *cursor_pre;  //cursor pointer to previous
    Node *cursor_next; //cursor pointer to next
    Node *last_call;    //a call to one of next or previous or findNext or findPrevious
    int can_delete; //delete flag

} IteratorIntRep;

//create a new Doubly linked list Node
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

// Creates a new list iterator
IteratorInt IteratorIntNew(){
    IteratorInt it = malloc(sizeof (struct IteratorIntRep));
    assert(it!=NULL);
    //it->items=0;
    it->first_node=NULL;
    it->cursor_pre=NULL;
    it->cursor_next=NULL;
    it->last_call=NULL;
    it->can_delete=0;

    return it;
}
//Resets it to the start of the list
void reset(IteratorInt it){
    it->cursor_pre=NULL;
    it->cursor_next=it->first_node;
}

//Inserts the specified value v into the list iterator it
int add(IteratorInt it, int v){
    assert(it != NULL);
    Node *new = newNode(v);
    assert(new != NULL);
    //if cursor pointer to previous is null
    if (it->cursor_pre==NULL){
        it->first_node=new;
        //if cursor pointer to next is not null
        if (it->cursor_next!=NULL){
            it->cursor_next->pre_node=new;
            new->next_node=it->cursor_next;
        }
        it->cursor_pre=new;
        return 1;
    } else{
        it->cursor_pre->next_node=new;
        new->pre_node=it->cursor_pre;
        //if cursor pointer to next is not null
        if (it->cursor_next!=NULL){
            it->cursor_next->pre_node=new;
            new->next_node=it->cursor_next;
        }
        it->cursor_pre=new;
        return 1;
    }
    return 0;
}

/*Returns 1 if list iterator has more elements
when traversing the list in the forward direction,
returns 0 otherwise.*/
int hasNext(IteratorInt it){

    //if list iterator cursor pointer to next is not null, it has next node
    return it->cursor_next!=NULL;;
}
/*Returns 1 if list iterator has more elements
 when traversing the list in the reverse direction,
 returns 0 otherwise.*/
int hasPrevious(IteratorInt it){
    //if list iterator cursor pointer to previous is not null, it has previous node
    return it->cursor_pre!=NULL;
}

//Returns the pointer to the next value in the given list iterator and advances the cursor position
int *next(IteratorInt it){
    if (it->cursor_next==NULL)
        return NULL;
    //if cursor pointer to next is not null, list iterator advances the cursor position
    it->cursor_pre=it->cursor_next;
    it->cursor_next=it->cursor_next->next_node;
    it->last_call=it->cursor_pre;   //record this node so as to delete
    it->can_delete=1;   //delete flag is 1 indicating that delete method is successful

    return &it->cursor_pre->value; //return the current cursor's previous node value
}

//Returns the pointer to the previous value in the given list iterator and moves the cursor position backwards.
int *previous(IteratorInt it){
    if (it->cursor_pre ==NULL)
        return NULL;
    //if cursor pointer to previous is not null, list iterator moves the cursor position backwards.
    it->cursor_next=it->cursor_pre;
    it->cursor_pre=it->cursor_pre->pre_node;
    it->last_call=it->cursor_next;
    it->can_delete=1;

    return &it->cursor_next->value; //return the current cursor's next node value
}

//Deletes from the list iterator the last value that was returned by next or previous or findNext or findPrevious
int deleteElm(IteratorInt it){
    if (it->last_call==NULL)    //if the last value is null, return 0
        return 0;
    if (it->can_delete==0)      //if delete flag is 0 indicating that there is no element can be deleted, return 0
        return 0;
    if (it->first_node==NULL)   //if first node is null, it indicates that there are no elements in the list iterator
        return 0;
    Node *temp_node=it->first_node;  //temporary node pointer to first node
    //if the last element that was returned by next or previous or findNext or findPrevious is first node
    if (it->last_call==temp_node){
        it->first_node=it->first_node->next_node; //delete first node and new first node should be first node's next node
        it->first_node->pre_node=NULL;
    }else{ // if the last value is not first node
        for (; temp_node!=NULL &&  temp_node != it->last_call; ) {
            temp_node=temp_node->next_node;
        }
        //the node that will be deleted is found
        temp_node->pre_node->next_node=temp_node->next_node;
        // if this node has next node, next node's previous node should point to this node's previous node
        if (temp_node->next_node)
            temp_node->next_node->pre_node=temp_node->pre_node;
    }
    free(it->last_call); //free the node space
    it->can_delete=0;   //delete flag is 0
    //the list iterator cursor should be changed
    //1. the deleted element is cursor previous node
    if (it->last_call==it->cursor_pre) {
        it->cursor_pre = it->cursor_pre->pre_node;
    }
    //2. the deleted element is cursor next node
    if (it->last_call==it->cursor_next)
        it->cursor_next=it->cursor_next->next_node;
    return 1;  //return 1 if successful
}

//Replaces the last element returned by next or previous or findNext or findPrevious with the specified element
int set(IteratorInt it, int v){
    if (it->last_call==NULL)  //return 0 if the last element is null
        return 0;
    if (it->first_node==NULL) //return o if there is no element
        return 0;
    it->last_call->value=v; //replace the last element value by v

    return 1; //return 1 if successful
}

//Returns pointer to the next value in it that matches the given value v and advances the cursor position past the value returned.
int *findNext(IteratorInt it, int v){
    if (it->first_node==NULL)   //return null if there is no element
        return NULL;
    Node *cur=it->cursor_next;
    if (cur==NULL)  //return null if it has no next
        return NULL;
    //traverse the list so as to find the node whose value is v
    for (;cur!=NULL;) {
        if (cur->value==v)
            break;
        cur=cur->next_node;
    }
    //if this node exists, the list iterator advances the cursor position
    if (cur){
        it->cursor_pre=cur;
        it->cursor_next=cur->next_node;
        it->last_call=cur;
        it->can_delete=1;
    }
    // if this node exists, return its value. Otherwise, return null
    if (cur)
        return &cur->value;
    else
        return NULL;
}

//Returns pointer to the previous value in it that matches the given value v and moves the cursor position backwards before the value returned.
int *findPrevious(IteratorInt it, int v){
    if (it->first_node==NULL)   //return null if there is no element
        return NULL;
    Node *cur=it->cursor_pre;
    if (cur==NULL)  //return null if it has no previous node
        return NULL;
    //traverse the list so as to find the node whose value is v
    for (; cur!=NULL;) {
        if (cur->value==v)
            break;
        cur=cur->pre_node;
    }
    //if this node exists, the list iterator moves the cursor position backwards
    if (cur){
        it->cursor_next=cur;
        it->cursor_pre=cur->pre_node;
        it->last_call=cur;
        it->can_delete=1;
    }
    // if this node exists, return its value. Otherwise, return null
    if (cur)
        return &cur->value;
    else
        return NULL;

}
//free up all space associated with list iterator
void freeIt(IteratorInt it){
    //Resets it to the start of the list
    it->cursor_pre=NULL;
    it->cursor_next=it->first_node;
    //travesing the whole list iterator, free the associated node
    while(it->cursor_next!=NULL){
        Node *temp=it->cursor_pre;
        it->cursor_pre=it->cursor_next;
        it->cursor_next=it->cursor_next->next_node;
        free(temp);
    }
    it->first_node=NULL;
    free(it->first_node);
    free(it);
}





