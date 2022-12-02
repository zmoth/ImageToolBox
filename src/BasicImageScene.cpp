#include "BasicImageScene.h"

#include <QtMath>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

BasicImageScene::BasicImageScene(QObject *parent)
    : QGraphicsScene(parent)
{
    _imageItem = new QGraphicsPixmapItem();
    this->addItem(_imageItem);
}

BasicImageScene::~BasicImageScene()
{
    if (_imageItem)
        delete _imageItem;
}

void BasicImageScene::setImage(QPixmap pix)
{
    _imageItem->setPixmap(pix);
    setSceneRect(pix.rect());
}

void BasicImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    QPoint pos = mouseEvent->scenePos().toPoint();
    if (_imageItem->pixmap().rect().contains(pos, false))
    {
        // qDebug() << pos + QPoint(1, 1) << _imageItem->pixmap().toImage().pixelColor(pos);
        Q_EMIT updatePixelPos(pos + QPoint(1, 1)); // 2448x2048 [1~2448]
        Q_EMIT updatePixelColor(_imageItem->pixmap().toImage().pixelColor(pos));
    }
}