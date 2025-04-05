# CygClient
QT 跨平台金融客户端项目，支持皮肤切换，多语言处理。

# 平台
开发环境 qt6.8.2  编译器mingw_64
windows 11
macos 14

# common.pri
当前代码基于qmake 构建项目文件， common.pri是一个公共用引入的模块，负责全局的编译输出对象的定义。比如公共输出库目录，输出执行文件目录，以及三方库目录，还有一些跨编译的公共变量的定义。

# skin
目前支持黑白两种皮肤的运行时切换。
## mac
![image](https://github.com/mincheng1987/CygClient/blob/main/CygClient/doc/img/mac_ui.png?raw=true)
## win
![image](https://github.com/mincheng1987/CygClient/blob/main/CygClient/doc/img/win_ui.png.png?raw=true)

# 整体架构设计
[行情客户端项目整体规划](https://github.com/mincheng1987/CygClient/tree/main/CygClient/doc/行情客户端项目整体规划.pdf)

# 其他功能
持续迭代中
