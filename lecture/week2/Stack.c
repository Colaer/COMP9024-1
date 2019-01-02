// Stack ADO implementation ... COMP9024 17s2
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include <assert.h>

#define MAXITEMS 10

static struct StackObject {
    int item[MAXITEMS];
    int  top;
} stackObject;  // defines the Data Object

void StackInit() {         // set up empty stack
   stackObject.top = -1;
}

int StackIsEmpty() {       // check whether stack is empty
   return (stackObject.top < 0);
}

void StackPush(int ch) {  // insert char on top of stack
   assert(stackObject.top < MAXITEMS-1);
   stackObject.top++;
   int i = stackObject.top;
   stackObject.item[i] = ch;
}

int StackPop() {         // remove char from top of stack
   assert(stackObject.top > -1);
   int i = stackObject.top;
   int ch = stackObject.item[i];
   stackObject.top--;
   return ch;
}
//int main(){
//    int elements;
//    int temp;
//    printf("Enter a positive number: ");
//    scanf("%d",&elements);
//    for (int i = 0; i <3 ; ++i) {
//        printf("Enter a number: ");
//        scanf("%d",&temp);
//        StackPush(temp);
//    }
//    for (int j = 0; j < 3; ++j) {
//        printf("%d\n",StackPop());
//
//    }
//}
//int main(int argc, char *argv[] ){
//    int elements;
//    int temp;
//    printf("Enter a positive number: ");
//    scanf("%d",&elements);
//    for (int i = 0; i <3 ; ++i) {
//        printf("Enter a number: ");
//        scanf("%d",&temp);
//        StackPush(temp);
//    }
//    for (int j = 0; j < 3; ++j) {
//        printf("%d\n",StackPop());
//
//    }
//
//    for (int i = 1; i < argc; i++) {
//        StackPush(atoi(argv[i]));
//    }
//    for (int j = 1; j < argc; ++j) {
//        printf("%d\n",StackPop());
//    }
//}
int main(int argc, char *argv[]){
    int n;
    int temp=0;
    n=atoi(argv[1]);
    while(n>0){
        StackPush(n%2);
        n=n/2;
        temp++;
    }
    printf("Result: ");
    for (int i = 0; i <temp ; ++i) {
        printf("%d",StackPop());
    }
    printf("\n");

}