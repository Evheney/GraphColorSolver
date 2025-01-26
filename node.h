#ifndef MYNODE_H
#define MYNODE_H


#include <QGraphicsItem>
#include <QKeyEvent>

class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Node(int index);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void keyPressEvent ( QKeyEvent * event );

    int getIndex() const { return index_; };
    void setColor(QColor color) { color_ = color; }

signals:
    void moved(Node *node);
    void deleted(Node *node);
public slots:

protected:
    QString indexName() { return QString::number(index_); }

private:
    int index_;
    QColor color_;
};

#endif // MYNODE_H
