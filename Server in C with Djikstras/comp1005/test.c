/* This file is for testing functions and code from graph.c */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "graph.h"
#include "utility.h"


void foundVertex(Graph* g, int id){

    if(find_vertex(g,id) != NULL){
        printf("found vertex with id %d\n",id);
    }else{
        printf("Vertex with id %d doesnt exist\n",id);

    }

}


int main(void){

    Graph* G = init_graph();
    Edge* E;
    int count = 0;
    int*  numofARR;
    int i;


                                    /* init graph and free graph work (for the graph part itself) */
                                    /* find vertex needs work */

                                    /* add vertex works, remove vertex has mem leaks */
    
    
    add_edge(G,1025,2245,1.21);
    add_edge(G,1025,12,1.22);
    add_edge(G,1025,5,1.23);
    add_edge(G,1025,2245,1.42069);


    numofARR = get_vertices(G,&count);


    
    remove_edges(G,1025);


    free(numofARR);
    

    free_graph(G); 


    return 0;
}