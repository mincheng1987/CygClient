#ifndef FILEPATHHELPER_H
#define FILEPATHHELPER_H

#include <QObject>
#include "CygClientCore_global.h"


class CYG_CLIENTCORE_EXPORT FilePathHelper : public QObject
{
    Q_OBJECT
public:
    explicit FilePathHelper(QObject *parent = nullptr);

    static QString getExecutableDirectory();

signals:
};

#endif // FILEPATHHELPER_H
