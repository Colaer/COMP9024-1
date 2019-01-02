// Linked list implementation ... COMP9024 17s2
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

struct node {
    int url;
    int id;
    int outdegree;
    Node next;
};

struct ListRep{
    int elements;
    Node first;
    Node last;
};


Node newNode(int n) {
    Node new = malloc(sizeof(struct node));
    assert(new != NULL);
    new->url = n;
    new->id=0;
    new->outdegree=0;
    new->next = NULL;
    return new;
}
List newList(){
   List L=malloc(sizeof(struct ListRep));
   assert(L!=NULL);
   L->elements=0;
   L->first=NULL;
   L->last=NULL;
   return L;
}

void insertLL(List L, int n) {
   if (L->first==NULL){
       Node new=newNode(n);
       new->id=L->elements;
       L->first=L->last=new;
   }else{
       Node new=newNode(n);
       new->id=L->elements;
       L->last->next=new;
       L->last=new;
   }
   L->elements++;
}

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
Node first(List L) {
    return L->first;
}
Node next(Node N) {
    return N->next;
}
int url(Node N){
    return N->url;
}
void outdegree(Node N,int degree){
    N->outdegree=degree;
}
int id(Node N){
    return N->id;
}
int out(Node N) {
    return N->outdegree;
}
int nElements(List L){
    return L->elements;
}