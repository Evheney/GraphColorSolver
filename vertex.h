#ifndef VERTEX_H
#define VERTEX_H

#include <QColor>
#include <QString>

class Vertex
{
public:
    Vertex ();
    Vertex (int x, int y);
    Vertex (int x, int y, QColor color);

    int x() const{ return x_; }
    int y() const { return y_; }

    void setX(int x) {x_ = x; }
    void setY(int y) {y_ = y; }

    void setName(const QString& name) { name_ = name; }
    QString name() const { return name_; }

    void setColor(QColor c) { color_ = c; }
    QColor color() const { return color_; }

private:
    int x_, y_;
    QString name_;
    QColor color_;
};

#endif // VERTEX_H
