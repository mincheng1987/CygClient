TEMPLATE = subdirs
CONFIG += ordered

#引入公共多平台定义编译项目
include($$PWD/common.pri)

#当前应用根据自己需要引入依赖的模块
SUBDIRS += \
    CygClientCore \
    CygClientExample \
    CygClientControl \
    CygFinClientComponent \
    CygFinClientShell

system(/users/qt/6.8.2/macos/libexec/rcc -binary $$PWD/CygFinClientShell/skin/black/resource.qrc -o $$OUTPUT_ROOT_PATH/theme-black.rcc)
system(/users/qt/6.8.2/macos/libexec/rcc -binary $$PWD/CygFinClientShell/skin/white/resource.qrc -o $$OUTPUT_ROOT_PATH/theme-white.rcc)
include($$PWD/CygFinClientShell/skin/skin.pri)
