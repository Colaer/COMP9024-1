// Written by Jack Gardner

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "readData.h"

// Used for in and out links for urls
#define IN  0
#define OUT 1

void  calculatePageRank(List, Graph, double d, double diffPR,
                        int maxIterations, double PR[], int N,
                        double weightedIn[N][N], double weightedOut[N][N]);
double calculateWeightedValue(Graph, int v, int w, double Links[]);

// UTILITY FUNCTIONS
static double innerSum(Graph, List, char *link, double prevPR[], int N,
                       double weightedIn[N][N], double weightedOut[N][N]);
static double links(Graph, int v, int io);

int main(int argc, char *argv[]) {

    double d, diffPR;
    int maxIterations;
//    if (argc != 4) {
//        printf("Usage: ./pagerank <damping factor> <PageRank sum difference> <max iterations>\n");
//        return EXIT_FAILURE;
//    }
//    sscanf(argv[1], "%lf", &d);
//    sscanf(argv[2], "%lf", &diffPR);
//    maxIterations = atoi(argv[3]);
    d=0.85;
    diffPR=0.00001;
    maxIterations=1000;
    List urls = getCollection();
    Graph g = getGraph(urls);

    int N = nVertices(g);

    // In and out links + weighted in and out values of each url are constant
    double weightedIn[N][N];
    double weightedOut[N][N];
    double inLinks[N];
    double outLinks[N];

    // Initialise those values for all urls
    for (int i = 0; i < N; i++) {
        inLinks[i] = links(g, i, IN);
        outLinks[i] = links(g, i, OUT);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                weightedIn[i][j] = calculateWeightedValue(g, i, j, inLinks);
                weightedOut[i][j] = calculateWeightedValue(g, i, j, outLinks);
            } else {
                weightedIn[i][j] = weightedOut[i][j] = 0;
            }
        }
    }

    // Fill pagerank array for urls
    // Indexes of array are IDs of url nodes
    double PR[N];
    calculatePageRank(urls, g, d, diffPR, maxIterations, PR, N, weightedIn, weightedOut);

    // Order list in descending order of pageranks
    // Creates new list and frees old one
    List ordered_urls = orderList(urls, PR, DESCENDING);
    FILE *out = fopen("./pagerankList.txt", "w");
    for_node_in(ordered_urls)
        fprintf(out, "%s, %d, %.7f\n", url(node), findDegree(url(node), g), PR[id(node)]);
    fclose(out);

    // Free everything
    disposeList(ordered_urls); disposeGraph(g);

    return EXIT_SUCCESS;
}

void calculatePageRank(List L, Graph g, double d, double diffPR,
                              int maxIterations, double PR[], int N,
                              double weightedIn[N][N], double weightedOut[N][N]) {

    // Double version of N for calculations requiring it
    double dN = (double) N;
    double prevPR[N];

    // Initialise pageranks as 1 / N
    for_node_in(L)
        PR[id(node)] = prevPR[id(node)] = 1 / dN;

    int iteration = 0;
    double diff = diffPR;

    while (iteration < maxIterations && diff >= diffPR) {
        iteration++;
        diff = 0;

        // Calculate pagerank
        for_node_in(L) {
            double sum = innerSum(g, L, url(node), prevPR, N, weightedIn, weightedOut);
            PR[id(node)] = (1 - d) / dN + (d * sum);
            diff += fabs(PR[id(node)] - prevPR[id(node)]);
        }

        // Set new values for previous pageranks
        for_node_in(L)
            prevPR[id(node)] = PR[id(node)];
    }

}

double calculateWeightedValue(Graph g, int v, int w, double Links[]) {
    double denominator = 0;
    int N = nVertices(g);
    for (int i = 0; i < N; i++)
        if (edge(g, v, i))
            denominator += Links[i];
    return Links[w]/denominator;
}

static double innerSum(Graph g, List pages, char *link, double prevPR[], int N,
                       double weightedIn[N][N], double weightedOut[N][N]) {
    double sum = 0;
    int x = vertexID(link, g, N);
    for (int y = 0; y < N; y++)
        if (edge(g, y, x))
            sum += prevPR[getNodeID(pages, vertex(g, y))] * weightedIn[y][x] * weightedOut[y][x];
    return sum;
}

/* --- MATRIX ---
 * Iterate through:
 * x values for outgoing
 * y values for incoming
 */

static double links(Graph g, int v, int io) {
    double links = 0;
    int N = nVertices(g);
    for (int j = 0; j < N; j++)
        links += (io == IN) ? edge(g, j, v) : edge(g, v, j);
    return (links == 0) ? 0.5 : links;
}
