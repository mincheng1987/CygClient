#编译选项全局公共功能定义，被所有模块全局引用。
#比如编译模式 debug or release
#比如指定当前应用需要编译的版本
#比如定义三方库依赖文件
#比如生成库或应用输出路径
#全局功能需要利用的方法


# 重复包含检查，如果发现重复包含了就报错
!isEmpty(APP_PRI_INCLUDED):error("common.pri already included")
APP_PRI_INCLUDED = 1


#编译路径只到debug/release这一层，不再追加$$[QT_VERSION]和$$[QMAKE_SPEC]
BUILD_MODE = release
BUILD_LIB_NAME = release_lib
CONFIG(debug, debug|release) {
    BUILD_MODE = debug
    BUILD_LIB_NAME = debug_lib
}


#指定最小的QT版本
greaterThan(QT_MAJOR_VERSION, 4):

# 指定支持的c++版本， 链接的时候输出相关依赖文件
CONFIG += c++17

#FLATFORM_NAME平台定义 这个名字和Output目录，ThirdPartlib目录下的各个平台名字一样
win32 {
    FLATFORM_NAME = win
    DLL_SUFFIX = .dll
    message(win platform compile)
}

macx {
    FLATFORM_NAME = mac
    DLL_SUFFIX = .dylib
    message(mac platform compile)
}

android {
    FLATFORM_NAME = android
    DLL_SUFFIX = .so
    message(android platform compile)
}

unix:!macx {
    FLATFORM_NAME = linux
    DLL_SUFFIX = .so
    message(unix platform compile)
}



#项目所在目录 CygClient 所在目錄
ROOT_PATH = $$PWD/..
#项目根路径
PROJECT_PATH = $$PWD
#外部三方库路径
THIRD_PARTY_LIB_PATH = $$ROOT_PATH/ThirdPartlib/$$FLATFORM_NAME/$$BUILD_MODE
#外部三方库头文件路径
THIRD_PARTY_INCLUDE_PATH = $$ROOT_PATH/ThirdPartlib/$$FLATFORM_NAME/include
#应用程序生成目录，相关依赖的库也会被拷贝到这里，确保编译完成，全部自动生成到这个目录
OUTPUT_ROOT_PATH = $$ROOT_PATH/Output/$$FLATFORM_NAME/$$BUILD_MODE
# PDB_PATH
PDB_PATH = $$ROOT_PATH/Output/PDB
#字库lib目录名称
LIB_PATH = $$ROOT_PATH/Output/$$FLATFORM_NAME/lib/$$BUILD_MODE


#定义用于文件拷贝的函数，当编译完成后，各个字库可将生成的lib , dll ，头文件拷贝到内部库目录，
#或者拷贝三方库中的dll 到执行目录。
defineReplace(qtDependentCopy) {
   unset(src_dir)
   unset(dst_dir)
   src_dir = $$1
   dst_dir = $$2
   src_dir ~= s,/,\\,g
   dst_dir ~= s,/,\\,g
   system(xcopy $$src_dir $$dst_dir /y /e /s)
   return ($$1)
}


#通用编译选项
INCLUDEPATH += $$PWD
PRECOMPILED_HEADER = $$PROJECT_PATH/precompiler_header.h





#内存泄露检测（备用）
#CONFIG(debug, debug|release) {
#    LIBS += -L$$OUTPUT_LIB_PATH -lvld
#}
