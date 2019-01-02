#include <stdio.h>
#include <string.h>
#include "InvertedIdx.h"
#include "readdata2.h"

Tree wordfillTree(Tree tree, List urls);

int main(){
    List urls=get2Collection(); //create a linked list and read data from collection.txt
    Tree tree=newTree();    //create a new tree
    tree=wordfillTree(tree,urls);   //read word from section-2 and fill these words to a new tree
//    printInorder(tree);
    FILE *out=fopen("invertedIndex.txt","w");   //create a new file named invertedIndex.txt
    Treetofile(tree,out);   //print the contents of tree to .txt file
    fclose(out);    //close the file
    free2LL(urls);  //free the memory associated with List urls
    freeTree(tree); //deallocates the memory associated with Tree tree

    return 0;
}

//read word from section-2 and fill these words to a new tree
//strcmo() takes two strings as arguments and compare these two strings lexicographically
Tree wordfillTree(Tree tree, List urls){
    LNode tempnode;//loop for every urlxx from List urls
    for (tempnode=first_node(urls);tempnode;tempnode=tempnode->next) {
        char filename[100];//url2(x) get the specific value of x
        sprintf(filename,"%s.txt",url2(tempnode));//sends formatted output to a string pointed to filename.
        FILE *web=fopen(filename,"r");  //open the urlxx.txt
        int reading_flag=0;//set the reading flag in order to read words from section-2
        char word[100];
        while (fscanf(web,"%s",word)==1){   //reads word from web(urlxx.txt)
            if(strcmp(word,"Section-2")==0 && !reading_flag){   //if word == "Section-2" and reading_flag ==0, continue
                reading_flag=1; //setting reading_flag equals 1
                continue;
            }
            else if (strcmp(word,"Section-2")==0 && reading_flag){  //if word == "Section-2" and reading_flag !=0, break
                break;
            }
            if (reading_flag && strcmp(word,"#end")!=0){    //if reading flag is 1 and word != "#end",start reading word
                adjust(word);   //normalise words by removing leading ,trailing spaces and punctuation marks, and converting all characters to lowercase
                if (strlen(word)<1) //check if length of word <1
                    continue;
                tree=TreeInsert(tree,word,url2(tempnode));  //insert word and its url to tree
            }

        }
        fclose(web);    //close the file web
    }
    return tree;
}