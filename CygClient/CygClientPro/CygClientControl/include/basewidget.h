#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
#include "CygClientControl_global.h"
#include "baseobject.h"


class CYG_CLIENTCONTROL_EXPORT BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);
    virtual ~BaseWidget();

signals:

protected:
    BaseObject baseObject;
};

#endif // BASEWIDGET_H
