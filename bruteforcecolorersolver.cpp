#include <QDebug>

#include "bruteforcecolorersolver.h"
#include "graph.h"
#include "vertex.h"

BruteforceColorerSolver::BruteforceColorerSolver()
{
}


/*
https://stackoverflow.com/questions/39865194/optimization-in-brute-force-vertex-cover-algorithm
BruteForceVertexCover( Graph G = (V,E) ){
    for size= 1 ... |V|
        vector<int> v = {0...size-1}
        do{
            if(test(G, v)) return v;     //test if v covers G
        }
        while(v has next combinations of lenght size);
    return empty vector<int>;
}

//this stops when find a answer, and it will find,
//since it tries all combinations of all sizes
where

bool test( Graph G = (V,E), vector<int> v ){
    for each u in v:
        for each w in G[u]
            remove u from G[w]     //this is linear in size of vector G[w]
        clear G[v]                 //removed all (bidirectional) edges that have u
    for i = 0 ... |V|
        if(G[i] is not empty) return false;
        return true;
}
im trying this to lots of graphs (but their maximum size is 20 vertices) and
this is taking a decade... is there any optimization I can do on this
brute force so it run faster?
*/

bool BruteforceColorerSolver::coloring(Graph* graph, int noC, QColor *colors)
{
    qDebug().nospace() << "Bruteforce coloring";

    // Assign the available colors
    setColors(noC, colors);

    const int noV = graph->vertexCount();
    QVector<int> resultColor(noV, -1);

    // Assign the first color to first vertex
    resultColor[0] = 0;


    for (int u = 1; u < noV; u++) {
        for (int v = 0; v < noV; v++) {
            // Not implemented yet
        }
    }

    return true;
}
