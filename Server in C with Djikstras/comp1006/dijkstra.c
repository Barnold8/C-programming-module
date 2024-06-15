/*
 *  dijkstra.c
 *  ProgrammingPortfolio
 *
 *  Created by Steven Bagley on 08/12/2021.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "graph.h"
#include "dijkstra.h"

/* 
S = All vertices apart from the source
R = Next hops from source to each vertex
D = Weights of traversing the path from source to each vertex 
*/

Vertex* getVertex(Graph* G,const int ID){ /* Grabs vertex from graph linked list */

    Node* N;
    Vertex* V;
    if(!G || !G->head){
        fprintf(stderr,"error: cant get vertex from NULL graph\n");
        return NULL;
    }
    N = G->head;

    while(N){

        V = N->data;

        if(V->id == ID){
            return V;
        }

        N = N->next;

    }
    return NULL;
}

int countNodes(Graph* G){

    Node * S;
    int count = 0;
    S = G->head;
    while(S){

        S = S->next;
        count++;

    }
    return count;
}

Node ** allocTable(const int count){

    Node** S;

    if(!(S = (Node**)malloc(count*sizeof(Node*)))){
        fprintf(stderr,"error: an error has occured while allocating memory in the allocTable function\n");
        return NULL;
    }
    else{return S;}
}

int* allocIDTable(const int count){

    int* arr;
    if(!(arr = (int*)malloc(count*sizeof(int)))){

        fprintf(stderr,"error: an error has occured while allocating memory in the allocIDTable function\n");
        return NULL;

    }else{return arr;}
}

Node** Gen_S_Table(Graph* G, const int avoid){ /* Place all networks in an array of type Node*. Include avoid network so it can be included in other functions */

    Node** S;
    Node * N;
    Vertex * V;
    int x;
    x = 0;

    if(G && G->head){
        S = allocTable(countNodes(G)-1);
        N = G->head;
        while (N)
        {
            V = N->data;
            if(V->id != avoid){ 
                S[x] = N;
                x++;
                
             } 
      
            N = N->next;
           
        }
        
    }
    else{
        fprintf(stderr, "error: cant work on null graph or graph with no nodes in function GenTable\n");
        return NULL;
    }
    return S;
}

int* Gen_R_Table(Graph*G, const int avoid, int*length){

/* return array of vertex ID's. */
/* Make array of where the network points to */
/* Go through the entire network graph, if the current network points to that network in S, then add it to new array as is, if not, append a 0 */
/* Dont include current network as valid network, make that 0 */

    int*arr,w;
    int arrLength,i,count,count2,yesFlag;
    Node * N;
    Edge** E;
    Vertex *V;
    count2 = 0;

    if(!G || !G->head){
        fprintf(stderr, "error, cannot generate D table from NULL graph");
        return NULL;
    }
    arrLength = countNodes(G);

    if(!(arr = (int*)malloc(arrLength*sizeof(int)))){
        fprintf(stderr, "error: trouble allocating mem in Gen_D_Table function\n");
        return NULL;
    }

    *length = arrLength;

    N = G->head;
    V = getVertex(G,avoid);
    E = get_edges(G,V,&count);

    while(N){
        V = N->data;
        for(i = 0; i < count; i++){

            if(V->id == edge_destination(E[i])){
                yesFlag = 1; /* used to see if the current network node is being pointed to by the source node */
                w = V->id;
            }

        }

        if(yesFlag){arr[count2] = w;}
        else{arr[count2] = -1;}
        
        count2++;
        yesFlag = 0;
        N = N->next;

    }

    return arr;
   

}

double* Gen_D_Table(Graph*G, const int avoid, int*length){  /*get all edge weights of current vertex, if the edge points to NULL then its weight is INF(DBL_MAX )*/

    double*arr,w;
    int arrLength,i,count,count2,yesFlag;
    Node * N;
    Edge** E;
    Vertex *V;
    count2 = 0;

    if(!G || !G->head){
        fprintf(stderr, "error, cannot generate D table from NULL graph");
        return NULL;
    }
    arrLength = countNodes(G);

    if(!(arr = (double*)malloc(arrLength*sizeof(double)))){
        fprintf(stderr, "error: trouble allocating mem in Gen_D_Table function\n");
        return NULL;
    }

    *length = arrLength;

    N = G->head;
    V = getVertex(G,avoid);
    E = get_edges(G,V,&count);

    while(N){
        V = N->data;
        for(i = 0; i < count; i++){

            if(V->id == edge_destination(E[i])){
                yesFlag = 1; /* used to see if the current network node is being pointed to by the source node */
                w = E[i]->weight;
            }

        }

        if(yesFlag){arr[count2] = w;}
        else{arr[count2] = DBL_MAX;}
        
        count2++;
        yesFlag = 0;
        N = N->next;

    }

    return arr;

}

