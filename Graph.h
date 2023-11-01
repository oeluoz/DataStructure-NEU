#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define INF 99999
#define MAX_VEX 100

typedef int VertexType;
typedef enum {DG, UDG, DN, UDN} GraphKind;
typedef struct info {

} InfoType;

typedef struct {
    int weight;
    // InfoType *pInfo;
} AdjacentArray[MAX_VEX][MAX_VEX] ;

typedef struct {
    AdjacentArray edges;
    VertexType vertex[MAX_VEX];
    int vertexNum;
    int edgeNum;
    GraphKind kind;
} MatrixGraph;

void graphDemo();
void createMGraph();
#endif // GRAPH_H_INCLUDED
