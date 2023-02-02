#pragma once
namespace ImageToolBox
{

class ShapePainter
{
  public:
    enum DrawShapes
    {
        Normal = 0,  ///< 不绘制
        Line,
        Rect,
    };

    ShapePainter(/* args */);
    ~ShapePainter();
};

}  // namespace ImageToolBox
