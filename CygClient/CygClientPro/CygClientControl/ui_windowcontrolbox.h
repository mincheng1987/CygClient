/********************************************************************************
** Form generated from reading UI file 'windowcontrolbox.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWCONTROLBOX_H
#define UI_WINDOWCONTROLBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowControlBox
{
public:
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *hBoxLayout;
    QPushButton *minBtn;
    QPushButton *expandBtn;
    QPushButton *closeBtn;

    void setupUi(QWidget *WindowControlBox)
    {
        if (WindowControlBox->objectName().isEmpty())
            WindowControlBox->setObjectName("WindowControlBox");
        WindowControlBox->resize(128, 43);
        horizontalLayout = new QHBoxLayout(WindowControlBox);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        hBoxLayout = new QHBoxLayout();
        hBoxLayout->setSpacing(4);
        hBoxLayout->setObjectName("hBoxLayout");
        minBtn = new QPushButton(WindowControlBox);
        minBtn->setObjectName("minBtn");

        hBoxLayout->addWidget(minBtn);

        expandBtn = new QPushButton(WindowControlBox);
        expandBtn->setObjectName("expandBtn");

        hBoxLayout->addWidget(expandBtn);

        closeBtn = new QPushButton(WindowControlBox);
        closeBtn->setObjectName("closeBtn");

        hBoxLayout->addWidget(closeBtn);


        horizontalLayout->addLayout(hBoxLayout);


        retranslateUi(WindowControlBox);

        QMetaObject::connectSlotsByName(WindowControlBox);
    } // setupUi

    void retranslateUi(QWidget *WindowControlBox)
    {
        WindowControlBox->setWindowTitle(QCoreApplication::translate("WindowControlBox", "Form", nullptr));
        minBtn->setText(QString());
        expandBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WindowControlBox: public Ui_WindowControlBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWCONTROLBOX_H
