
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readData.h"

void quick_sort(double arr[], int start, int end);
int partition(double arr[], int low, int high);
//d - damping factor, diffPR - difference in PageRank sum, maxIterations - maximum iterations
int main(int argc,char *argv[]){
    double d,diffPR;
    int maxIterations;
    if  (argc!=4){
        printf("wrong command input");
        return 1;
    }
    d=atof(argv[1]);
    diffPR=atof(argv[2]);
    maxIterations=atoi(argv[3]);
    //printf("%f",d);
//    d=0.85;
//    diffPR=0.00001;
//    maxIterations=1000;
    List urls=getCollection();
    Graph g=getGraph(urls);
    int N=nElements(urls);
    Node out_degree_zero;
    for (out_degree_zero=first(urls); out_degree_zero; out_degree_zero=next(out_degree_zero)) {
        if (out(out_degree_zero)==0){
            int i;
            for (i = 0; i < N ; ++i) {
                if (i!=id(out_degree_zero)){
                    Edge e;
                    e.v=id(out_degree_zero);
                    e.w=i;
                    insertEdge(g,e);
                }
            }
        }
    }
    double pr[N];
    double prev[N];
    double dN=(double)N;
    int i;
    for (i = 0; i < N; ++i) {
        pr[i]=prev[i]=1.0/dN;
    }

//    for (int i = 0; i < N; ++i) {
//        printf("%.20f\n",pr[i]);
//    }
    int iteration=0;
    double diff=diffPR;
    double damping_value=(1.0-d)/dN;
    while(iteration<maxIterations && diff >=diffPR){
        iteration++;
        diff=0.0;
        Node tempnode;
        for (tempnode=first(urls);tempnode; tempnode=next(tempnode)){
            double rank=0.0;
            int i;
            for (i = 0; i <N ; i++) {
                if (adjacent(g,i,id(tempnode))){
                    Node temp;
                    for (temp=first(urls);temp; temp=next(temp)){
                        if (id(temp)==i) {
                            double outlength;
                            if (out(temp)!=0){
                                outlength = out(temp);
                            }
                            if (out(temp)==0){
                                outlength = N-1;
                            }
                            rank += d * pr[i]/outlength;
                        }
                    }
                }
            }
            rank+=damping_value;
            diff+=fabs(rank-pr[id(tempnode)]);
            //printf("%d\n",id(tempnode));
            prev[id(tempnode)]=rank;
//            printf("%.7f\n",rank);
//            rank+=damping_value;
//            pr[id(tempnode)]=rank;
//            diff+=fabs(pr[id(tempnode)]-prev[id(tempnode)]);
//            if (diff>=diffPR && iteration<maxIterations)
//                break;
//            prev[id(tempnode)]=pr[id(tempnode)];
        }
        int j;
        for (j = 0; j <N ; ++j) {
            pr[j]=prev[j];
        }
    }
    double newpr[N];

    for (i = 0; i < N; ++i) {
        newpr[i]=pr[i];
    }
//    for (int i = 0; i < N; ++i) {
//        pr[i]=0;
//    }
//    quick_sort(newpr,0,N-1);
//    for(int i=N-1; i>=0; i--)
//        printf("%.7f\t", newpr[i]);
//    printf ("\n");

//    int idfind= maxID(urls,pr);
//    printf("%d\n",idfind);

    List order_list=orderList(urls,pr);
//    for (Node outputnode=first(order_list);outputnode; outputnode=next(outputnode)){
//        printf("%d\n",url(outputnode));
//        printf("%d\n",out(outputnode));
//    }

    FILE *outf=fopen("pagerankList.txt","w");
    Node outputnode;
    for (outputnode=first(order_list);outputnode; outputnode=next(outputnode)){
        fprintf(outf,"url%d, %d, %.7lf\n",url(outputnode),out(outputnode),newpr[id(outputnode)]);
    }
    fclose(outf);
    freeLL(urls);
    freeGraph(g);
    return 0;

}


int partition(double arr[], int low, int high){
    double key;
    key = arr[low];
    while(low<high){
        while(low <high && arr[high]>= key )
            high--;
        if(low<high)
            arr[low++] = arr[high];
        while( low<high && arr[low]<=key )
            low++;
        if(low<high)
            arr[high--] = arr[low];
    }
    arr[low] = key;
    return low;
}
void quick_sort(double arr[], int start, int end){
    int pos;
    if (start<end){
        pos = partition(arr, start, end);
        quick_sort(arr,start,pos-1);
        quick_sort(arr,pos+1,end);
    }
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readData.h"

int main(){
    List urls=getCollection();
    for (Node outputnode=first(urls);outputnode; outputnode=next(outputnode)){
        printf("%d, %d,\n",url(outputnode),id(outputnode));
        //int d=getNodeID(urls,11);
        //printf("%d\n",d);
    }
    //int d=getNodeID(urls,11);
    //printf("%d\n",d);
    Graph g=getGraph(urls);
    showGraph(g);
}
*/






















