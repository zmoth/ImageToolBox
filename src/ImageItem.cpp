#include "ImageItem.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QtMath>

namespace ImageToolBox {

ImageItem::ImageItem()
{
    setAcceptHoverEvents(true);
}

void ImageItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    static QPoint pos;
    pos.setX(qCeil(event->scenePos().x()));  // 舍弃小数点后的数值
    pos.setY(qCeil(event->scenePos().y()));
    if (pos.x() <= 0 || pos.y() <= 0) {
        return;
    }
    Q_EMIT updateItemPixel(pos, pixmap().toImage().pixelColor(pos - QPoint(1, 1)));
    QGraphicsItem::hoverMoveEvent(event);
}

}  // namespace ImageToolBox
