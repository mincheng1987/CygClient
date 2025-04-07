# CygClient
QT 跨平台金融客户端项目，支持皮肤切换，多语言处理。

# 愿景
我期望能将金融客户端软件的全套开发功能分享出来，为每个模块配备完备的文档。当下，金融客户端领域的开源项目不仅稀缺，而且大多不够完整，致使开发者常常陷入重复编码的困境。
目前，项目的整体框架搭建，包括 pro 文件配置都已顺利完成。后续，我会利用业余时间，逐步完成其他模块的开发与文档撰写工作。旨在为行业内的新人提供一套实用的学习资料，同时，帮助同行们规避重复劳动，推动整个行业的知识共享与技术进步 。
作者博客：[淬渊阁]https://blog.csdn.net/u011374344?type=blog
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
![image](https://github.com/mincheng1987/CygClient/blob/main/CygClient/doc/img/%E6%95%B4%E4%BD%93%E6%9E%B6%E6%9E%84%E5%9B%BE.jpg?raw=true)
[行情客户端项目整体规划](https://github.com/mincheng1987/CygClient/tree/main/CygClient/doc/行情客户端项目整体规划.pdf)

# 其他功能
持续迭代中
