#include "sort.h"
#include "stack.h"
#include "string.h"
#include <stdio.h>

/* sort linked list *list using merge insertion sort. */
/* upon success, the elements in *list will be sorted. */
/* return silently if *list is uninitialised or empty. */
/* the compare argument is a pointer to a function which returns */
/* less than 0, 0, or greater than 0 if first argument is */
/* less than, equal to, or greater than second argument respectively. */


/* | < 0 = -1 | | == 0 = 0 | | > 0 = 1 | */


int getListLen(LinkedList* L){

    Node * x = L->head;
    int y = 0;
    while(x){

      x = x->next;
      y++;

    }
    return y;
}

void Swap(Node* A, Node* B){

  void * Ab, *Bb;

  Ab = A->data;
  Bb = B->data;

  A->data = Bb;
  B->data = Ab;
}

void insertion_sort(LinkedList *list, int (*compare)(void *, void *)) 
{

    Node* PTR;      /* this looks at the elements in A */
    Node* PTR_B;      /* This looks at the elements in B */                                               
    Node* Node_B;    /* This is to get to the end of B */                  
    LinkedList* List_B = initialise_linked_list(); /* The sorted list */
    PTR = list->head->next;                        /* Point to the head of next part of the list after head */
    append_linked_list(List_B,list->head->data);  /* Add the head of the unsorted list to the head of the sorted list */

    remove_head_linked_list(list);                /* Remove head of unsorted list */
    Node_B = List_B->head;                        /* Point to the head of the sorted list */
    
    while(PTR != NULL){ /* Go through all unsorted elements, as if we were popping them */

      append_linked_list(List_B,PTR->data);
    
      while(Node_B->next != NULL){ /* Make Node_B the end of the sorted list */
        Node_B = Node_B->next;
      }

      PTR_B = Node_B;             /* Have a pointer start at the end, thanks to Node_B */
      
      while(PTR_B->prev != NULL){

        if(strcmp(PTR_B->prev->data,PTR_B->data) >= 0){
        
            Swap(PTR_B->prev,PTR_B);

        }
        PTR_B = PTR_B->prev;
      }

      PTR = PTR->next;
   
    }

    list->head = List_B->head;    
    PTR_B = List_B->head;
    free(List_B);                 /* Possible mem loss here */

                                    
}

Node ** splitList(LinkedList * L){

  int len = getListLen(L);
  int count = 0;
  Node ** arr = (Node**) malloc(sizeof(Node*)*len);
  Node * PTR = L->head;

  while(count != len){ /* Emulate splitting all elements into their own list (sorted one elem list) */
      
      
      arr[count] = PTR;
      PTR = PTR->next;
      count++;
  }

  return arr;

}

void printNodeArr(Node** arr, int len){
  int i;
  for(i = 0; i < len; i++){

    print_string(arr[i]->data);
    printf("--------------------\n");
  }
  
}

void merge(LinkedList * Original, LinkedList* L, LinkedList* R, int(*compare)(void*,void*)){

    Node * L_PTR = L->head;
    Node * R_PTR = R->head;
    Node * O_PTR = Original->head;


    while(L_PTR && R_PTR){ /* Go through both lists and add the lower value to the sorted list */

      if((*compare)(L_PTR->data,R_PTR->data) < 0){

        O_PTR->data = L_PTR->data;
        O_PTR = O_PTR->next;
        L_PTR = L_PTR->next;

      }
      else{

        O_PTR->data = R_PTR->data;
        O_PTR = O_PTR->next;
        R_PTR = R_PTR->next;

      }
    }

    /* if any data is left over in one of the lists, just add the rest on to the now sorted list */
    while (L_PTR)
    {
      O_PTR->data = L_PTR->data;
      O_PTR = O_PTR->next;
      L_PTR = L_PTR->next;
    }
    while (R_PTR)
    {
      O_PTR->data = R_PTR->data;
      O_PTR = O_PTR->next;
      R_PTR = R_PTR->next;
    }
    

}

void actual_merge_sort(LinkedList *list, int (*compare)(void *, void *),LinkedList * Heads){

    /* Make two arrays of L side and R side where L side is one half of the original array and R is the rest */
    int ListSize = getListLen(list);
    int listMid = ListSize/2;
    int i;
    Node * PTR = list->head;
    LinkedList * LSide = initialise_linked_list();
    LinkedList * RSide = initialise_linked_list();

    if(getListLen(list) < 2){ /* if list is empty or has 1 elem, its already sorted */
      return;
    }

    /* Populate left side */
    for(i = 0; i < listMid; i++){
      append_linked_list(LSide, PTR->data);
      PTR = PTR->next;
    }
    /* Populate right side */
    for(i = listMid; i < ListSize; i++){
      append_linked_list(RSide, PTR->data);
      PTR = PTR->next;
    }

    merge_sort(LSide,compare);
    merge_sort(RSide,compare);
  
    merge(list,LSide,RSide,compare);

    free_linked_list(LSide);
    free_linked_list(RSide);

}

void merge_sort(LinkedList *list, int (*compare)(void *, void *))         
{
    /* LinkedList* HeadList = initialise_linked_list();
    Node* PTR = HeadList->head; */

    actual_merge_sort(list,compare,NULL);;

    /*
    while(PTR){

      PTR = PTR->next;
      free_node(PTR);
    }
    free(HeadList);
    */

    
}









/* Code graveyard yet again

   int i,j,LeftLen,RightLen;
    Node ** SplitList;
    Node ** LSide;
    Node ** RSide;
    LeftLen = getListLen(list)/2;
    RightLen = getListLen(list) - (getListLen(list)/2);
    SplitList = splitList(list); 
    LSide = (Node**) malloc(sizeof(Node *)*LeftLen);
    RSide = (Node**) malloc(sizeof(Node *)*RightLen);

    if(getListLen(list) < 2){

      return;

    }
    for(i = 0; i < getListLen(list)/2 ; i++){
       LSide[i] = SplitList[i];
    }
    j = 0;
    for(i = getListLen(list)/2 ; i < getListLen(list) ; i++){       
      RSide[j] = SplitList[i];
      j++;
    }
     


    merge_sort(LSide,*compare);
    merge_sort(RSide,*compare);

    free(SplitList);

    */
/* Returns the current linked list as an array of node* so its like splitting them up into each elem *//* Need to add the n element (last elem) to a seperate var to sort down at the end of the merge */