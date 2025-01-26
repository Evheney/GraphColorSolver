#ifndef EDGE_H
#define EDGE_H

class Vertex;

class Edge
{
public:
    Edge(Vertex* v1, Vertex* v2, double weight = -1, bool enabled = true);

    double weight() const;
    Vertex* v1() const{ return v1_;}
    Vertex* v2() const { return v2_; }
    bool isEnabled() const { return enabled_; }

private:
    Vertex* v1_;
    Vertex* v2_;
    bool enabled_;
    double weight_;
};

#endif // EDGE_H
