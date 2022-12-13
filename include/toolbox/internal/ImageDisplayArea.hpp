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

#include "Export.hpp"
#include "ImageView.hpp"

#include <QAction>
#include <QGraphicsView>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QWidget>

class PROJECT_DLL_PUBLIC ImageDisplayArea : public QWidget
{
    Q_OBJECT

  public:
    explicit ImageDisplayArea(QWidget *parent = nullptr);
    //  ~ImageDisplayArea();

    QPixmap pixmap() const;       /* 当前显示图像获取 */
    void showPixmap(QPixmap pix); /* 图像展示*/

  private Q_SLOTS:
    /**
     * @brief 更新像素位置和颜色标签
     * @param pos 像素位置
     * @param color 像素颜色
     */
    void on_updatePixal(QPoint pos, QColor color);

    void on_changeColorFormat();

  private:
    QColor imageColor; /* 鼠标位置像素颜色 */

    ImageView *View;

    /* 按键 */
    QPushButton *btnCrossLine;
    QPushButton *btnPixelColor;

    QLabel *labelImageSize;
    QLabel *labelPixelCoord;
};
