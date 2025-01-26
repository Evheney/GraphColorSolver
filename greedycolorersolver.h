#ifndef GREEDYCOLORER_H
#define GREEDYCOLORER_H

#include "colorersolver.h"

class Graph;

class GreedyColorerSolver : public ColorerSolver
{
public:
    GreedyColorerSolver();

// BaseColorer interface
public:
    virtual bool coloring(Graph* graph, int noC, QColor* colors);
    virtual QString coloringName() const { return "Greedy"; }

};

#endif // GREEDYCOLORER_H