int* generateIGNORE(const int length){
    
    /* How to take an element out of S */
    /* if the index in ignore is 1, ignore that S thats in the same index, else dont ignore. */

    int* ignore_LIST;
    int i;

    if(!(ignore_LIST = (int*)malloc(length*sizeof(int)))){
        fprintf(stderr, "error: unable to allocate array for ignorable elems. Add at least 1MB of RAM im begging you....\n");
        return NULL;
    }

    for(i = 0; i < length; i++){

        ignore_LIST[i] = -1; /* -1 being default value as its not a valid index */

    }

    return ignore_LIST;
}

int errorCheck(Graph* G, const int id){

    Vertex *V;

    if(!G||!G->head){

        fprintf(stderr,"error: graph parsed into function was type NULL\n");
        return 1;

    }
    if(!(V = getVertex(G,id))){
        fprintf(stderr,"error: couldnt find source network with id %d\n",id);
        return 1;
    }

    return 0;

}

void addIgnore(int* arr, const int IGNORE,const int length){


    if(IGNORE > length){
        fprintf(stderr, "error: cannot ignore value out of S table index. Index given %d\n",IGNORE);
        return;
    }else if(arr[IGNORE] == 1){
        fprintf(stderr,"error: cannot ignore already ignored value\n");
        return;
    }else{
        arr[IGNORE] = 1;
    }

}

int findShortest(double* D,const int len,double* cost,int*IGNORE){ /* Need to add ignore into this somehow so we can change the network node at the start */

    double start_VAL;
    int i, result;
    
    /* find first available value in table */
    for (i = 0; i < len-1; i++){
    
        if(IGNORE[i] != 1){
            start_VAL = D[i];
            result = i;
            *cost = D[i];
            
            break;
        }
    }

    for(i = 0; i < len-1; i++){
        
        if(IGNORE[i] != 1 && start_VAL > D[i]){
            result  = i;
            *cost = D[i];
        }

    }

 /*    printf("weight index chosen %d.\tWeight %f\n",result,D[result]); */
    addIgnore(IGNORE,result,len);    

    return result;
   
}

int getIndex(Node**S ,int S_Len,const int ID){

    int i,x;
    Vertex*V;
    x = -1;

    

    for(i = 0; i < S_Len -1; i++){

        V =  S[i]->data;
        if(V->id == ID){
            x = i;
        }

    }
    return x+1;
}

int isInSet(int* IGNORE, const int ID){

    /* 1 = in set | 0 = not in set */
    /*  printf("--%d--\n",IGNORE[ID]); */
    if(IGNORE[ID] == 0){
        return 1;
    }
    return IGNORE[ID];
}

int NULL_S(int* IGNORELIST, const int length){ /* Checks the IGNORE list to see if all values are being ignored, if thats the case, then the list can be determined as NULL */

    int isNull, i;
    int counter = 0;

    for(i = 0; i < length; i++){

        if(IGNORELIST[i] == -1 ){counter++;}

    }
    
    if(counter <= 1){isNull =1;}
    else{isNull = 0;}
    return isNull;
}

/* Print functions */
void printEdgeArray(Edge** E, const int count){

    int i;

    for(i = 0; i < count; i++){

        printf("Edge %d = %f\n",i,E[i]->weight);

    }

}

void printNodeArr(Node** A,int count, int*IGNORELIST){

    int i;
    Vertex* V;

    for(i = 0; i < count-1; i++){
        V = A[i]->data;
        if(IGNORELIST[i] != 1){
            printf("NODE ID:\t %d\n",V->id);
        }

    }
  
}

void printWeightArr(double* D,const int length){

    int x;

    for(x = 0; x < length; x++){
        if(D[x]>100){
            printf("\nweight -- INF\n");
        }else{printf("\nweight -- %.2f\n",D[x]);}
        
    }

} 

void printIDArr(int* IDs,const int length){

    int x;

    for(x = 0; x < length; x++){

        printf("ID -- %d\n",IDs[x]);

    }


}
/* Print functions */

