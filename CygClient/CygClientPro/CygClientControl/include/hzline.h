/********************************************************************
created: 2025/03/12
author: min.cheng
purpose:界面布局分割线，支持水平和垂直两种方式
*********************************************************************/
#ifndef HZLINE_H
#define HZLINE_H

#include "CygClientControl_global.h"
#include <QFrame>

class CYG_CLIENTCONTROL_EXPORT HZLine : public QFrame
{
    Q_OBJECT
public:
    HZLine(QWidget *parent = 0,QString style="");
    HZLine(Qt::Orientation orientation ,QWidget *parent = 0,QString style="");
    ~HZLine(){}

    void setHZlineWidth(const int &lineWidth);

private:
    void createLine();

private:
    Qt::Orientation m_orientation;
    int   m_hzLineWidth=1;
};

#endif // HZLINE_H
