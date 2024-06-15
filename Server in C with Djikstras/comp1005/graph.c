#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

/* initialise an empty graph */
/* return pointer to initialised graph */
Graph *init_graph(void)
{
    Graph* G = initialise_linked_list();
    return G;

}

/* release memory for graph */
void free_graph(Graph *graph)
{
    /* To do later when all other freeing methods are done */
 
    Node* N;
    Node* N2;
    Vertex* V;
    if(graph == NULL){

        fprintf(stderr,"error: cant free null graph\n");
        return;
    }

    if(graph->head == NULL){

        free_linked_list(graph); 
        return;

    }

    N = graph->head;

    while(N){
        V = N->data;
        N2 = N->next;
        remove_vertex(graph,V->id);
        N = N2;
    
    }
    
    free_linked_list(graph); 

}

/* initialise a vertex */
/* return pointer to initialised vertex */
Vertex *init_vertex(int id)
{
    Vertex* V = (Vertex*)malloc(sizeof(Vertex));
    V->id = id;
    V->edges = initialise_linked_list();
    return V;

}

/* release memory for initialised vertex */
void free_vertex(Vertex *vertex)
{
    if(vertex == NULL){
        fprintf(stderr, "error: cant free NULL vertex\n");
        return;

    }
/*     if(vertex->edges == NULL){
        fprintf(stderr,"error: cannot free set of edges with no eges\n");

    } */

    free_linked_list(vertex->edges);
    free(vertex);
    
}

/* initialise an edge. */
/* return pointer to initialised edge. */
Edge *init_edge(void)
{
    Edge* E = (Edge*)malloc(sizeof(Edge));
    E->weight = 0.00;
    E->vertex = NULL;
    return E;
}

/* release memory for initialised edge. */
void free_edge(Edge *edge)
{

    if(edge == NULL){
        fprintf(stderr,"error: cant free a NULL edge");
    }

    free(edge);

}

/* remove all edges from vertex with id from to vertex with id to from graph. */
void remove_edge(Graph *graph, int from, int to)
{
}

/* remove all edges from vertex with specified id. */
/* So only remove edges from vertex "from" if they point to vertex "to" */
void remove_edges(Graph *graph, int id)
{

    Node* N, *EN;
    Vertex* V;
    Edge * E;

    if(graph && graph->head){
    
        N = graph->head;


        while(N){ /* Find the "from" ID */

            V = N->data;
            if(V->id == id){ /* Find the "to" ID */
                
                /* printf("--%d--\n",V->id); */
                
                if (V->edges->head != NULL)
                {
                    EN = V->edges->head;
                    while(EN){

                        E = EN->data;
                        if(E->vertex){
                            free_edge(E);
                        }
                        EN = EN->next;
                        
                    }

                }
                

            }


            N = N->next;

        }


            
    }else{return;}
    return;

}

/* output all vertices and edges in graph. */
/* each vertex in the graphs should be printed on a new line */
/* each vertex should be printed in the following format: */
/* vertex_id: edge_to_vertex[weight] edge_to_vertex[weight] ... */
/* for example: */
/* 1: 3[1.00] 5[2.00] */
/* indicating that vertex id 1 has edges to vertices 3 and 5 */
/* with weights 1.00 and 2.00 respectively */
/* weights should be output to two decimal places */
void print_graph(Graph *graph)
{

    Node * N;
    Vertex* V;

    if(graph != NULL){ 

        if(graph->head == NULL){
            return;
        }

        N  = graph->head;
        V  = (Vertex *)N->data; /* Mental note: this line of code allows us to access id and edges later down the line */
        while(N){
            
            
            V = N->data;
            printf("%d\n",V->id);
            
            N = N->next;
        
        }
     
    }
    else{
        fprintf(stderr,"error: graph parsed into print_graph is type NULL so it cannot be printed\n");
    }
}   

/* find vertex with specified id in graph. */
/* return pointer to vertex, or NULL if no vertex found. */
Vertex *find_vertex(Graph *graph, int id)
{
    Node* N;
    Vertex* V = NULL;

    if(graph == NULL){
        fprintf(stderr, "error: cannot find vertex in null graph\n");
        return NULL;
    }else if(graph->head == NULL){
        return NULL;
    }else{

        N = graph->head;
        while(N){
            
            V = N->data;
            
            if(V->edges!= NULL ){       /* invalid read here, FIX */
                if( V->id == id){
                    return V;
                }
            }
            N = N->next;
        }

    }
    return NULL;
        

}

