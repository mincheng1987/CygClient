#include "mainwindow.h"
#include "StyleSheet.h"
#include "titlebar.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    :FrameWindow(parent)
{
    this->create();
    addSkinToggleButton();
}

MainWindow::~MainWindow()
{

}

void MainWindow::addSkinToggleButton()
{
    QPushButton* skinToggleButton = new QPushButton(this);
    if (CStyleSheet::GetInstance()->getEStyleSheet() == CStyleSheet::DEFAULT) {
        skinToggleButton->setText("切换白色");
    } else {
        skinToggleButton->setText("切换黑色");
    }

    connect(skinToggleButton, &QPushButton::clicked, this, [=]() {
        CStyleSheet::EStyleSheet newStyle = (CStyleSheet::GetInstance()->getEStyleSheet() == CStyleSheet::DEFAULT) ? CStyleSheet::WHITE : CStyleSheet::DEFAULT;
        CStyleSheet::GetInstance()->SetStyle(newStyle);
        skinToggleButton->setText(newStyle == CStyleSheet::DEFAULT ? "切换白色" : "切换黑色");
    });

    QHBoxLayout* contentLayout = qobject_cast<QHBoxLayout*>(this->titleBar()->contentArea()->layout());
    contentLayout->addStretch();
    contentLayout->addWidget(skinToggleButton);
}
