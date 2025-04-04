#ifndef FRAMEWINDOW_H
#define FRAMEWINDOW_H

#include "CygClientControl_global.h"
#include <QVBoxLayout>
#include "basewidget.h"


class FramelessHelper;
class TitleBar;

class CYG_CLIENTCONTROL_EXPORT FrameWindow : public BaseWidget
{
    Q_OBJECT
public:
    explicit FrameWindow(QWidget *parent = nullptr);

    virtual ~FrameWindow();

    void create();

    /**
     * @brief titleBar  获取标题栏对象
     * @return 返回标题栏对象指针
     */
    TitleBar* titleBar();

public slots:
    virtual void slotMainWndMinimized();
    virtual void slotMainWndMaximized();
    virtual void slotMainWndClose();

signals:

protected:
    FramelessHelper* m_pHelper = nullptr;
    TitleBar*   m_pTitleBar = nullptr;
    QVBoxLayout* m_pLayout = nullptr;
};

#endif // FRAMEWINDOW_H