/* create and add vertex with specified id to graph. */
/* return pointer to vertex or NULL if an error occurs. */
/* if vertex with id already exists, return pointer to existing vertex. */
Vertex *add_vertex(Graph *graph, int id)
{
    Vertex* V;
    if(!graph){
        fprintf(stderr,"error: cant add vertex to empty graph");
        return NULL;
    }
    V = find_vertex(graph,id);
    if(V){
        return V;
    }else{
        V = init_vertex(id);
        append_linked_list(graph,V);
    }
    
    return V;
    

}

/* remove vertex with specified id from graph. */
/* remove all edges between specified vertex and any other vertices in graph. */
void remove_vertex(Graph *graph, int id)
{

    Vertex * V;
    Node* N;
    if(!graph){
        fprintf(stderr,"error: cannot work on NULL graph in remove_vertex function\n");
    }
    V = find_vertex(graph,id);
    if(!V){fprintf(stderr,"error: vertex doesnt exist within graph\n");
            return;}


    N = graph->head;

    while(N){

        V = N->data;
        if(V->id == id){

          
            if(N == graph->head){

                if(!N->prev && !N->next){
                    free_vertex(V);
                    remove_head_linked_list(graph);
                }
                else if(N->next && !N->prev){
                    N->next->prev = NULL;
                    free_vertex(V);
                    remove_head_linked_list(graph);
                }
                else if(N->prev && !N->next){
                    N->prev->next = NULL;
                    free_vertex(V);
                    remove_head_linked_list(graph);
                }

            }
            else if(N == graph->tail){
                if(!N->prev && !N->next){
                    free_vertex(V);
                    remove_tail_linked_list(graph);
                }
                else if(N->next && !N->prev){
                    N->next->prev = NULL;
                    free_vertex(V);
                    remove_tail_linked_list(graph);
                }
                else if(N->prev && !N->next){
                    N->prev->next = NULL;
                    free_vertex(V);
                    remove_tail_linked_list(graph);
                }
            }
            else{
                if(!N->prev && !N->next){
                    free_vertex(V);
                    free_node(N);
                }
                else if(N->next && !N->prev){
                    N->next->prev = NULL;
                    free_vertex(V);
                    free_node(N);
                }
                else if(N->prev && !N->next){
                    N->prev->next = NULL;
                    free_vertex(V);
                    free_node(N);
                }else{
                
                    
                }
            }

            return;
        }
        
        
        N = N->next;

    }
}



/* add directed edge with specified weight between vertex with id "from" */
/* to vertex with id "to." */
/* if no vertices with specified ids (from or to) exist */
/* then the vertices will be created. */
/* multiple vertices between the same pair of vertices are allowed. */
/* return pointer to edge, or NULL if an error occurs found. */

/* Point from "from" to "to" */

/* A---------->B */

Edge *add_edge(Graph *graph, int from, int to, double weight)
{
    
    Vertex* V1, *V2;
    Edge* E;
    if(graph == NULL){

        fprintf(stderr, "error: cant add edge to NULL graph\n");

        return NULL;

    }

    if((V1 = find_vertex(graph,from)) == NULL){

        V1 = add_vertex(graph,from);

    }
    if((V2 = find_vertex(graph,to))== NULL){

        V2 = add_vertex(graph,to);

    }

    E = init_edge();  
    E->weight = weight;
    E->vertex = V2; 
    append_linked_list(V1->edges,E);
    return E;
}

/* add two edges to graph, one from vertex with id from to vertex with id to, */
/* and one from vertex with id to to vertex with id from. */
/* both edges should have the same weight */
/* if no vertices with specified ids (from or to) exist */
/* then the vertices will be created. */
/* multiple vertices between the same pair of vertices are allowed. */

/*
    A               B
    *               *
    --------------->
    <---------------
*/


void add_edge_undirected(Graph *graph, int from, int to, double weight)
{

    Vertex* V1, *V2;

    if(graph == NULL){

        fprintf(stderr, "error: cant add edge to NULL graph\n");

        return;

    }

    if((V1 = find_vertex(graph,from)) == NULL){

        V1 = add_vertex(graph,from);

    }
    if((V2 = find_vertex(graph,to))== NULL){

        V2 = add_vertex(graph,to);

    }

    add_edge(graph,from,to,weight);
    add_edge(graph,to,from,weight);

}

