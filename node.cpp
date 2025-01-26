#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include "node.h"

// Constructor
Node::Node(int index) : QObject(), QGraphicsItem(), index_(index), color_(Qt::yellow)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(ItemSendsGeometryChanges);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);

    // Draw a circle outline
    painter->drawEllipse(-7, -7, 20, 20);

    // Drow an fancy gradient filled circle
    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Selected)
    {
        //... blue when it is selected
        gradient.setColorAt(0, Qt::blue);
        gradient.setColorAt(1, Qt::darkBlue);
    }
    else
    {
        //... normal color when it is regular
        gradient.setColorAt(0, color_);
        gradient.setColorAt(1, color_);
    }

    painter->setBrush(gradient);

    // Draw a shadow
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-9, -9, 20, 20);

    // Display an vertex index
    painter->setPen(QPen(Qt::blue, 0));
    painter->drawText(QRectF(-7,-25, 20, 15), Qt::AlignCenter, indexName());
}

QRectF Node::boundingRect() const
{
    qreal adjust = 20;
    return QRectF(-10 - adjust, -10 - adjust,
                  23 + adjust, 23 + adjust);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        emit moved(this);
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::keyPressEvent ( QKeyEvent * event )
{
    //if (event->key() == Qt::Key_Delete)
    //    emit deleted(this);
}
