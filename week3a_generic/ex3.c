#include <stdio.h>
#include <string.h>

// generic min function
void * min(void *element1, void *element2, int (*compare)(void *, void *)) {
    if (compare(element1, element2) < 0)
       return element1;
    else
       return element2;
}


int intCompare( void *item1, void *item2 ) {
    int val1 = * ( (int *)item1 ) ;
    int val2 = * ( (int *)item2 ) ;

    return val1 - val2;
}


// stringCompare downcasts its void * arguments to char * and then passes
// them to strcmp for comparison
int stringCompare(void *item1, void *item2) {
    
    char *s1 = (char *)item1;
    char *s2 = (char *)item2;

    return strcmp( s1, s2);
}


int main(int argc, char *argv[]) {
  
    char *s1 = "Sydney"; 
    char *s2 = "New Your"; 

    char *minString = (char *) min(s1, s2, stringCompare); 
    printf("min string = %s\n", minString);

    // -----------------------------------

    int val1 = 55;
    int val2 = 34;

    int *minInt = (int *) min(&val1, &val2, intCompare);
    printf("min int = %d\n", *minInt);

    return 0;
}

