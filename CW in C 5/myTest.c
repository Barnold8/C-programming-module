/* This file is for me to test functions and algorithms */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "rpn.h"
#include "sort.h"
#include "stack.h"


int nothing(void* x,void*y){ /* Test function to compare ints, this is so I can test my sorting algo */

    if(x == y ){return 0;}
    if(x > y){return 1;}
    if(x < y ){return -1;}
    return 0;
}


int main(int argc,char ** argv){

    LinkedList* T = initialise_linked_list(); /* CHECK BACK HERE. TEST FOR EMPTY AND NULL LISTS. ALSO CHECK THE COMPARE FUNCTION IN NOTES IN SORT.C */

    int a[10] = {1,9,5,7,3,5,42,3,2,1};
    int i;
    for(i = 0; i < 10; i++){

        append_linked_list(T,&a[i]);

    }
    insertion_sort(T,&nothing);

    print_linked_list(T,print_int);

    free_linked_list(T);

    printf("Hello world!\n");

    return 0;

}