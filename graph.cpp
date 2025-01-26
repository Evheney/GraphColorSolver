#include <QDebug>

#include "colorersolver.h"
#include "edge.h"
#include "graph.h"
#include "vertex.h"

QColor kColors[] = {
    Qt::red,
    Qt::green,
    Qt::magenta,
    Qt::cyan,
    Qt::yellow,
    Qt::lightGray,
};

Graph::Graph(int noV_, ColorerSolver* c) : noV_(noV_), colorer_(c)
{
    adj_ = new int *[noV_];
    for(int i=0;i<noV_;i++){
        adj_[i] = new int[noV_];
    }

    for(int i=0;i<noV_;i++){
        for(int j=0;j<noV_;j++){
            adj_[i][j]=0;
        }
    }
}

Graph::~Graph()
{
    for(int i=0;i<noV_;i++){
        delete [] adj_[i];
    }
    delete [] adj_;

    qDeleteAll(vertices_);
    vertices_.clear();
}

bool Graph::create(int noV)
{
    switch(noV)
    {
    default:
    case 5: create5(); break;
    case 10: create10(); break;
    case 20: create20(); break;
    case 30: create30(); break;
    }
    return true;
}
bool Graph::create5()
{
    int vx0 = addVertex(200,50);
    int vx1 = addVertex(50,150);
    int vx2 = addVertex(350,150);
    int vx3 = addVertex(200,250);
    int vx4 = addVertex(200,350);

    linkVertices(vx0,vx1);
    linkVertices(vx0,vx2);
    linkVertices(vx1,vx2);
    linkVertices(vx1,vx3);
    linkVertices(vx2,vx3);
    linkVertices(vx3,vx4);

    return true;
}

bool Graph::create10()
{
    int vx0 = addVertex(200,50);
    int vx1 = addVertex(50,150);
    int vx2 = addVertex(350,150);
    int vx3 = addVertex(200,250);
    int vx4 = addVertex(200,350);
    int vx5 = addVertex(25,50);

    linkVertices(vx0,vx1);
    linkVertices(vx0,vx2);
    linkVertices(vx1,vx2);
    linkVertices(vx1,vx3);
    linkVertices(vx2,vx3);
    linkVertices(vx3,vx4);
    linkVertices(vx5,vx2);
    linkVertices(vx5,vx1);

    return true;
}
bool Graph::create20()
{
    int vx0 = addVertex(200,50);
    int vx1 = addVertex(50,150);
    int vx2 = addVertex(350,150);
    int vx3 = addVertex(200,250);
    int vx4 = addVertex(200,350);
    int vx5 = addVertex(25,50);

    linkVertices(vx0,vx1);
    linkVertices(vx0,vx2);
    linkVertices(vx1,vx2);
    linkVertices(vx1,vx3);
    linkVertices(vx2,vx3);
    linkVertices(vx3,vx4);
    linkVertices(vx5,vx2);
    linkVertices(vx5,vx1);

    return true;
}
bool Graph::create30()
{
    int vx0 = addVertex(200,50);
    int vx1 = addVertex(50,150);
    int vx2 = addVertex(350,150);
    int vx3 = addVertex(200,250);
    int vx4 = addVertex(200,350);
    int vx5 = addVertex(25,50);

    linkVertices(vx0,vx1);
    linkVertices(vx0,vx2);
    linkVertices(vx1,vx2);
    linkVertices(vx1,vx3);
    linkVertices(vx2,vx3);
    linkVertices(vx3,vx4);
    linkVertices(vx5,vx2);
    linkVertices(vx5,vx1);

    return true;
}

int Graph::addVertex(int x, int y)
{
    Vertex* vx = new Vertex(x,y);
    if (vx) {
        vertices_.push_back(vx);
        return vertices_.count()-1;
    }
    return -1;
}

Vertex* Graph::getVertex(int index)
{
    return vertices_[index];
}

bool Graph::removeVertex(int index)
{
    Vertex* vx = getVertex(index);
    if (vx) {
        vertices_.remove(index);
        delete vx;
        return true;
    }
    return false;
}

bool Graph::linkVertices(int from, int to)
{
    adj_[from][to]=1;
    adj_[to][from]=1; //undirected graph

    Vertex* vx1 = getVertex(from);
    Vertex* vx2 = getVertex(to);
    if (vx1 && vx2) {
        edges_.push_back(new Edge(vx1,vx2));
        return true;
    }
    return false;
}

Edge *Graph::getEdge(int index)
{
    return edges_[index];
}

void Graph::setColorer(ColorerSolver *cPtr)
{
    if (colorer_)
        delete colorer_;

    colorer_ = cPtr;
}

bool Graph::coloring()
{
    bool result = false;
    if (colorer_) {
        result = colorer_->coloring(this, _countof(kColors), kColors);
        return result;
    }
    return result;
}

QString Graph::coloringName()
{
    if (colorer_)
        return colorer_->coloringName();
    return QString("");
}
