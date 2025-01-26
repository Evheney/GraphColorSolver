#ifndef BASECOLORER_H
#define BASECOLORER_H

#include <QColor>
#include <QVector>

class Graph;


class ColorerSolver
{
public:
    enum Id
    {
        Unknown=-1,
        Bruteforce=0,
        Backtrace,
        Greedy,
        GreedyOpenMP,
    };

    ColorerSolver();

    virtual bool coloring(Graph* graph, int noC, QColor* colors) = 0;
    virtual QString coloringName() const = 0;

    void setColors(int noC, QColor* colors);
    QColor color(int index) { return availableColors_[index%availableColors_.count()];}

    static ColorerSolver* create(ColorerSolver::Id id);

protected:
    QVector<QColor> availableColors_;
};

#endif // BASECOLORER_H
