#include "filepathhelper.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

FilePathHelper::FilePathHelper(QObject *parent)
    : QObject{parent}
{}

QString FilePathHelper::getExecutableDirectory()
{
    QString strProject = QCoreApplication::applicationDirPath();

    // 在 macOS 上处理 .app 包的情况
#ifdef Q_OS_MAC
    // 直接拼接进程名字和 /Contents/MacOS
    QString processName = QCoreApplication::applicationName() + ".app";
    if (strProject.endsWith(processName + "/Contents/MacOS")) {
        strProject = strProject.left(strProject.length() - (processName + "/Contents/MacOS").length());
    }
#endif

    // 确保路径以分隔符结尾
    if (!strProject.endsWith(QDir::separator())) {
        strProject.append(QDir::separator());
    }

    return strProject;
}
