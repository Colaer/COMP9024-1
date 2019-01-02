// getPeaks.c 
// Written by Ashesh Mahidadia, December 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();
	//assert(peaksL!=NULL);
	DLListNodeP cur;
	cur=L->first;
	while(cur->next->next !=NULL){
		DLListNodeP temp;
		temp=cur->next;
		if(temp->value > cur->value && temp->value > temp->next->value){
			if (peaksL->first==NULL && peaksL->last==NULL){
				peaksL->first=peaksL->curr=peaksL->last=temp;			
			}
			else if(peaksL->first==peaksL->last){
				temp->prev=peaksL->last;
				peaksL->last->next=temp;
				peaksL->curr=peaksL->last;
				/*peaksL->first->next=temp;
				peaksL->last=temp;
				peaksL->curr=temp;
				peaksL->curr->prev=peaksL->first;
				peaksL->nitems++;*/
			}
			else{
				temp->prev=peaksL->curr;
				temp->next=peaksL->curr->next;
				peaksL->curr->next->prev=temp;
				peaksL->curr->next=temp;
				/*DLListNodeP temp3node;
				temp3node=peaksL->curr;
				peaksL->curr=temp;
				temp3node->next=peaksL->curr;
				peaksL->curr->prev=temp3node;
				peaksL->last=temp;
				peaksL->nitems++;*/			
			}
			peaksL->curr=temp;
			peaksL->nitems++;		
		}
	}
	cur=cur->next;
	// your solution here ... 

	return peaksL;
}


