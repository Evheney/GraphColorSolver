#include "vertex.h"

Vertex::Vertex()
    : x_(0)
    , y_(0)
    , color_(Qt::lightGray)
{
}

Vertex::Vertex (int x, int y)
    : x_(x)
    , y_(y)
    , color_(Qt::lightGray)
{
}

Vertex::Vertex (int x, int y, QColor color)
    : x_(x)
    , y_(y)
    , color_(color)
{

}

