// Linked list implementation ... COMP9024 17s2
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

// data structures representing linked list
struct node {
    int url;    // url
    int id; // id in order to identify url
    int outdegree;  // the number of outgoing links
    Node next;  // pointer to next node in list
};

struct ListRep{
    int elements;   //the number of urls
    Node first; //first node in list
    Node last;  //last node in list
};

//create new linked list Node
Node newNode(int n) {
    Node new = malloc(sizeof(struct node));
    assert(new != NULL);
    new->url = n;
    new->id=0;
    new->outdegree=0;
    new->next = NULL;
    return new;
}
//Creates a new list
List newList(){
   List L=malloc(sizeof(struct ListRep));
   assert(L!=NULL);
   L->elements=0;
   L->first=NULL;
   L->last=NULL;
   return L;
}
//Inserts the specified value n into the List L
void insertLL(List L, int n) {
    //if List is Null
   if (L->first==NULL){
       Node new=newNode(n);
       new->id=L->elements;
       L->first=L->last=new;
   } else{
       Node new=newNode(n);
       new->id=L->elements;
       L->last->next=new;
       L->last=new;
   }
   L->elements++;
}

//get n's ID from List L
int getNodeID(List L,int n){
    Node cur=L->first;
    while (cur!=NULL){
        if (cur->url==n){
            return cur->id;
        }
        cur=cur->next;
    }
    return 0;
}
//order the list by descending order
List orderList(List urls,double pr[]){
    List orderlist=newList();
    int i;
    for (i = 0; i <urls->elements ; ++i) {
        int maxid = maxID(urls, pr);
//        printf("%d\n",maxid);
        Node tempnode = first(urls);
        for (; tempnode && id(tempnode) != maxid; tempnode = next(tempnode)) {
        }
        insertLL(orderlist, url(tempnode));
        Node tempnode1 = first(orderlist);
        for (; tempnode1 && url(tempnode1) != url(tempnode); tempnode1 = next(tempnode1)) {
        }
        tempnode1->outdegree = tempnode->outdegree;
        tempnode1->id=tempnode->id;
    }
    return orderlist;
}

//because of descending order, find the max ID every time
//set the previous max ID=0 in order to find 2th max ID until last one
int maxID(List urls,double pr[]){
    int N=urls->elements;
    int ID=0;
    double max=pr[0];
    int i;
    for (i = 1; i <N ; ++i) {
        if (pr[i]>max){
            max=pr[i];
            ID=i;
        }
    }
    pr[ID]=0;
    return ID;
}

// free memory associated with List L
void freeLL(List L) {
   assert(L!=NULL);
   Node cur,pre;
   cur=L->first;
   if (cur != NULL) {
      pre=cur;
      cur=cur->next;
      free(pre);
   }
   free(L);
}
//return first node of List L
Node first(List L) {
    return L->first;
}
//return next of node of Node N
Node next(Node N) {
    return N->next;
}
//return the value of Node N
int url(Node N){
    return N->url;
}
//set the outdegree of Node N equals degree
void outdegree(Node N,int degree){
    N->outdegree=degree;
}
//return the id of Node N
int id(Node N){
    return N->id;
}
//return the number of outgoing links of Node N
int out(Node N) {
    return N->outdegree;
}
//return the number of elements (urls)
int nElements(List L){
    return L->elements;
}