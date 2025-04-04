#include "framewindow.h"
#include "framelesshelper.h"
#include "titlebar.h"


FrameWindow::FrameWindow(QWidget *parent)
    : BaseWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    this->setMouseTracking(true); //界面拉伸需要这个属性
    m_pHelper = new FramelessHelper(this);
    m_pTitleBar = new TitleBar(this);
    m_pTitleBar->createTitleBar();
    m_pLayout = new QVBoxLayout();
    installEventFilter(m_pTitleBar);
}

FrameWindow::~FrameWindow()
{
    m_pHelper->removeFrom(this);
    m_pHelper->deleteLater();
    m_pTitleBar->deleteLater();
    m_pLayout->deleteLater();
    m_pHelper = nullptr;
    m_pTitleBar = nullptr;
    m_pLayout = nullptr;
}

void FrameWindow::create()
{
    resize(800, 600);
    m_pLayout->addWidget(m_pTitleBar);
    m_pLayout->addStretch();
    m_pLayout->setSpacing(0);
    m_pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_pLayout);

    m_pHelper->activateOn(this);  //激活当前窗体
    m_pHelper->setTitleHeight(m_pTitleBar->height());  //设置窗体的标题栏高度
    m_pHelper->setWidgetMovable(true);  //设置窗体可移动
    m_pHelper->setWidgetResizable(true);  //设置窗体可缩放
    connect(m_pTitleBar, &TitleBar::mainWndClose, this, &FrameWindow::slotMainWndClose);
    connect(m_pTitleBar, &TitleBar::mainWndMinimized, this, &FrameWindow::slotMainWndMinimized);
    connect(m_pTitleBar, &TitleBar::mainWndMaximized, this, &FrameWindow::slotMainWndMaximized);

}

void FrameWindow::slotMainWndMinimized()
{

}

void FrameWindow::slotMainWndMaximized()
{

}

void FrameWindow::slotMainWndClose()
{

}

/**
 * @brief FrameWindow::titleBar  获取标题栏对象
 * @return 返回标题栏对象指针
 */
TitleBar* FrameWindow::titleBar() {
    return m_pTitleBar;
}
