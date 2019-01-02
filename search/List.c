// list.c ... simple List of Strings
// Adapted from queue code provided in lab
// Written by Jack Gardner and Zhenhao Chen

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "List.h"

#define strEQ(g, t) (strcmp((g),(t)) == 0)

struct _node {
    char *url;
    int id;
    Node next;
};

struct _ListRep {
    int n;
    Node head, tail;
};

extern char *strdup(const char *s);
static Node newNode(char *, int);
static void disposeNode(Node);
static void sortedInsert(List, Node, double cmp[], int order);

List newList() {
    List new = malloc(sizeof(struct _ListRep));
    assert(new != NULL);
    new->head = NULL;
    new->tail = NULL;
    new->n = 0;
    return new;
}

void disposeList(List L) {
    if (L == NULL) return;
    Node next, curr = L->head;
    while (curr != NULL) {
        next = curr->next;
        disposeNode(curr);
        curr = next;
    }
    free(L);
}

void enterList(List L, char *str, int ID) {
    if (getNodeID(L, str) != -1) return;
    if (L->head == NULL) {
        Node new = newNode(str, ID == -1 ? 0 : ID);
        L->head = L->tail = new;
    } else {
        Node new = newNode(str, ID == -1 ? L->tail->id + 1 : ID);
        L->tail->next = new;
        L->tail = new;
    }
    L->n++;
}

static int greater(double a, double b) { return a >= b ? 1 : 0; }
static int smaller(double a, double b) { return a <= b ? 1 : 0; }

static void sortedInsert(List L, Node toInsert, double cmp[], int order) {
    int (* first)(double, double);
    int (* second)(double, double);
    switch (order) {
        case ASCENDING:
            first = greater; second = smaller;
            break;
        case DESCENDING:
            first = smaller; second = greater;
            break;
    }
    Node N = newNode(toInsert->url, toInsert->id);
    if (L->head == NULL) L->head = L->tail = N;
    else if (first(cmp[L->head->id], cmp[N->id])) {
        N->next = L->head;
        L->head = N;
    } else if (second(cmp[L->tail->id], cmp[N->id])) {
        L->tail->next = N;
        L->tail = N;
    } else {
        Node temp = L->head;
        while (temp->next) {
            if (first(cmp[temp->next->id], cmp[N->id])) break;
            temp = temp->next;
        }
        N->next = temp->next;
        temp->next = N;
    }
    L->n++;
}

List orderList(List urls, double cmp[], int order) {
    List ordered_urls = newList();
    for (Node temp = urls->head; temp; temp = temp->next)
        sortedInsert(ordered_urls, temp, cmp, order);
    disposeList(urls);
    return ordered_urls;
}

int getNodeID(List L, char *str) {
    for (Node temp = L->head; temp; temp = temp->next)
        if (strEQ(temp->url, str)) return temp->id;
    return -1;
}

static Node newNode(char *str, int ID) {
    Node new = malloc(sizeof(struct _node));
    assert(new != NULL);
    new->url = strdup(str);
    new->id = ID;
    new->next = NULL;
    return new;
}

static void disposeNode(Node curr) {
    assert(curr != NULL);
    free(curr->url);
    free(curr);
}

Node head(List L) { return L->head; }
Node next(Node N) { return N->next; }
char *url(Node N) { return N->url; }
int id(Node N) { return N->id; }
int nNodes(List L) { return L->n; }
