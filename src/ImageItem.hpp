#pragma once

#include <QColor>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPointF>

class ImageItem
    : public QObject
    , public QGraphicsPixmapItem
{
    Q_OBJECT
  public:
    explicit ImageItem();
    ~ImageItem();

  protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

  Q_SIGNALS:
    void updateItemPixel(QPoint pos, QColor color); /* 更新像素信息的信号 */

  private:
};
