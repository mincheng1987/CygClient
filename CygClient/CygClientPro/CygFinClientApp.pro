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

# 皮肤rcc文件生成， 注意rcc 的逻辑，确保配置正确的环境变量.
win32 {
    system(rcc.exe -binary $$PWD/CygFinClientShell/skin/black/resource.qrc -o $$OUTPUT_ROOT_PATH/theme-black.rcc)
    system(rcc.exe -binary $$PWD/CygFinClientShell/skin/white/resource.qrc -o $$OUTPUT_ROOT_PATH/theme-white.rcc)
}

macx {
    system(/users/qt/6.8.2/macos/libexec/rcc -binary $$PWD/CygFinClientShell/skin/black/resource.qrc -o $$OUTPUT_ROOT_PATH/theme-black.rcc)
    system(/users/qt/6.8.2/macos/libexec/rcc -binary $$PWD/CygFinClientShell/skin/white/resource.qrc -o $$OUTPUT_ROOT_PATH/theme-white.rcc)
}

include($$PWD/CygFinClientShell/skin/skin.pri)
