#ifndef BASEDIALOG_H
#define BASEDIALOG_H

#include <QDialog>
#include "baseobject.h"


class BaseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BaseDialog(QWidget *parent = nullptr);

signals:
protected:
    BaseObject baseObject;
};

#endif // BASEDIALOG_H
