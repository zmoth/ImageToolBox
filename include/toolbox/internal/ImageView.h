/**
 *  @brief 图像显示
 *  @author moth
 *  @date 2022.08.05
 *  @version v0.1
 *  @note
 */
#pragma once

#include <QtWidgets/QGraphicsView>
// #include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "Export.hpp"

class BasicImageScene;
class ImageItem;
class QGraphicsCrossLineItem;

class PROJECT_DLL_PUBLIC ImageView : public QGraphicsView
{
  Q_OBJECT

public:
  struct ScaleRange
  {
    double minimum = 0;
    double maximum = 0;
  };

  enum DrawShapes
  {
    Normal = 0, ///< 不绘制
    Line,
    Rect,
  };

  explicit ImageView(QWidget *parent = nullptr);
  ImageView(BasicImageScene *scene, QWidget *parent = nullptr);
  ~ImageView();

  ImageView(const ImageView &) = delete;
  ImageView operator=(const ImageView &) = delete;

  ImageItem *imageItem();
  QPixmap pixmap() const;
  void addPixmap(QPixmap pix);
  void openCrossLine(bool flag = false);

  void setScene(BasicImageScene *scene);

  void centerScene(); ///< 居中显示

  /// @brief max=0/min=0 indicates infinite zoom in/out
  void setScaleRange(double minimum = 0, double maximum = 0);
  void setScaleRange(ScaleRange range);
  double getScale() const;

public Q_SLOTS:
  void scaleUp();
  void scaleDown();
  void setupScale(double scale);

Q_SIGNALS:
  void scaleChanged(double scale);

protected:
  void wheelEvent(QWheelEvent *event) override; ///< 鼠标滚轮，放大缩小
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override; ///< 鼠标中键双击：填充整个屏幕
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void resizeEvent(QResizeEvent *event) override; // 图像显示窗口大小改变
  void showEvent(QShowEvent *event) override;     // show()

protected:
  BasicImageScene *imageScene();

private:
  void drawShape(DrawShapes shape, std::vector<QPointF> vetPt, QPointF ptCurrent);

private:
  QGraphicsCrossLineItem *crossLine;
  ImageItem *image;
  QGraphicsLineItem *line;

  DrawShapes _drawStatus = DrawShapes::Normal;
  QPointF _clickPos;
  ScaleRange _scaleRange;
};
