#include "backtrackingcolorersolver.h"
#include "greedycolorersolver.h"
#include "greedycoloreropenmpsolver.h"

ColorerSolver* ColorerSolver::create(ColorerSolver::Id id)
{
    ColorerSolver* p = nullptr;
    switch (id) {
    case ColorerSolver::Bruteforce:
        // p = ...
        break;
    case ColorerSolver::Backtrace:
        p = new BacktrackingColorerSolver();
        break;
    case ColorerSolver::Greedy:
        p = new GreedyColorerSolver();
        break;
    case ColorerSolver::GreedyOpenMP:
        p = new GreedyColorerOpenMpSolver();
        break;
    default:
        break;
    }

    return p;
}
