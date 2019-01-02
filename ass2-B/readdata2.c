//
// Created by apple on 2018/1/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readdata2.h"

//List getCollection(){
//    FILE *collection=fopen("collection.txt","r");
//    List urls=newList();
//    char word[100];
//    while(fscanf(collection,"%s",word)==1){
//        printf("%s ",word);
//        insertSetOrd(urls,word);
//    }
//    fclose(collection);
//    return urls;
//}

List get2Collection(){
    FILE *collection=fopen("collection.txt","r");
    List urls=new2List();
    char word[100];
    while(fscanf(collection,"%s",word)==1){
        insertSetOrd(urls,word);
    }
    fclose(collection);
    return urls;
}

void adjust(char *str){
    int first=0;
    int last=strlen(str)-1;
    while (isspace(str[first]))
        first++;
    while (isspace(str[last]))
        last--;
    if (str[last]==','){
        last--;
    }
    if (str[last]==';'){
        last--;
    }
    if(str[last]=='.'){
        last--;
    }
    if(str[last]=='?'){
        last--;
    }
    int i;
    for (i = first; i <=last ; i++) {
        str[i]=tolower(str[i]);
    }
    str[i]='\0';
}