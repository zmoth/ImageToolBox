#include "CrossLine.hpp"

QGraphicsCrossLineItem::QGraphicsCrossLineItem(QGraphicsItem *parent) : QGraphicsPathItem(parent) {}

QGraphicsCrossLineItem::QGraphicsCrossLineItem(const QCrossRect &crossRect, QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
    setCrossLine(crossRect);
}

QGraphicsCrossLineItem::QGraphicsCrossLineItem(
    qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
    setCrossLine(x, y, width, height);
}

void QGraphicsCrossLineItem::setCrossLine(const QCrossRect &crossRect)
{
    QPainterPath pathh;
    QPainterPath pathv;

    _crossRect = crossRect;

    if (_type == CrossType::Straight)
    {
        pathh.moveTo(crossRect.left(), crossRect.center().y());
        pathh.lineTo(crossRect.right(), crossRect.center().y());
        pathv.moveTo(crossRect.center().x(), crossRect.top());
        pathv.lineTo(crossRect.center().x(), crossRect.bottom());
    }
    else if (_type == CrossType::Oblique)
    {
        pathh.moveTo(crossRect.topLeft());
        pathh.lineTo(crossRect.bottomRight());
        pathv.moveTo(crossRect.topRight());
        pathv.lineTo(crossRect.bottomLeft());
    }

    pathh.addPath(pathv);
    this->setPath(pathh);
}

void QGraphicsCrossLineItem::setCrossType(CrossType type)
{
    _type = type;
    setCrossLine(_crossRect);
}
