/*
 *  dijkstras.h
 *  ProgrammingPortfolio
 *
 *  Created by Steven Bagley on 09/12/2021.
 */

#ifndef dijkstra_h
#define dijkstra_h

/* an entry storing the shortest path */
/* next_hop is the next vertex in the path */
/* weight is the total weight of the path to dst */
typedef struct Path
{
    int next_hop;
    double weight;
} Path;


Path *dijkstra(Graph *graph, int id, int *pnEntries);

#endif /* dijkstras_h */
