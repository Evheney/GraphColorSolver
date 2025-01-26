#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>

class ColorerSolver;
class Edge;
class Vertex;

class Graph
{
public:
    Graph(int v, ColorerSolver* c=nullptr);
    ~Graph();

    int adjacent(int i, int j) const { return adj_[i][j]; }

    bool create(int v);

    int vertexCount() const { return vertices_.count(); }
    int addVertex(int x, int y);
    Vertex* getVertex(int index);
    bool removeVertex(int index);

    int edgeCount() const {return edges_.count(); }
    bool linkVertices(int from, int to);
    Edge* getEdge(int index);

    void setColorer(ColorerSolver* cPtr);
    bool coloring();

    QString coloringName();
private:
    int noV_; // No. of vertices
    int **adj_; // 2D adjacency matrix

    QVector<Vertex*> vertices_;
    QVector<Edge*> edges_;

    ColorerSolver* colorer_;

    bool create5();
    bool create10();
    bool create20();
    bool create30();
};

#endif // GRAPH_H
