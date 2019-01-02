#include <stdio.h>
#include <string.h>
#include "InvertedIdx.h"
#include "readdata2.h"

Tree fillTree(Tree tree, List urls);

int main(){
    List urls=get2Collection();
    Tree tree=newTree();
    tree=fillTree(tree,urls);
//    printInorder(tree);
    FILE *out=fopen("invertedIndex.txt","w");
    Treetofile(tree,out);
    fclose(out);
    free2LL(urls);
    freeTree(tree);

    return 0;
}

Tree fillTree(Tree tree, List urls){
    LNode tempnode;
    for (tempnode=first_node(urls);tempnode;tempnode=tempnode->next) {
        char filename[100];
        sprintf(filename,"%s.txt",url2(tempnode));
        FILE *web=fopen(filename,"r");
        int reading_flag=0;
        char word[100];
        while (fscanf(web,"%s",word)==1){
            if(strcmp(word,"Section-2")==0 && !reading_flag){
                reading_flag=1;
                continue;
            }
            else if (strcmp(word,"Section-2")==0 && reading_flag){
                break;
            }
            if (reading_flag && strcmp(word,"#end")!=0){
                adjust(word);
                if (strlen(word)<1)
                    continue;
                tree=TreeInsert(tree,word,url2(tempnode));
            }

        }
        fclose(web);
    }
    return tree;
}