
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readData.h"

int main(int argc,char *argv[]){
    double d,diffPR;//d - damping factor, diffPR - difference in PageRank sum
    int maxIterations;//maxIterations - maximum iterations
    //require input three arguments d, diffPR,maxIterations
    if  (argc!=4){
        printf("wrong command input");
        return 1;
    }
    d=atof(argv[1]);    //The C library function atof(const char *str) converts the string argument str to a floating-point number.
    diffPR=atof(argv[2]);
    maxIterations=atoi(argv[3]);    //The C library function atoi(const char *str) converts the string argument str to an integer.
    List urls=getCollection();  //the function reads urls from collection.txt.
    Graph g=getGraph(urls); //read out urls from urlxx.txt and build a graph.
    int N=nElements(urls);  // N is the number of url
    //check if there are urls whose outdegree is zero
    Node out_degree_zero;
    for (out_degree_zero=first(urls); out_degree_zero; out_degree_zero=next(out_degree_zero)) {
        if (out(out_degree_zero)==0){
            int i;
            for (i = 0; i < N ; ++i) {  //set the url whose outdegree is zero connect to the other urls except itself.
                if (i!=id(out_degree_zero)){
                    Edge e;
                    e.v=id(out_degree_zero);
                    e.w=i;
                    insertEdge(g,e);    //insert new edge
                }
            }
        }
    }
    double pr[N];
    double prev[N];
    double dN=(double)N;
    int i;
    //initialise every url pagerank value = 1/N (N=number of urls in the collection)
    for (i = 0; i < N; ++i) {
        pr[i]=prev[i]=1.0/dN;
    }

    int iteration=0;
    double diff=diffPR;//to enter the following loop
    double damping_value=(1.0-d)/dN;//easy for every calculation
    //Simplified PageRank Algorithm from wiki
    while(iteration<maxIterations && diff >=diffPR){
        iteration++;
        diff=0.0;
        Node tempnode;
        for (tempnode=first(urls);tempnode; tempnode=next(tempnode)){//Traverse each node in the list (every url)
            double rank=0.0;
            int i;
            for (i = 0; i <N ; i++) {//Traverse each node in the Adjacency matrix
                if (adjacent(g,i,id(tempnode))){//check if they are adjacent nodes
                    Node temp;
                    for (temp=first(urls);temp; temp=next(temp)){//find the outdegree of the url which is the incident url of tempnode
                        if (id(temp)==i) {
                            double outlength;
                            if (out(temp)!=0){ // if the incident url whose outdegree is not zero, find its outdegree
                                outlength = out(temp);
                            }
                            if (out(temp)==0){ //if the incident url whose outdegree is zero, outdegree is the number of total urls minus 1 (N-1)
                                outlength = N-1;
                            }
                            rank += d * pr[i]/outlength;//according to the given formula
                        }
                    }
                }
            }
            rank+=damping_value;    //one complete calculation
            diff+=fabs(rank-pr[id(tempnode)]); //The C library function double fabs(double x) returns the absolute value of x.
            prev[id(tempnode)]=rank; // store the calculation result
        }
        int j;
        for (j = 0; j <N ; ++j) { // in order to t+1 iteration calculation
            pr[j]=prev[j];
        }
    }
    double newpr[N];

    for (i = 0; i < N; ++i) { //copy the whole pagerank value for every url to new array.
        newpr[i]=pr[i];
    }

    List order_list=orderList(urls,pr);//Reorder the list by pagerank value;

    FILE *outf=fopen("pagerankList.txt","w");//create new .txt file
    //write url,outdegree, pr value to the txt file
    Node outputnode;
    for (outputnode=first(order_list);outputnode; outputnode=next(outputnode)){
        fprintf(outf,"url%d, %d, %.7lf\n",url(outputnode),out(outputnode),newpr[id(outputnode)]);
    }
    fclose(outf);//The C library function int fclose(FILE *stream) closes the stream.
    freeLL(urls);// free memory associated with linked list urls
    freeGraph(g); // free memory assocauted with graph g
    return 0;

}

