/**
 *  @brief 十字中心线
 *  @author moth
 *  @date 2022.08.01
 *  @version 0.0.1
 *  @note
 */
#pragma once

#include <QGraphicsPathItem>

namespace ImageToolBox
{

class QGraphicsCrossLineItem : public QGraphicsPathItem
{
  public:
    using QCrossRect = QRectF;

    enum CrossType
    {
        Straight,
        Oblique,
    };

    explicit QGraphicsCrossLineItem(QGraphicsItem *parent = nullptr);
    QGraphicsCrossLineItem(const QCrossRect &crossRect, QGraphicsItem *parent = nullptr);
    QGraphicsCrossLineItem(qreal x,
                           qreal y,
                           qreal width,
                           qreal height,
                           QGraphicsItem *parent = nullptr);

    void setCrossLine(const QCrossRect &crossline);

    inline void setCrossLine(qreal x, qreal y, qreal width, qreal height)
    {
        setCrossLine(QCrossRect(x, y, width, height));
    }

    void setCrossType(CrossType type);

  private:
    CrossType _type = CrossType::Straight;
    QCrossRect _crossRect;
};

}  // namespace ImageToolBox
