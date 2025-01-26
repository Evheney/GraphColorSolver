#include "edge.h"
#include "vertex.h"

Edge::Edge(Vertex* v1, Vertex* v2, double weight, bool enabled)
    : v1_(v1)
    , v2_(v2)
    , weight_(weight)
    , enabled_(enabled)
{
}

double Edge::weight() const
{
    if (weight_>0)
        return weight_;
    return sqrt(pow(v1_->x()-v2_->x(),2) + pow(v1_->y()-v2_->y(),2));
}
