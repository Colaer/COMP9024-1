// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015
// Modified by Jack Gardner and Zhenhao Chen

#ifndef GRAPH_H
#define GRAPH_H

typedef struct _GraphRep *Graph;

Graph newGraph(int);
void  disposeGraph(Graph);
int   addEdge(Graph, char *, char *);
int   nVertices(Graph);
void  showGraph(Graph, int);
int   vertexID(char *, Graph, int);
int   findDegree(char *, Graph);

char *vertex(Graph, int);
int   edge(Graph, int, int);

#endif
