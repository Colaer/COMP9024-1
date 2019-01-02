#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"

int delete_word(char *begin_word);

List getCollection(){
    FILE *collection=fopen("collection.txt","r");
    List urls=newList();
    char word[1024];
    while(fscanf(collection,"%s",word)==1){
        int new=delete_word(word);
        insertLL(urls,new);
    }
    fclose(collection);
    return urls;
}

Graph getGraph(List urls){
    Graph urlGraph=newGraph(nElements(urls));
    Node tempnode;
    for (tempnode=first(urls);tempnode ; tempnode=next(tempnode)){
        char filename[BUFSIZ];
        sprintf(filename,"url%d.txt",url(tempnode));
        FILE *web=fopen(filename,"r");
        char addr[BUFSIZ];
        int out=0;
        while (fscanf(web,"%s",addr)==1){
            if (strcmp(addr,"#start")==0 || strcmp(addr,"Section-1")==0){
                continue;
            }
            if (strcmp(addr,"#end")==0){
                break;
            }
            int new_neighbor=delete_word(addr);
            int newID=getNodeID(urls,new_neighbor);
//            struct Edge *newEdge;
            //Edge *newEdge;
            Edge e;
            e.v=id(tempnode);
            e.w=newID;
            //newEdge->v=id(tempnode);
            //newEdge->w=newID;
            insertEdge(urlGraph,e);
            out++;
        }
        //curr->out=out;
        outdegree(tempnode,out);
        fclose(web);
    }
    return urlGraph;
}

int delete_word(char *begin_word){
    int j=0,k=0;
    int new_url;
    for(; begin_word[j]!='\0'; j++) {
        if (begin_word[j] != 'u' && begin_word[j] != 'r' && begin_word[j] != 'l')
            begin_word[k++] = begin_word[j];
    }
    begin_word[k]= '\0';
    new_url=atoi(begin_word);
    return new_url;
}



