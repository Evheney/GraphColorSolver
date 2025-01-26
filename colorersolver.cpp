#include "colorersolver.h"

ColorerSolver::ColorerSolver()
{

}

void ColorerSolver::setColors(int noC, QColor *colors)
{
    for (int idx = 0; idx < noC; ++idx)
        availableColors_.append(colors[idx]);
}
