#pragma once

#include <QtWidgets/QGraphicsScene>

class BasicImageScene : public QGraphicsScene
{
    Q_OBJECT
  public:
    BasicImageScene(QObject *parent = nullptr);
    ~BasicImageScene();
};
