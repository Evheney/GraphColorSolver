#include <QDebug>
#include <QVector>

#include "graph.h"
#include "greedycoloreropenmpsolver.h"
#include "vertex.h"

GreedyColorerOpenMpSolver::GreedyColorerOpenMpSolver()
    : ColorerSolver()
{

}

bool GreedyColorerOpenMpSolver::coloring(Graph* graph, int noC, QColor* colors)
{
    qDebug().nospace() << "Greedy coloring";

    // Assign the available colors
    setColors(noC, colors);

    const int noV = graph->vertexCount();
    QVector<int> result(noV, -1);

    // Assign the first color to first vertex
    result[0] = 0;

#pragma omp parallel
{
    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // available to assign
    QVector<bool> available(noV);
    for (int cr = 0; cr < noV; cr++)
        available[cr] = true;

    // Assign colors to remaining noV-1 vertices
    #pragma omp for
    for (int u = 1; u < noV; u++) {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        for(int i=0;i<noV;i++) {
            if(graph->adjacent(u,i)) {
                if(result[i]!=-1){
                    available[result[i]]=false;
                }
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < noV; cr++) {
            if (available[cr] == true)
                break;
        }

        // Assign the found color
        result[u] = cr;

        // Reset the values back to true for the next iteration
        for (int cr = 0; cr < noV; cr++) {
            available[cr] = true;
        }
    }
}

    // print the result
    for (int u = 0; u < noV; u++) {
        qDebug().nospace() << "Vertex " << u
                << " ---> Color " << result[u];
    }

    for (int i=0; i<graph->vertexCount(); i++) {
        Vertex* vx = graph->getVertex(i);
        QColor color = availableColors_[result[i]];
        vx->setColor(color);
    }

    return true;
}
