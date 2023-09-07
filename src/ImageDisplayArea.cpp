#include "ImageDisplayArea.hpp"

#include <QAbstractButton>
#include <QBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QLine>
#include <QMargins>
#include <QMessageBox>
#include <QSpacerItem>
#include <QtMath>
#include <QtWidgets>
#include <QWheelEvent>

#include "BasicImageScene.hpp"

namespace ImageToolBox {

ImageDisplayArea::ImageDisplayArea(QWidget *parent) : QMainWindow(parent)
{
    this->setContentsMargins(0, 0, 0, 0);

    // 菜单-文件
    auto *menuFile = new QMenu(tr("File"));
    menuBar()->addMenu(menuFile);

    QAction *action;

    action = new QAction(tr("Open"), this);
    connect(action, &QAction::triggered, this, &ImageDisplayArea::_loadImage);
    menuFile->addAction(action);

    action = new QAction(tr("Save"), this);
    connect(action, &QAction::triggered, this, &ImageDisplayArea::_saveImage);
    menuFile->addAction(action);

    _view = new ImageView();
    this->setCentralWidget(_view);
    auto *s = dynamic_cast<BasicImageScene *>(_view->scene());
    connect(s, &BasicImageScene::updatePixelPos, this,
            [this](QPoint pos) { _labelPixelCoord->setText(tr("%1,%2").arg(pos.x(), 5).arg(pos.y(), 5)); });

    connect(s, &BasicImageScene::updatePixelColor, this, [this](QColor color) {
        _imageColor = color;
        if (_btnPixelColor->text().left(1) != "(") {
            _btnPixelColor->setText(color.name(QColor::HexArgb));
        } else {
            _btnPixelColor->setText(tr("(%1,%2,%3,%4)")
                                        .arg(color.alpha(), 3)
                                        .arg(color.red(), 3)
                                        .arg(color.green(), 3)
                                        .arg(color.blue(), 3));
        }
    });

    _btnCrossLine = new QPushButton("+");
    _btnCrossLine->setToolTip(tr("cross line"));
    _btnCrossLine->setCheckable(true);
    statusBar()->addWidget(_btnCrossLine);

    _btnPixelColor = new QPushButton("pixel color");
    _btnPixelColor->setFixedWidth(120);
    _btnPixelColor->setFlat(true);
    statusBar()->addPermanentWidget(_btnPixelColor);

    _labelPixelCoord = new QLabel("pixel coord");
    _labelPixelCoord->setFixedWidth(100);
    _labelPixelCoord->setAlignment(Qt::AlignCenter);
    statusBar()->addPermanentWidget(_labelPixelCoord);

    _labelImageSize = new QLabel("image size");
    _labelImageSize->setAlignment(Qt::AlignCenter);
    statusBar()->addPermanentWidget(_labelImageSize);

    connect(_btnPixelColor, &QAbstractButton::clicked, this, &ImageDisplayArea::_on_changeColorFormat);

    connect(_btnPixelColor, &QAbstractButton::clicked, this, [=]() {
        QClipboard *clip = QApplication::clipboard();
        clip->setText(_btnPixelColor->text());
    });

    connect(_btnCrossLine, &QAbstractButton::toggled, this, [=](bool flag) { _view->openCrossLine(flag); });
}

void ImageDisplayArea::_loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open Image"), QDir::homePath(),
                                                    tr("Image Files (*.png *.jpg *.bmp)"));

    if (fileName.isEmpty()) {
        return;
    }

    QPixmap img = QPixmap(fileName);

    if (img.isNull()) {
        return;
    }

    this->setPixmap(img);
    _view->centerScene();
}

void ImageDisplayArea::_saveImage()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "",
                                                    tr("Image Files (*.png *.jpg *.bmp)"));  // 选择路径
    if (fileName.isEmpty()) {
        return;
    }

    QImage img2 = _view->image().toImage();

    if (!(img2.save(fileName)))  // 保存图像
    {
        QMessageBox::information(this, tr("Failed to save the image"), tr("Failed to save the image!"));
        return;
    }
}

QPixmap ImageDisplayArea::pixmap() const
{
    return _view->image();
}

void ImageDisplayArea::setPixmap(QPixmap pix)
{
    if (pix.isNull()) {
        return;
    }

    _view->setImage(pix);
    _view->openCrossLine(_btnCrossLine->isChecked());
    _labelImageSize->setText(QString::number(pix.width()) + "x" + QString::number(pix.height()));
}

void ImageDisplayArea::_on_changeColorFormat()
{
    if (_btnPixelColor->text().left(1) == "(") {
        _btnPixelColor->setText(_imageColor.name(QColor::HexArgb));
    } else {
        _btnPixelColor->setText(tr("(%1,%2,%3,%4)")
                                    .arg(_imageColor.alpha(), 3)
                                    .arg(_imageColor.red(), 3)
                                    .arg(_imageColor.green(), 3)
                                    .arg(_imageColor.blue(), 3));
    }
}

}  // namespace ImageToolBox
