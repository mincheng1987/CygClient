QT += core gui
# 指定当前项目作为什么类型使用，比如app， lib, subdirs等
TEMPLATE = lib
# 指定一个宏，后面在CygClientCore_global.h中可以看到， 用于区分是导出还是导入
DEFINES += CYG_CLIENTCORE_LIBRARY



#帮定功能pri 文件
include($$PWD/../common.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#指定查找.h 文件的相关目录，这样导入后代码里面就可以写成#include "cygclientcore.h"，否则
#就需要写出#include "include/cygclientcore.h"，否则就会报错
INCLUDEPATH += \
     $$PWD/include

#编译依赖的源文件
SOURCES += \
    baseobject.cpp \
    filepathhelper.cpp

#编译依赖的头文件
HEADERS += \
    include/CygClientCore_global.h \
    include/filepathhelper.h \
    include/baseobject.h


#生成的项目文件，比如.a .dll等都会直接生成到这个目录
DESTDIR = $$LIB_PATH


# 执行install安装命令的时候 会将这些文件拷贝到对应的目录
# 这里需要添加一个构建步骤，否则这里不会生效， 点击"项目"-"构建"-"添加构建步骤"-"Make 参数"这一栏输入 install

win32 {
    INSTALL_PDB_PATH.files += $$PWD/$$LIB_PATH/*.pdb
    INSTALL_PDB_PATH.path = $$PDB_PATH
    INSTALLS += INSTALL_PDB_PATH
} 
