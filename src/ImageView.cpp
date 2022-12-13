#include "ImageView.hpp"

#include "BasicImageScene.hpp"
#include "shapes/CrossLine.hpp"

#include <QDebug>
#include <QEvent>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPoint>
#include <QPointF>
#include <QWheelEvent>
#include <QtMath>

ImageView::ImageView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setRenderHint(QPainter::Antialiasing);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏水平条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 隐藏竖条

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    this->setScene(std::make_unique<BasicImageScene>(new BasicImageScene()));

    setScaleRange(0.1, 10);
}

ImageView::~ImageView()
{
    delete crossLine;
}

QPixmap ImageView::image() const
{
    return _scene->image();
}

void ImageView::setImage(QPixmap pix)
{
    if (pix.isNull())
        return;
    _scene->setImage(pix);
    centerScene();
    // scene()->setSceneRect(pix.rect());
    // image->setPixmap(pix);
}

void ImageView::setScene(std::unique_ptr<BasicImageScene> scene)
{
    _scene = std::move(scene);
    QGraphicsView::setScene(_scene.get());

    // image = new ImageItem();
    // scene->addItem(image);

    /* 十字中心线 */
    crossLine = new QGraphicsCrossLineItem(_scene->sceneRect());
    QPen pen(Qt::green);
    pen.setWidth(1);
    crossLine->setPen(pen);
    _scene->addItem(crossLine);
    crossLine->setVisible(false);
}

void ImageView::centerScene()
{
    if (scene())
    {
        scene()->setSceneRect(QRectF());

        QRectF sceneRect = scene()->sceneRect();

        if (sceneRect.width() > this->rect().width() || sceneRect.height() > this->rect().height())
        {
            fitInView(sceneRect, Qt::KeepAspectRatio);
        }

        centerOn(sceneRect.center());
    }
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();

    if (delta.y() == 0)
    {
        event->ignore();
        return;
    }

    double const d = delta.y() / std::abs(delta.y());

    if (d > 0.0)
        scaleUp();
    else
        scaleDown();
}

double ImageView::getScale() const
{
    return transform().m11();
}

void ImageView::setScaleRange(double minimum, double maximum)
{
    if (minimum <= maximum)
        _scaleRange = {minimum < 0 ? 0 : minimum, maximum < 0 ? 0 : maximum};
    else
        _scaleRange = {maximum < 0 ? 0 : maximum, minimum < 0 ? 0 : minimum};

    this->setupScale(transform().m11());
}

void ImageView::setScaleRange(ScaleRange range)
{
    setScaleRange(range.minimum, range.maximum);
}

void ImageView::scaleUp()
{
    double const step = 1.2;
    double const factor = std::pow(step, 1.0);

    if (_scaleRange.maximum > 0)
    {
        QTransform t = transform();
        t.scale(factor, factor);
        if (t.m11() >= _scaleRange.maximum)
        {
            setupScale(t.m11());
            return;
        }
    }

    scale(factor, factor);
    Q_EMIT scaleChanged(transform().m11());
}

void ImageView::scaleDown()
{
    double const step = 1.2;
    double const factor = std::pow(step, -1.0);

    if (_scaleRange.minimum > 0)
    {
        QTransform t = transform();
        t.scale(factor, factor);
        if (t.m11() <= _scaleRange.minimum)
        {
            setupScale(t.m11());
            return;
        }
    }

    scale(factor, factor);
    Q_EMIT scaleChanged(transform().m11());
}

void ImageView::setupScale(double scale)
{
    if (scale < _scaleRange.minimum)
        scale = _scaleRange.minimum;
    else if (scale > _scaleRange.maximum) // && _scaleRange.maximum > 0
        scale = _scaleRange.maximum;

    if (scale <= 0)
        return;

    if (scale == transform().m11())
        return;

    QTransform matrix;
    matrix.scale(scale, scale);
    this->setTransform(matrix, false);
    Q_EMIT scaleChanged(scale);
}

void ImageView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Shift :
            setDragMode(QGraphicsView::RubberBandDrag);
            break;

        case Qt::Key_Control :
            setDragMode(QGraphicsView::RubberBandDrag);
            // _drawStatus = DrawShapes::Line;
            break;

        default :
            break;
    }

    QGraphicsView::keyPressEvent(event);
}

void ImageView::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Shift :
            setDragMode(QGraphicsView::ScrollHandDrag);
            break;

        case Qt::Key_Control :
            setDragMode(QGraphicsView::ScrollHandDrag);
            // _drawStatus = DrawShapes::Normal;
            break;

        default :
            break;
    }
    QGraphicsView::keyReleaseEvent(event);
}

void ImageView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton)
    {
        this->centerScene();
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // // 当图形处于绘制状态时
        // if (_drawStatus != DrawShapes::Normal)
        // {
        //   // 记录鼠标按下的点
        //   _clickPos = mapToScene(event->pos());
        // }
    }
    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    // if (_drawStatus != DrawShapes::Normal)
    // {
    //   // this->drawShape(_drawStatus, m_vetPt, e->scenePos());
    // }
    QGraphicsView::mouseMoveEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void ImageView::resizeEvent(QResizeEvent *event)
{
    if (event->oldSize().height() == -1 || event->oldSize().width() == -1)
        return;

    if (event->size().height() != event->oldSize().height())
    {
    }
}

void ImageView::openCrossLine(bool flag)
{
    if (flag == true)
    {
        crossLine->setCrossLine(sceneRect());
        crossLine->setVisible(true);
    }
    else
    {
        crossLine->setVisible(false);
    }
}

void ImageView::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
    scene()->setSceneRect(this->rect());
    centerScene();
}
