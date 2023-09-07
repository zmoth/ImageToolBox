/**
 *  @brief 图像信息展示区域
 *  @author moth
 *  @date 2022.07.26
 *  @version v0.1
 *  @note
 *  图像显示类，包含对图像的基本信息，常规操作与展示
 *  图像尺寸，帧率，像素位置，像素颜色
 */
#pragma once

#include <export.h>

#include <QAction>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>

#include "ImageView.hpp"

namespace ImageToolBox {

class IMAGETOOLBOX_EXPORT ImageDisplayArea : public QMainWindow
{
    Q_OBJECT

  public:
    explicit ImageDisplayArea(QWidget *parent = nullptr);
    ~ImageDisplayArea() override = default;

    [[nodiscard]] QPixmap pixmap() const; /* 当前显示图像获取 */
    void setPixmap(QPixmap pix);          /* 图像展示*/

  private Q_SLOTS:

    void _on_changeColorFormat();

    void _loadImage();

    void _saveImage();

  private:
    QColor _imageColor; /* 鼠标位置像素颜色 */

    ImageView *_view;

    /* 按键 */
    QPushButton *_btnCrossLine;
    QPushButton *_btnPixelColor;

    QLabel *_labelImageSize;
    QLabel *_labelPixelCoord;
};

}  // namespace ImageToolBox
