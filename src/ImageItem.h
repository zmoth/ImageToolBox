/**
 *  @brief 图像类
 *  @author moth
 *  @date 2022.08.05
 *  @version v0.1
 *  @note
 */
#pragma once

#ifndef IMAGE_ITEM_H
#define IMAGE_ITEM_H

#include <QColor>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPointF>

class ImageItem : public QObject, public QGraphicsPixmapItem
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

#endif // IMAGE_ITEM_H
