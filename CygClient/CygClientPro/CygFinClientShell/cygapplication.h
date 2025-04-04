#ifndef CYGAPPLICATION_H
#define CYGAPPLICATION_H

/********************************************************************
created:
author: min.cheng
purpose: 用于程序初始化，代替在Main函数中处理代码
*********************************************************************/
#include <QApplication>
#include <memory>
#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>



class CygApplication:public QObject
{
    Q_OBJECT
public:
    CygApplication(QObject *parent=Q_NULLPTR);

    ~CygApplication();

    int initInstance(int argc, char *argv[]);

protected slots:
    void onExitInstance();
protected:
    int onInitInstance(QApplication& app);
    QApplication * m_app;
};

#endif // CYGAPPLICATION_H