/* find shortest paths between source node id and all other nodes in graph. */
/* upon success, returns an array containing a table of shortest paths.  */
/* return NULL if *graph is uninitialised or an error occurs. */
/* each entry of the table array should be a Path */
/* structure containing the path information for the shortest path between */
/* the source node and every node in the graph. If no path exists to a */
/* particular desination node, then next should be set to -1 and weight */
/* to DBL_MAX in the Path structure for this node */

/* While S is not empty:

    Select a node u from S D[u] is minimum (pick shortest path from S)
    
        if this path is INF, abort since no path exists in nodes in S (if weight of shortest return is == DBL_MAX exit failure)
    
    delete u from set S
    
    for each node v such that u,v is an edge

        if v is still in S

            c = D[u] + weight(u,v)

            if c < D[v] then update the tables R and D

                R[v] = R[u]
                
                D[v] = c
    
    */



Path *dijkstra(Graph *graph, int id, int *pnEntries)
{
    /* Variables | D = weight table | R = ID table | S = node table | IGNORE = Ignore table| avoid = changing ID to avoid using (source network) */
    int weightLen, IDLen, S_Len, *IGNORE;
    int avoid = id;
    int counter = 0;
    
    /* Variables */

    /* Iteration variables */

    Node* U;            /* Current network being looked at*/
    Vertex* V;          /* Adjacent node from list of edges from U */
    double C;           /* Sum of weight travelled between U and V */
    double currWeight;  /* Current weight of source node */
    Edge** E;           /* To hold array of edges */
    int EdgeCount, i,x;
    /* Iteration variables */

    /* Tables */
    Path * Table;
    Node ** S;
    double * D;
    int* R;
    /* Tables */
    
    /* Insert your implementation of Dijkstra's algorithm here */

    if(errorCheck(graph,avoid)){
        return NULL;
    }
    *pnEntries = x = 0;
    S_Len = countNodes(graph);

    /* Respective tables */
    S = Gen_S_Table(graph,avoid);
    R = Gen_R_Table(graph,avoid,&IDLen);   
    D = Gen_D_Table(graph,avoid,&weightLen);
    IGNORE = generateIGNORE(S_Len);
    /* Respective tables */


    while(!(NULL_S(IGNORE,S_Len))){

        /* Find shortest */
        U = S[findShortest(D,S_Len,&currWeight,IGNORE)];
        V = U->data;
        /* Find shortest */
        /* Get edges of shortest */
        E = get_edges(graph,V,&EdgeCount);
        /* Get edges of shortest */

        /* Assemble weight of travel */
        for(i = 0;  i < EdgeCount ; i++){
            if(edge_destination(E[i]) != avoid){
                /* Assembling weight */
                C = currWeight + E[i]->weight;
                /* Assembling weight */

                if(C < D[getIndex(S,S_Len,V->id)] ){
                    D[getIndex(S,S_Len,V->id)] = C; /* THis may be the wrong */
                    R[getIndex(S,S_Len,V->id)] = V->id;
                }
                
            }
        }
        /* Assemble weight of travel */
      
        i = *pnEntries;
        i++;
        *pnEntries = i;
    }

    Table = (Path*)malloc(sizeof(Path)* (*pnEntries));
    for(i = 0 ; i < *pnEntries; i++){
        Table[i].weight = D[i];
        Table[i].next_hop = R[i];
    }
    
    return Table;
}

/* Note:, instead of removing elems from the S array, jusy change the counter for the start. so start off at 0, "pop", start off from 1, "pop",start off from 2 */


/* Temp code */

/*     UID = findShortest(D,weightLen); */            /* Generate ID of U for later use */
/*     U = S[findShortest(D,weightLen)]; */           /* Generate U */
/*     E = get_edges(graph,U->data,&EdgeCount);  */   /* Get array of edges from U */


/*     i = 0;
     
    while(!NULL_S(IGNORE,S_Len)){


        
        addIgnore(IGNORE,i,S_Len);
       
        *pnEntries = i;
        i++;
    }   */


/* Code graveyard */

/*  void Pop_S(Node** S, int*count){

    Node *N = S[0];
    int x,i;
    x = i = 0;
    while(N){

        x++;
        N = N->next;

    }
    
    if(*count == x){
        return;
    }
    x = *count; 
    x++;
    *count = x;   

} */


/* 
int isInSet(Edge*E,Node**S,const int S_Count){ | if edge points to elem not in set, return 0, else return 1 | This is to stop calculating invalid weights */
 /*                                             
    int i;
    int UID = edge_destination(E);

    for(i = 0; i < S_Count;i++){

         if(UID == E->vertex->id){
             printf("%d\n",E->vertex->id);
         }
    }

    return 1;
}
  */ 