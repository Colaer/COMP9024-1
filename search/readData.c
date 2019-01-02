// Written by Jack Gardner

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"

#define strEQ(g, t) (strcmp((g),(t)) == 0)

List getCollection() {

    FILE *collection = fopen("./collection.txt", "r");
    if (!collection) { perror("collection.txt"); }

    // Read all urls from collection.txt and make list
    List urls = newList();
    char line[BUFSIZ];
    while (fscanf(collection, "%s", line) == 1)
        enterList(urls, line, NEW_ID);

    fclose(collection);

    return urls;
}

Graph getGraph(List urls) {

    Graph urlGraph = newGraph(nNodes(urls));

    for_node_in(urls) {

        char filename[BUFSIZ];
        sprintf(filename, "./%s.txt", url(node));
        FILE *page = fopen(filename, "r");
        if (!page) { perror(filename); }

        char line[BUFSIZ];
        while (fscanf(page, "%s", line) == 1) {
            if (strEQ(line, "#start") || strEQ(line, "Section-1")) continue;
            if (strEQ(line, "#end")) break;
            addEdge(urlGraph, url(node), line);
        }

        fclose(page);

    }
    return urlGraph;
}

// Determine if a term appears in a file
double appears(char *term, char *filename) {

    char fname[BUFSIZ];
    sprintf(fname, "./%s.txt", filename);
    FILE *f = fopen(fname, "r");
    if (!f) { perror(filename); }

    normalise(term);
    char word[BUFSIZ];
    bool start_reading = false;
    while (fscanf(f, "%s", word) == 1) {

        // Start reading words in section 2 of the file
        if (strEQ(word, "Section-2") && !start_reading) {
            start_reading = true; continue;
        } else if (strEQ(word, "#end") && start_reading) {
            break;
        }
        // if the word is found, close file and return 1
        if (start_reading)
            normalise(word);
            if (strEQ(term, word)) {
                fclose(f);
                return 1;
            }
    }

    fclose(f);

    return 0;
}

// Return 'search results' from inverted index
void results(char *term, List urls, double termsFound[]) {

    FILE *index = fopen("./invertedIndex.txt", "r");
    if (!index) { perror("invertedIndex.txt"); }

    normalise(term);
    char line[BUFSIZ];
    // Read in each line
    while (fgets(line, BUFSIZ, index) != NULL) {

        char *line_search = line, word[BUFSIZ];
        int letters;
        // Determine if line starts with the search term
        sscanf(line_search, "%s%n", word, &letters);
        line_search += letters;

        if (!strEQ(word, term)) continue;

        // If it does, then fill list with the urls it appears in
        while (sscanf(line_search, "%s%n", word, &letters) == 1) {
            line_search += letters;
            normalise(word);
            enterList(urls, word, NEW_ID);
            // Increment search terms found
            termsFound[getNodeID(urls, word)]++;
        }

    }

    fclose(index);
}

void normalise(char *str) {
    int first = 0, last = strlen(str)-1;
    // Removed trailing and leading space
    while (isspace(str[first])) first++;
    while (isspace(str[last])) last--;
    // Remove required trailing punctuation
    switch (str[last]) {
        case ',':
        case ';':
        case '.':
        case '?':
            last--; break;
    }
    // Convert to lowercase
    int i;
    for (i = first; i <= last; i++) str[i] = tolower(str[i]);
    str[i] = '\0';
}
