/********************************************************************
created:2025/03/15
author: min.cheng dk.zhang
purpose:通用的标题栏控件，包括标题名称和右侧最小化最大化和关闭按钮
*********************************************************************/
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "CygClientControl_global.h"
#include "basewidget.h"
#include "windowcontrolbox.h"
#include <QPushButton>

class QLabel;
class QWidget;
class CYG_CLIENTCONTROL_EXPORT TitleBar : public BaseWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

    virtual void createTitleBar(QWidget* ctrlWnd  = nullptr);

    WindowControlBox *windowControlBox(){return m_controlBox;}
    
    /**
     * @brief contentArea 获取内容区域，用于添加自定义控件
     * @return 返回内容区域控件
     */
    QWidget* contentArea() { return m_pContentArea; }

    void setControlFlag(const WindowControlBox::ControlFlag &controlFlag,bool enable = true);

    void setControlFlags(const WindowControlBox::ControlFlags &controlFlags);

    void setWinTitle(const QString& str,Qt::Alignment align = Qt::AlignLeft | Qt::AlignVCenter);

    void setIconName(const QString& iconLabeName="");

    void setIcon(const QIcon &icon);
signals:
    void mainWndMinimized();
    void mainWndMaximized();
    void mainWndClose();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
protected:
    // 最大化/还原
    void onMinimized();
    void onMaximinzed();
    void onClose();

protected:
    QString                     m_iconName = "";
    QPushButton                 *m_pIconItem = nullptr;
    QLabel                     *m_pTitleLabel = nullptr;
    QWidget                    *m_pContentArea = nullptr;    // 内容区域，用于添加自定义控件
    WindowControlBox           *m_controlBox = nullptr;
};
#endif // TITLEBAR_H
