#include <QDebug>

#include "backtrackingcolorersolver.h"
#include "graph.h"
#include "vertex.h"

BacktrackingColorerSolver::BacktrackingColorerSolver()
    : noV_(-1)
{

}

/* A utility function to check if the current color assignment
is safe for vertex v i.e. checks whether the edge exists or not
(i.e, graph[v][i]==1). If exist then checks whether the color to
be filled in the new vertex(c is sent in the parameter) is already
used by its adjacent vertices(i-->adj vertices) or not (i.e, color[i]==c) */
bool BacktrackingColorerSolver::isSafe (int v, Graph* graph, int color[], int c)
{
    for (int i = 0; i < noV_; i++)
        if (graph->adjacent(v,i) && c == color[i])
            return false;
    return true;
}

/* A recursive utility function to solve m coloring problem */
bool BacktrackingColorerSolver::graphUtil(Graph* graph, int m, int color[], int v)
{
    /* base case: If all vertices are assigned a color then
       return true */
    if (v == noV_)
        return true;


    /* Consider this vertex v and try different colors */
    for (int c = 1; c <= m; c++)
    {
        /* Check if assignment of color c to v is fine*/
        if (isSafe(v, graph, color, c))
        {
            color[v] = c;

            /* recur to assign colors to rest of the vertices */
            if (graphUtil(graph, m, color, v+1) == true)
                return true;

            /* If assigning color c doesn't lead to a solution
               then remove it */
            color[v] = 0;
        }
    }

    /* If no color can be assigned to this vertex then return false */
    return false;
}

/* This function solves the m Coloring problem using Backtracking.
  It mainly uses graphColoringUtil() to solve the problem. It returns
  false if the m colors cannot be assigned, otherwise return true and
  prints assignments of colors to all vertices. Please note that there
  may be more than one solutions, this function prints one of the
  feasible solutions.*/
bool BacktrackingColorerSolver::coloring(Graph* graph, int noC, QColor *colors)
{
    const int m = 3;

    qDebug().nospace() << "Backtracking coloring";

    // Assign the available colors
    setColors(noC, colors);

    noV_ = graph->vertexCount();
    //QVector<int> result(noV, -1);

    // Initialize all color values as 0. This initialization is needed
    // correct functioning of isSafe()
    int *color = new int[noV_];
    for (int i = 0; i < noV_; i++)
        color[i] = 0;

    // Call coloringUtil() for vertex 0
    if (graphUtil(graph, m, color, 0) == false)
    {
        delete [] color;
        return false;
    }

    // Print the result
    for (int u = 0; u < noV_; u++) {
        qDebug().nospace() << "Vertex " << u
                           << " ---> Color " << color[u];
    }

    // Assign the color to graph vertex
    for (int i=0; i<graph->vertexCount(); i++) {
        Vertex* vx = graph->getVertex(i);
        QColor clr = availableColors_[color[i]];
        vx->setColor(clr);
    }

    delete [] color;

    return true;
}
