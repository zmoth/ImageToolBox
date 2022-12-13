#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);

  private:
    void createWidget();    // 创建窗口
    void createMenuBar();   // 创建菜单栏
    void createStatusBar(); // 创建状态栏
};
