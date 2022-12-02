#include "ImageDisplayArea.h"

#include <QDebug>

#include <QAbstractButton>
#include <QBoxLayout>
#include <QLabel>
#include <QLine>
#include <QMargins>
#include <QMessageBox>
#include <QSpacerItem>
#include <QWheelEvent>
#include <QtMath>
#include <QtWidgets>

#include "ImageItem.h"

/* 析构函数 */
ImageDisplayArea::ImageDisplayArea(QWidget *parent) : QWidget(parent)
{
  this->setContentsMargins(0, 0, 0, 0);

  View = new ImageView();

  btnCrossLine = new QPushButton("+");
  btnPixelColor = new QPushButton("pixel color");
  btnPixelColor->setFlat(true);
  labelPixelCoord = new QLabel("pixel coord");
  labelImageSize = new QLabel("image size");

  QVBoxLayout *mainLayout = new QVBoxLayout();
  QHBoxLayout *btnLayout = new QHBoxLayout();
  mainLayout->setContentsMargins(0, 0, 0, 0);
  btnLayout->setContentsMargins(0, 0, 0, 0);

  btnLayout->addWidget(btnCrossLine);
  //  btnLayout->addSpacerItem(new QSpacerItem(900, 0));
  btnLayout->addWidget(btnPixelColor);
  btnLayout->addWidget(labelPixelCoord);
  btnLayout->addWidget(labelImageSize);

  mainLayout->addWidget(View);
  mainLayout->addLayout(btnLayout);
  this->setLayout(mainLayout);

  btnCrossLine->setToolTip(tr("cross line"));
  btnCrossLine->setCheckable(true);

  connect(btnPixelColor, &QAbstractButton::clicked, this,
          &ImageDisplayArea::on_changeColorFormat);

  connect(btnPixelColor, &QAbstractButton::clicked, this, [=]()
          {
    QClipboard *clip = QApplication::clipboard();
    clip->setText(btnPixelColor->text()); });

  connect(btnCrossLine, &QAbstractButton::toggled, this,
          [=](bool flag)
          { View->openCrossLine(flag); });

  // connect(View->imageItem(), &ImageItem::updateItemPixel, this,
  //         &ImageDisplayArea::on_updatePixal);
}

// ImageDisplayArea::~ImageDisplayArea() {}

// QPixmap ImageDisplayArea::pixmap() const { return View->pixmap(); }

void ImageDisplayArea::showPixmap(QPixmap pix)
{
  if (pix.isNull())
    return;
  View->setImage(pix);
  View->openCrossLine(btnCrossLine->isChecked());
  labelImageSize->setText(QString::number(pix.width()) + "x" +
                          QString::number(pix.height()));
}

void ImageDisplayArea::on_updatePixal(QPoint pos, QColor color)
{
  labelPixelCoord->setText(QString::number(pos.x()) + "," +
                           QString::number(pos.y()));
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
