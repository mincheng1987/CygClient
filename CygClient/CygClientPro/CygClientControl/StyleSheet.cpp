#include "StyleSheet.h"
#include <QApplication>
#include <QDir>
#include <QFileInfoList>
#include <QtCore>
#include <QtGui>
#include "filepathhelper.h"

CStyleSheet* CStyleSheet::GetInstance()
{
    static CStyleSheet styleInstance;
    return &styleInstance;
}

CStyleSheet::CStyleSheet(QObject *parent)
    : QObject(parent)
{
    QString strProject = FilePathHelper::getExecutableDirectory();
    m_theme_default_file = QString("%1theme-black.rcc").arg(strProject);
    m_theme_white_file = QString("%1theme-white.rcc").arg(strProject);
}


CStyleSheet::~CStyleSheet()
{
}

void CStyleSheet::SetStyle(EStyleSheet style)
{
    if(m_styleSheet == style)
        return;
    bool ret = false;
    if (!m_current_theme.isEmpty())
    {
        ret = QResource::unregisterResource(m_current_theme);
        qDebug() << "unregisterResource:" << m_current_theme << ret;
    }
    switch(style)
    {
        case DEFAULT:
        {
            m_current_theme = m_theme_default_file;
            break;

        }
        case WHITE:
        {
            m_current_theme = m_theme_white_file;
            break;
        }
        default:
            break;
    }
    if(m_current_theme.isEmpty())
        return;
    m_styleSheet = style;
    QString strStyle = "";
    ret = QResource::registerResource(m_current_theme);
    if(ret)
    {
        if(!m_styleMap.contains(m_styleSheet))
        {
            strStyle = loadStyle(":/qss");
            m_styleMap[m_styleSheet] = strStyle;
        }
        qApp->setStyleSheet(m_styleMap[m_styleSheet]);
        // #ifdef Q_OS_MAC
        // qApp->setStyle("fusion");
        // #endif
    }
    qDebug() << "registerResource:" << m_current_theme << ret;
    emit sigStyleChanged();
}

void CStyleSheet::ChangeStyle(CStyleSheet::EStyleSheet style)
{
    bool ret = false;
    QString lasttheme = m_current_theme;
    if(DEFAULT == style)
    {
        if(m_current_theme == m_theme_default_file)
            return;
        m_current_theme = m_theme_default_file;
    }else if(WHITE == style)
    {
        if(m_current_theme == m_theme_white_file)
            return;
         m_current_theme = m_theme_white_file;
    }
    if(m_current_theme.isEmpty())
        return;
    if (!lasttheme.isEmpty())
    {
        ret = QResource::unregisterResource(lasttheme);
        qDebug() << "unregisterResource:" << lasttheme << ret;
    }

    QString strStyle = "";
    ret = QResource::registerResource(m_current_theme);
    if(ret)
    {
        if(!m_styleMap.contains(style))
        {
            strStyle = loadStyle(":/qss");
            m_styleMap[style] = strStyle;
        }
        qApp->setStyleSheet(m_styleMap[style]);
        // #ifdef Q_OS_MAC
        // qApp->setStyle("fusion");
        // #endif
    }
    qDebug() << "registerResource:" << m_current_theme << ret;
    emit sigStyleChanged();
}

CStyleSheet::EStyleSheet CStyleSheet::getEStyleSheet()
{
    return m_styleSheet;
}

QString CStyleSheet::loadStyle(const QString &filePath)
{
    //qDebug() << Q_FUNC_INFO << filePath;
    QString styleSheet ;
    QDir dir(filePath);
    QStringList nameFilters;
    nameFilters << "*.qss";
    dir.setNameFilters(nameFilters);
    QFileInfoList fileList = dir.entryInfoList();
    int size = fileList.size();
    for(int i = 0; i < size; ++i)
    {
        QFileInfo fileInfo = fileList.at(i);
        //qDebug() << "files:" << fileInfo.fileName() << fileInfo.filePath();
        QFile qss(fileInfo.filePath());
        if(qss.open(QFile::ReadOnly))
        {
            styleSheet += qss.readAll();
            qss.close();
        }
    }
    return styleSheet;
}

