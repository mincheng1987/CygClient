#include "cygapplication.h"
#include <QTranslator>
#include "StyleSheet.h"
#include "mainwindow.h"


CygApplication::CygApplication(QObject *parent):QObject(parent)
{
    m_app = nullptr;
}

CygApplication::~CygApplication()
{
    if(m_app)
        delete m_app;
}

int CygApplication::initInstance(int argc, char *argv[])
{
    //创建 APP实例，绑定退出事件
    m_app = new QApplication(argc,argv);

    connect(m_app,SIGNAL(aboutToQuit()),this,SLOT(onExitInstance()));
    //调用初始化函数，用于用户数据初始化
    return onInitInstance(*m_app);
}

void CygApplication::onExitInstance()
{
}


int CygApplication::onInitInstance(QApplication& app)
{
    //语言初始化
    // QTranslator translator;
    // translator.load(Hzcfg::getInstance()->getLanguagePath());
    // app.installTranslator(&translator);

    //皮肤加载
    CStyleSheet::GetInstance()->SetStyle(CStyleSheet::DEFAULT);


    MainWindow w;
    w.show();

    return app.exec();
}
