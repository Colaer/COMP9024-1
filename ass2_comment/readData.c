#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"

int delete_word(char *begin_word);

List getCollection(){
    FILE *collection=fopen("collection.txt","r");   //open the file collection.txt
    List urls=newList();    //create new List
    char word[100];
    while(fscanf(collection,"%s",word)==1){ //read contents from the file collection.txt
        int new=delete_word(word);  //if read success. normalise the word
        insertLL(urls,new); //insert word to List urls
    }
    fclose(collection); //close the file
    return urls;
}

Graph getGraph(List urls){
    Graph urlGraph=newGraph(nElements(urls));   //create new graph
    Node tempnode;
    for (tempnode=first(urls);tempnode ; tempnode=next(tempnode)){  //loop for all urls
        char filename[100];
        sprintf(filename,"url%d.txt",url(tempnode));    //sends url(tempnode) output to a string filename by str
        FILE *web=fopen(filename,"r");  //open the urlxx.txt
        char addr[100];
        int out=0;
        while (fscanf(web,"%s",addr)==1){   //read data from urlxx.txt
            if (strcmp(addr,"#start")==0 || strcmp(addr,"Section-1")==0){   //check if word(addr) == "#start" or word(addr) == "Section-1"
                continue;
            }
            if (strcmp(addr,"#end")==0){    //check if word(addr)=="#end"
                break;
            }
            int new_neighbor=delete_word(addr); //normalise the word
            int newID=getNodeID(urls,new_neighbor); //get the Id of the word
            Edge e; //create new Edge
            e.v=id(tempnode);   //one node equals url from filename
            e.w=newID;          //another node equals url from the contents of filename.txt
            insertEdge(urlGraph,e); //insert new edge to graph urlGraph
            out++;  //record the number of outgoing links
        }
        outdegree(tempnode,out);    //get the outdegree for every url
        fclose(web);    //close the file
    }
    return urlGraph;
}

//normalise the word
int delete_word(char *begin_word){
    int j=0,k=0;
    int new_url;
    for(; begin_word[j]!='\0'; j++) {   //loop every digit for word until '\0'
        if (begin_word[j] != 'u' && begin_word[j] != 'r' && begin_word[j] != 'l')   //if 'u','r' or 'l' appears, delete
            begin_word[k++] = begin_word[j];
    }
    begin_word[k]= '\0';    //new word after normalise
    new_url=atoi(begin_word);   //convert char to int
    return new_url; //return integer xx after 'url'(urlxx)
}



