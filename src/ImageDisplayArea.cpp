#include "ImageDisplayArea.hpp"

#include "ImageItem.hpp"

#include <QAbstractButton>
#include <QBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QLine>
#include <QMargins>
#include <QMessageBox>
#include <QSpacerItem>
#include <QWheelEvent>
#include <QtMath>
#include <QtWidgets>

/* 析构函数 */
ImageDisplayArea::ImageDisplayArea(QWidget *parent) : QMainWindow(parent)
{
    this->setContentsMargins(0, 0, 0, 0);

    // 菜单-文件
    QMenu *_menuFile = new QMenu(tr("File"));
    menuBar()->addMenu(_menuFile);

    QAction *_action;

    _action = new QAction(tr("Open"), this);
    connect(_action, &QAction::triggered, this, &ImageDisplayArea::loadImage);
    _menuFile->addAction(_action);

    _action = new QAction(tr("Save"), this);
    connect(_action, &QAction::triggered, this, &ImageDisplayArea::saveImage);
    _menuFile->addAction(_action);

    View = new ImageView();
    this->setCentralWidget(View);

    btnCrossLine = new QPushButton("+");
    btnCrossLine->setToolTip(tr("cross line"));
    btnCrossLine->setCheckable(true);
    statusBar()->addWidget(btnCrossLine);

    btnPixelColor = new QPushButton("pixel color");
    btnPixelColor->setFlat(true);
    statusBar()->addWidget(btnPixelColor);

    labelPixelCoord = new QLabel("pixel coord");
    statusBar()->addWidget(labelPixelCoord);

    labelImageSize = new QLabel("image size");
    statusBar()->addWidget(labelImageSize);

    connect(btnPixelColor, &QAbstractButton::clicked, this,
            &ImageDisplayArea::on_changeColorFormat);

    connect(btnPixelColor, &QAbstractButton::clicked, this,
            [=]()
            {
                QClipboard *clip = QApplication::clipboard();
                clip->setText(btnPixelColor->text());
            });

    connect(btnCrossLine, &QAbstractButton::toggled, this,
            [=](bool flag) { View->openCrossLine(flag); });
}

ImageDisplayArea::~ImageDisplayArea() {}

void ImageDisplayArea::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open Image"), QDir::homePath(),
                                                    tr("Image Files (*.png *.jpg *.bmp)"));

    if (fileName.isEmpty())
        return;

    QPixmap img = QPixmap(fileName);

    if (img.isNull())
        return;

    this->setPixmap(img);
}

void ImageDisplayArea::saveImage()
{
    QString fileName =
        QFileDialog::getSaveFileName(this, tr("Save Image"), "",
                                     tr("Image Files (*.png *.jpg *.bmp)")); // 选择路径
    if (fileName.isEmpty())
        return;

    QImage img2 = View->image().toImage();

    if (!(img2.save(fileName))) // 保存图像
    {
        QMessageBox::information(this, tr("Failed to save the image"),
                                 tr("Failed to save the image!"));
        return;
    }
}

QPixmap ImageDisplayArea::pixmap() const
{
    return View->image();
}

void ImageDisplayArea::setPixmap(QPixmap pix)
{
    if (pix.isNull())
        return;

    View->setImage(pix);
    View->openCrossLine(btnCrossLine->isChecked());
    labelImageSize->setText(QString::number(pix.width()) + "x" + QString::number(pix.height()));
}

void ImageDisplayArea::on_updatePixal(QPoint pos, QColor color)
{
    labelPixelCoord->setText(QString::number(pos.x()) + "," + QString::number(pos.y()));
    //  btnPixelColor->setStyleSheet("color:" + color.name()); // 改变字体颜色
    imageColor = color;
    if (btnPixelColor->text().left(1) != "(")
    {
        btnPixelColor->setText(color.name());
    }
    else
    {
        btnPixelColor->setText("(" + QString::number(color.red()) + "," +
                               QString::number(color.green()) + "," +
                               QString::number(color.blue()) + ")");
    }
}

void ImageDisplayArea::on_changeColorFormat()
{
    if (btnPixelColor->text().left(1) == "(")
    {
        btnPixelColor->setToolTip(tr("HEX"));
        btnPixelColor->setText(imageColor.name());
    }
    else
    {
        btnPixelColor->setToolTip(tr("RGB"));
        btnPixelColor->setText("(" + QString::number(imageColor.red()) + "," +
                               QString::number(imageColor.green()) + "," +
                               QString::number(imageColor.blue()) + ")");
    }
}
