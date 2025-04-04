#include "titlebar.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QToolButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>

#include "windowcontrolbox.h"

TitleBar::TitleBar(QWidget *parent)
    : BaseWidget(parent),m_pContentArea(nullptr),m_controlBox(0)
{
}


TitleBar::~TitleBar()
{

}

void TitleBar::createTitleBar(QWidget* ctrlWnd)
{
    m_pIconItem = new QPushButton(this);
    m_pIconItem->setObjectName(m_iconName);
    if(m_iconName.isEmpty())
        m_pIconItem->hide();
    m_pTitleLabel = new QLabel(QStringLiteral("untitled"),this);
    m_pTitleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pTitleLabel->setObjectName("titleName");
    
    // 创建内容区域
    m_pContentArea = new QWidget(this);
    m_pContentArea->setObjectName("contentArea");
    QHBoxLayout* contentLayout = new QHBoxLayout(m_pContentArea);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);
    m_pContentArea->setLayout(contentLayout);
    
    if(!ctrlWnd)
        ctrlWnd = (QWidget*)this->parent();
    m_controlBox   =  new WindowControlBox(this,ctrlWnd);
    QHBoxLayout *titleLayout = new  QHBoxLayout;
    titleLayout->setContentsMargins(0,0,0,0);
    titleLayout->setSpacing(0);
    //titleLayout->addSpacing(10);
    titleLayout->addWidget(m_pIconItem,0,Qt::AlignVCenter);
    titleLayout->addSpacing(8);
    titleLayout->addWidget(m_pTitleLabel,6);
    titleLayout->addWidget(m_pContentArea, 1);
    titleLayout->addWidget(m_controlBox,0,Qt::AlignRight);
    this->setLayout(titleLayout);
}

void TitleBar::setControlFlag(const WindowControlBox::ControlFlag &controlFlag,bool enable)
{
    m_controlBox->setControlFlag(controlFlag,enable);
}

void TitleBar::setControlFlags(const WindowControlBox::ControlFlags &controlFlags)
{
    m_controlBox->setControlFlags(controlFlags);
}
void TitleBar::setWinTitle(const QString &str,Qt::Alignment align)
{
    m_pTitleLabel->setText(str);
    m_pTitleLabel->setAlignment(align);
}

void TitleBar::setIconName(const QString &iconLabeName)
{
    m_iconName = iconLabeName;
    if(m_pIconItem)
    {
        m_pIconItem->style()->unpolish(m_pIconItem);
        m_pIconItem->setObjectName(m_iconName);
        m_pIconItem->style()->polish(m_pIconItem);
        m_pIconItem->show();
    }
}

void TitleBar::setIcon(const QIcon &icon)
{
    if(m_pIconItem)
    {
        m_pIconItem->style()->unpolish(m_pIconItem);
        m_pIconItem->setObjectName("");
        m_pIconItem->setStyleSheet("background: transparent;");
        m_pIconItem->style()->polish(m_pIconItem);
        m_pIconItem->setIcon(icon);
        m_pIconItem->show();
    }
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
        }
        break;
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            // m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
        }
        break;
    }
    default:
        break;
    }
    return BaseWidget::eventFilter(obj, event);
}

void TitleBar::onMinimized()
{
    emit mainWndMinimized();
}

void TitleBar::onMaximinzed()
{
    emit mainWndMaximized();
}

void TitleBar::onClose()
{
    emit mainWndClose();
}

