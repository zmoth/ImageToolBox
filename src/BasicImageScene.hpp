#pragma once

#include <QEvent>
#include <QtWidgets/QGraphicsScene>

namespace ImageToolBox
{

class ImageItem;

/**
 * @brief 图片画布
 *
 * 一个Scene包含一个图片
 */
class BasicImageScene : public QGraphicsScene
{
    Q_OBJECT
  public:
    explicit BasicImageScene(QObject *parent = nullptr);
    ~BasicImageScene();

    QPixmap image() const;
    void setImage(QPixmap pix);

  Q_SIGNALS:
    void updatePixelPos(QPoint pos);
    void updatePixelColor(QColor color);

  protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

  private:
    QGraphicsPixmapItem *_imageItem = nullptr;
};

}  // namespace ImageToolBox
