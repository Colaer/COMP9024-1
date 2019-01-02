//
// Created by apple on 2018/1/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readdata2.h"


//Create a set (list) of urls to process by reading	data from file "collection.txt"
List get2Collection(){
    FILE *collection=fopen("collection.txt","r");//open the file
    List urls=new2List();   // create new List
    char word[100];
    while(fscanf(collection,"%s",word)==1){ // read data from file "collection.txt"
        insertSetOrd(urls,word);    //insert word to urls by order
    }
    fclose(collection); //close the file
    return urls;
}

//normalise the word
void adjust(char *str){
    int first=0;
    int last=strlen(str)-1; //  0...N-1 in string array
    while (isspace(str[first])) //check if begin of the string is space
        first++;
    while (isspace(str[last]))  //check if end of the string is space
        last--;
    if (str[last]==','){    //check ','
        last--;
    }
    if (str[last]==';'){    //check ';'
        last--;
    }
    if(str[last]=='.'){     //check '.'
        last--;
    }
    if(str[last]=='?'){     //check '?'
        last--;
    }
    int i;
    //converting all characters to lowercase
    for (i = first; i <=last ; i++) {
        str[i]=tolower(str[i]);
    }
    str[i]='\0'; //'\0' represents end
}