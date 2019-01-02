// list.h ... interface to simple List of Strings
// Written by Jack Gardner and Zhenhao Chen

#ifndef LIST_H
#define LIST_H

#define ASCENDING  0
#define DESCENDING 1
#define NEW_ID (-1)
#define for_node_in(list) for (Node node = head(list); node; node = next(node))

typedef struct _ListRep *List;
typedef struct _node *Node;

List  newList();
void  disposeList(List);
void  enterList(List, char *str, int ID);
List  orderList(List, double cmp[], int order);
int   getNodeID(List L, char *str);

Node  head(List);
Node  next(Node);
char *url(Node);
int   id(Node);
int   nNodes(List);

#endif
