// Written by Jack Gardner

#ifndef DATA_H
#define DATA_H

#include "List.h"
#include "Graph.h"

List   getCollection();
Graph  getGraph(List);
void   normalise(char *);
double appears(char *term, char *filename);
void   results(char *, List, double termsFound[]);

#endif
