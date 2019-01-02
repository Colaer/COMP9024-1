// Linked list interface ... COMP9024 17s2
//#include <stdbool.h>
#ifndef LIST_H
#define LIST_H


typedef struct node *Node;
typedef struct ListRep *List;
//typedef struct Node   Node;

List newList();
void insertLL(List, int);
int getNodeID(List,int);
void freeLL(List);
List orderList(List,double pr[]);
int maxID(List ,double pr[]);


Node first(List);
Node next(Node);
int url(Node);
void outdegree(Node, int);
int id(Node);
int out(Node);
int nElements(List);
#endif