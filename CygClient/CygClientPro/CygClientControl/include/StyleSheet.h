#ifndef CSTYLESHEET_H
#define CSTYLESHEET_H

#include <QObject>
#include <QMap>
#include "CygClientControl_global.h"


class CYG_CLIENTCONTROL_EXPORT CStyleSheet : public QObject
{
    Q_OBJECT
public:
    enum EStyleSheet
    {
        DEFAULT = 0,
        WHITE,
        StyleSheetUnknown,
    };

    static CStyleSheet* GetInstance();
    ~CStyleSheet();
    void SetStyle(EStyleSheet style);

    //切换皮肤显示，但不设置当前皮肤标志，用于特殊处理个股页面在白版时的皮肤
    void ChangeStyle(EStyleSheet style);

    EStyleSheet getEStyleSheet();

signals:
    void sigStyleChanged();

private:
    explicit CStyleSheet(QObject *parent = 0);
    QString loadStyle(const QString &filePath);

private:
    EStyleSheet m_styleSheet = StyleSheetUnknown;
    QString m_current_theme="";
    QString m_theme_default_file="";
    QString m_theme_white_file="";
    QMap<EStyleSheet,QString> m_styleMap;
};

#define DECLARE_QPROPERTY(TYPE, NAME)\
TYPE NAME() const { return _m_##NAME; }\
void set_##NAME(const TYPE& value) { _m_##NAME = value; }\
TYPE _m_##NAME = TYPE();

#endif // CSTYLESHEET_H
