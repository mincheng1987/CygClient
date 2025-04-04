#include "windowcontrolbox.h"
#include "ui_windowcontrolbox.h"

WindowControlBox::WindowControlBox(QWidget* parent,QWidget* controlWindow)
    :BaseWidget(parent),
      m_isMaximized(false),
      m_pControlWindow(controlWindow),
      ui(new Ui::WindowControlBox),
      m_controlFlags(WindowDefaultFlags)
{
    ui->setupUi(this);
    ui->minBtn->setObjectName("minBtn");
    ui->expandBtn->setObjectName("expandBtn");
    ui->closeBtn->setObjectName("closeBtn");

    ui->minBtn->setFocusPolicy(Qt::NoFocus);
    ui->expandBtn->setFocusPolicy(Qt::NoFocus);
    ui->closeBtn->setFocusPolicy(Qt::NoFocus);

    ui->hBoxLayout->setSpacing(1);
    ui->hBoxLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    connect(ui->minBtn, &QPushButton::clicked, this, &WindowControlBox::OnMinimized);
    connect(ui->expandBtn, &QPushButton::clicked, this, &WindowControlBox::OnMaximinzed);
    connect(ui->closeBtn, &QPushButton::released, this, &WindowControlBox::OnClose);
    setControlFlags(m_controlFlags);
    updateControlFlags();
}

WindowControlBox::~WindowControlBox()
{
	if (ui)
	{
		delete ui;
		ui = nullptr;
	}
}

void WindowControlBox::SwitchExpandOrNarrow()
{
    //SwitchExpandOrNarrow(m_isMaximized);
    OnMaximinzed();
}

void WindowControlBox::setControlFlag(const ControlFlag &controlFlag,bool enable)
{
    if(enable)
        m_controlFlags |= controlFlag;
    else
        m_controlFlags &= ~controlFlag;

    updateControlFlags();
}
void WindowControlBox::setControlFlags(const ControlFlags &controlFlags)
{
    m_controlFlags = controlFlags;
    updateControlFlags();
}

void WindowControlBox::SwitchExpandOrNarrow(bool isMaximized)
{
    if(isMaximized)
        ui->expandBtn->setObjectName("expandBtn");
    else
        ui->expandBtn->setObjectName("narrowBtn");

    ui->expandBtn->setStyle(ui->expandBtn->style());
}

void WindowControlBox::updateControlFlags()
{
    ui->minBtn->setVisible(m_controlFlags&WindowMinimizeButton);
    ui->expandBtn->setVisible(m_controlFlags&WindowMaximizeButton);
    ui->closeBtn->setVisible(m_controlFlags&WindowCloseButton);
}

void WindowControlBox::OnMinimized()
{
    if(m_pControlWindow)
    {
        m_pControlWindow->showMinimized();
    }
    emit mainWndMinimized();
}

void WindowControlBox::OnMaximinzed()
{
    if(m_pControlWindow)
    {
        if(m_isMaximized)
        {
            m_isMaximized = false;
            m_pControlWindow->showNormal();
        }
        else
        {
            m_isMaximized = true;
            m_pControlWindow->showMaximized();
            emit mainWndMaximized();
        }
    }
    SwitchExpandOrNarrow(m_isMaximized);
}

void WindowControlBox::onRestoreWindow()
{
    if(m_isMaximized)
    {
        m_pControlWindow->showMaximized();
    }
    else
    {
       m_pControlWindow->showNormal();
    }
}

void WindowControlBox::updateMaximize(bool isMaximized)
{
    m_isMaximized = isMaximized;
    SwitchExpandOrNarrow(!m_isMaximized);
}

void WindowControlBox::OnClose()
{
    if(m_pControlWindow){
        emit mainWndClose();
        m_pControlWindow->close();
    }

}

QWidget *WindowControlBox::getCtrlWnd()
{
    return m_pControlWindow;
}
