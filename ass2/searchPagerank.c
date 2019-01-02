
//#include <string.h>
//
//int main(int argc, char *argv[]) {
////    for (int i = 1; i <argc ; ++i) {
////        printf("%s\n",argv[i]);
////    }
//    FILE *pageranklist=fopen("pagerankList.txt","r");
//    char word[100];
//    while (fscanf(pageranklist,"%[^\n]",word)==1){
//        printf("%s\n",word);
//        if (strcmp(word,"\n")==0){
//            break;
//        }
//    }
//    return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int number_of_urls();
void geturls(char **links);


int main(int argc, char *argv[])
{
    int elements = number_of_urls();
    int i, j, args = argc -1;

    char **links = malloc(sizeof(char *) * elements);
    for(i = 0; i < elements; i++)
        links[i] = malloc(sizeof(char) * 30);
    for(i = 0; i< elements; i++)
        for(j = 0; j < 30; j++)
            links[i][j] = '\0';
    geturls(links);

    char words[argc-1][20];
    for(i = 0; i < args; i++){
        strcpy(words[i],argv[i+1]);
        strcat(words[i], " ");
    }

    FILE *word_urls = fopen("invertedIndex.txt", "r");
    char temp_words[200];
    char match_lines[args][100];
    while(fgets(temp_words, 200, word_urls) != NULL)
        for(i = 0; i < args; i++)
            if(!strncmp(words[i], temp_words, strlen(words[i]))){
                strcpy(match_lines[i],temp_words);
            }

    int dic_urls[elements];
    for(i = 0; i < elements; i++)
        dic_urls[i] = 0;

    for(i = 0; i < args; i++){
        for(j = 0; j < elements; j++){
            if(strstr(match_lines[i], links[j]) != NULL){
                dic_urls[j]++;
            }
        }
    }

//    for(i = 0; i < elements; i++) {
//        if (dic_urls[i] == args) {
//            printf("%s\n", links[i]);
//        }
//    }
    int k,l;
    /*
    for (k = 0; k < elements; ++k) {
        for (l = args; l >0 ; l--) {
            if (dic_urls[k]==l){
                printf("%s\n",links[k]);
            }
        }
    }
    */
    for (l = args; l >0 ; l--){
    		for (k = 0; k < elements; ++k){
    			if (dic_urls[k]==l){
                printf("%s\n",links[k]);
            }
    		}
    }
    fclose(word_urls);
    return 0;

}

int number_of_urls(void)
{
    FILE *page = fopen("pagerankList.txt", "r");
    char temp_store[200];
    int elements = 0;
    while(fgets(temp_store,200, page) != NULL){
        elements+=1;
    }
    fclose(page);

    return elements;
}

void geturls(char *links[])
{
    FILE *furls = fopen("pagerankList.txt", "r");
    char temp_storeg[200];
    int i,j;
    for(i = 0; fgets(temp_storeg,200, furls) != NULL; ++i){
        for(j = 0; temp_storeg[j] != ','; ++j) {
            links[i][j] = temp_storeg[j];
        }
    }
    fclose(furls);
}
