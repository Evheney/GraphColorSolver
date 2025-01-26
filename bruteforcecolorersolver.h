#ifndef BRUTEFORCECOLORERSOLVER_H
#define BRUTEFORCECOLORERSOLVER_H

#include "colorersolver.h"

class Graph;

class BruteforceColorerSolver : public ColorerSolver
{
public:
    BruteforceColorerSolver();

// BaseColorer interface
public:
    virtual bool coloring(Graph* graph, int noC, QColor* colors);
    virtual QString coloringName() const { return "Bruteforce"; }
};

#endif // BRUTEFORCECOLORERSOLVER_H
