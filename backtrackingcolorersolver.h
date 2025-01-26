#ifndef BACKTRACKINGCOLORERSOLVER_H
#define BACKTRACKINGCOLORERSOLVER_H

#include "colorersolver.h"

class Graph;


class BacktrackingColorerSolver  : public ColorerSolver
{
public:
    BacktrackingColorerSolver();

// BaseColorer interface
public:
    virtual bool coloring(Graph* graph, int noC, QColor* colors);
    virtual QString coloringName() const { return "Backtrack"; }

protected:
    int noV_;

    bool isSafe (int v, Graph* graph, int color[], int c);

    bool graphUtil(Graph* graph, int m, int color[], int v);

};

#endif // BACKTRACKINGCOLORERSOLVER_H