/* return array of node ids in graph. */
/* array of node ids should be dynamically allocated */
/* set count to be the number of nodes in graph */
/* return NULL if no vertices in graph */
int *get_vertices(Graph *graph, int *count)
{
    Node* N;
    Vertex* V;
    int c = 0;
    int x = 0;
    int * arr;
    if(!graph || !graph->head){
        fprintf(stderr,"error: cant get vertex amount/IDS from NULL graph\n");
        return NULL;
    }
    N = graph->head;
    
    while(N){

        c++;
        N = N->next;

    }
    if(!(arr = (int*)malloc(c*sizeof(int)))){
        fprintf(stderr,"error: memory allocation error in get_vertices function\n");

    }

    N = graph->head;

    while(N){
        V = N->data;
        arr[x] = V->id;
        x++;
        N = N->next;
    }

    *count = c;

    return arr;

}

/* return array of pointers to edges for a given vertex. */
/* array of edges should be dynamically allocated */
/* set count to be number of edges of vertex */
/* return NULL if no edges from/to vertex */
Edge **get_edges(Graph *graph, Vertex *vertex, int *count)
{

    int* arr = (int*)malloc(sizeof(int));
    if(!graph || !vertex){
        free(arr);
        return NULL;
    }
    else{return NULL;}
}

/* return pointer to edge from vertex with id from, to vertex with id to. */
/* return NULL if no edge */
Edge *get_edge(Graph *graph, int from, int to)
{
   
    Node* N, *EN;
    Vertex* V;
    Edge * E;

    if(graph && graph->head){
    
        N = graph->head;


        while(N){ /* Find the "from" ID */

            V = N->data;
            if(V->id == from){ /* Find the "to" ID */
                
                /* printf("--%d--\n",V->id); */
                
                if (V->edges->head != NULL)
                {
                    EN = V->edges->head;
                    while(EN){

                        E = EN->data;
                        if(E->vertex->id == to){
                            return E;
                        }
                        EN = EN->next;
                        
                    }

                }
                

            }


            N = N->next;

        }


            
    }else{return NULL;}
    return NULL;

}

/* return id of destination node of edge. */
int edge_destination(Edge *edge)
{
    if(edge){

        return edge->vertex->id;

    }return __INT_MAX__;

}

/* return weight of edge. */
double edge_weight(Edge *edge)
{
    if(edge){
        return edge->weight;
    }
    return __SIZEOF_DOUBLE__;

}

          /*            
            if((!N->prev) && (!N->next)){
                if(!graph->head && !graph->tail){
                    free_vertex(V);
                    free_node(N);
                }
                }else{
                    if(graph->head){
                        free_vertex(V);
                        remove_head_linked_list(graph);
                    }else if(graph->tail){

                        free_vertex(V);
                        remove_tail_linked_list(graph);
                    }
                }

            }else if(!N->prev && N->next){
                if(!graph->head ){
                    free_vertex(V);
                    free_node(N);
                }else{
                    free_vertex(V);
                    remove_head_linked_list(graph);
                }

            }else if(!N->next && N->prev){
                if(!graph->tail ){
                    free_vertex(V);
                    free_node(N);
                }else{
                    free_vertex(V);
                    remove_tail_linked_list(graph);
                }

            }

            if((!N->prev) && (!N->next)){
                if(!graph->head && !graph->tail){
                    free_vertex(V);
                    free_node(N);
                }
                }else{
                    if(graph->head){
                        free_vertex(V);
                        remove_head_linked_list(graph);
                    }else if(graph->tail){

                        free_vertex(V);
                        remove_tail_linked_list(graph);
                    }
                }

            }else if(!N->prev && N->next){
                if(!graph->head ){
                    free_vertex(V);
                    free_node(N);
                }else{
                    free_vertex(V);
                    remove_head_linked_list(graph);
                }

            }else if(!N->next && N->prev){
                if(!graph->tail ){
                    free_vertex(V);
                    free_node(N);
                }else{
                    free_vertex(V);
                    remove_tail_linked_list(graph);
                }

            }
 */