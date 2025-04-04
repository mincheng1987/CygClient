QT       += core gui widgets

include($$PWD/../common.pri)

TARGET = FinClient


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    $$PWD  \
    $$PWD/../CygClientCore/include  \
    $$PWD/../CygClientControl/include

SOURCES += \
    cygapplication.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    cygapplication.h \
    mainwindow.h

FORMS += \
    mainwindow.ui


# 可执行文件生成后输出的目录
DESTDIR = $$OUTPUT_ROOT_PATH

#三方依赖库拷贝到lib中
$$qtDependentCopy($$THIRD_PARTY_LIB_PATH, $$LIB_PATH)

#指定库链接
win32 {
    LIBS += -L$$LIB_PATH -lCygClientCore -lCygClientControl
}

macx {
    LIBS += -L$$LIB_PATH -lCygClientControl
}

android {
    LIBS += -L$$LIB_PATH -llibCygClientCore -lCygClientControl
}

unix:!macx {
    LIBS += -L$$LIB_PATH -llibCygClientCore -llibCygClientControl
}


# 自定义动态库和三方库拷贝到执行目录
INSTALL_DLL.files += $$LIB_PATH/*$$DLL_SUFFIX
INSTALL_DLL.path = $$OUTPUT_ROOT_PATH
INSTALLS += INSTALL_DLL




