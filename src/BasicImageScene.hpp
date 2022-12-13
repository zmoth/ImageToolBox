#pragma once

#include <QtWidgets/QGraphicsScene>
#include <QEvent>

class ImageItem;
/**
 * @brief 图片画布
 *
 * 一个Scene包含一个图片
 *
 */
class BasicImageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BasicImageScene(QObject *parent = nullptr);
    ~BasicImageScene();

    void setImage(QPixmap pix);

Q_SIGNALS:
    void updatePixelPos(QPoint pos);
    void updatePixelColor(QColor color);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    QGraphicsPixmapItem *_imageItem = nullptr;
};
