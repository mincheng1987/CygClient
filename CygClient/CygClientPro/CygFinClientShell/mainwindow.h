#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "framewindow.h"


// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

class MainWindow : public FrameWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /**
     * @brief addSkinToggleButton 在标题栏内容区域添加切换皮肤按钮
     */
    void addSkinToggleButton();

};
#endif // MAINWINDOW_H
