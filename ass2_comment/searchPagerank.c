

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int number_of_urls();   //get the number of urls
void geturls(char **links); //get the specific contents eg urlxx


int main(int argc, char *argv[])
{
    int elements = number_of_urls();    //count the number of urls from "pagerankList.txt
    int i, j, args = argc -1;   //args represents the number of command arguments

    char **links = malloc(sizeof(char *) * elements);   //allocate memory dynamically
    for(i = 0; i < elements; i++)
        links[i] = malloc(sizeof(char) * 20);   //assume the max length of url less than 20
    for(i = 0; i< elements; i++)
        for(j = 0; j < 20; j++)
            links[i][j] = '\0';     //fill '\0' to every links[i] (url)
    geturls(links); //get every url from "pagerankList.txt

    char words[argc-1][30]; //declare string array and the max length of word less than 30
    for(i = 0; i < args; i++){  //the number of command arguments loops
        strcpy(words[i],argv[i+1]); //copy  string argv[i+1] to words[i]
        strcat(words[i], " "); //append a copy of the source string to the end of destination string
    }

    FILE *word_urls = fopen("invertedIndex.txt", "r"); //open the file invertedIndex.txt
    char temp_words[200];
    char match_lines[args][100];
    while(fgets(temp_words, 200, word_urls) != NULL)//It reads a line from the word_urls and stores it into temp_words by str
        for(i = 0; i < args; i++)
            if(!strncmp(words[i], temp_words, strlen(words[i]))){   //compare no more than the length of word[i] between words[i] and temp_words
                strcpy(match_lines[i],temp_words);  //if success, find the specific line from invertedIndex.txt and copy the temp_words to match_lines
            }

    int dic_urls[elements];    //initialise array which contains the number of urls elements
    for(i = 0; i < elements; i++)
        dic_urls[i] = 0;
    //finds the first occurrence of the sub-string lins[j] in the string mathc_lines[i]
    for(i = 0; i < args; i++){  // the number of command arguments loops
        for(j = 0; j < elements; j++){  //traverse all urls
            if(strstr(match_lines[i], links[j]) != NULL){   //find the word line which match specific url
                dic_urls[j]++;  //find the url, url++
            }
        }
    }

    int k,l;
    if (elements<=30) {
        for (l = args; l > 0; l--) {  // the number of command arguments loops in descending order
            for (k = 0; k < elements; ++k) { //traverse every url
                if (dic_urls[k] == l) {    //the number of match for url
                    printf("%s\n", links[k]); //print the url
                }
            }
        }
    }
    fclose(word_urls); //close the file
    return 0;

}

//count the number of url from pagerankList.txt
int number_of_urls(void)
{
    FILE *page = fopen("pagerankList.txt", "r");    //open the file
    char temp_store[200];
    int elements = 0;   //line =0
    while(fgets(temp_store,200, page) != NULL){ //read by line
        elements+=1;    //line +1
    }
    fclose(page);   //close the file

    return elements;
}

//get every urlxx from pagerankList.txt
void geturls(char *links[])
{
    FILE *furls = fopen("pagerankList.txt", "r");//open the file
    char temp_storeg[200];
    int i,j;
    for(i = 0; fgets(temp_storeg,200, furls) != NULL; ++i){ //read by line
        for(j = 0; temp_storeg[j] != ','; ++j) {    //contents separated by ','
            links[i][j] = temp_storeg[j];   //string array links = urlxx
        }
    }
    fclose(furls); //close the file
}
