#ifndef GREEDYCOLOREROPENMPSOLVER_H
#define GREEDYCOLOREROPENMPSOLVER_H

#include "colorersolver.h"

class Graph;

class GreedyColorerOpenMpSolver : public ColorerSolver
{
public:
    GreedyColorerOpenMpSolver();
    // BaseColorer interface
public:
    virtual bool coloring(Graph* graph, int noC, QColor* colors);
    virtual QString coloringName() const { return "Greedy OpenMP"; }

};

#endif // GREEDYCOLOREROPENMPSOLVER_H
