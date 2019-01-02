// Linked list interface ... COMP9024 17s2
#include "list.h"
#include "Graph.h"

List    getCollection();    //Create a set (list) of urls to process by reading	data from file "collection.txt"
Graph   getGraph(List); //For each url in the above	list read <url>.txt	file, and update graph by adding a node	and outgoing links
