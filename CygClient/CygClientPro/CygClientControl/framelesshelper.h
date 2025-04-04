#ifndef FRAMELESS_HELPER_H
#define FRAMELESS_HELPER_H

/********************************************************************
created: 2020.2.26
author: min.cheng
purpose: 无边框窗口帮助类，实现自定义窗口的拖动和缩放功能
*********************************************************************/

#include <QObject>

class QWidget;
class FramelessHelperPrivate;

/**
 * @brief FramelessHelper  无边框窗口帮助类
 * 用于实现自定义窗口的拖动和缩放功能，通过事件过滤器监控窗口的鼠标事件
 * 支持窗口标题栏拖动和窗口边缘调整大小
 */
class FramelessHelper : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief FramelessHelper  构造函数
     * @param parent  父对象指针
     */
    explicit FramelessHelper(QObject *parent = 0);

    /**
     * @brief ~FramelessHelper  析构函数
     */
    ~FramelessHelper();

    /**
     * @brief activateOn  激活窗体，将指定窗口添加到事件过滤器中
     * @param topLevelWidget  需要处理的顶层窗口
     */
    void activateOn(QWidget *topLevelWidget);

    /**
     * @brief removeFrom  移除窗体，将指定窗口从事件过滤器中移除
     * @param topLevelWidget  需要移除的顶层窗口
     */
    void removeFrom(QWidget *topLevelWidget);

    /**
     * @brief setWidgetMovable  设置窗体是否可移动
     * @param movable  true表示窗体可以移动，false表示不可移动
     */
    void setWidgetMovable(bool movable);

    /**
     * @brief setWidgetResizable  设置窗体是否可缩放
     * @param resizable  true表示窗体可以缩放，false表示不可缩放
     */
    void setWidgetResizable(bool resizable);

    /**
     * @brief setRubberBandOnMove  设置移动窗体时是否显示橡皮筋效果
     * @param movable  true表示显示橡皮筋效果，false表示不显示
     */
    void setRubberBandOnMove(bool movable);

    /**
     * @brief setRubberBandOnResize  设置缩放窗体时是否显示橡皮筋效果
     * @param resizable  true表示显示橡皮筋效果，false表示不显示
     */
    void setRubberBandOnResize(bool resizable);

    /**
     * @brief setBorderWidth  设置边框的宽度
     * @param width  边框宽度，用于判断鼠标是否在边框区域
     */
    void setBorderWidth(uint width);

    /**
     * @brief setTitleHeight  设置标题栏高度
     * @param height  标题栏高度，用于判断鼠标是否在标题栏区域
     */
    void setTitleHeight(uint height);

    /**
     * @brief widgetResizable  获取窗体是否可缩放
     * @return 返回窗体是否可缩放
     */
    bool widgetResizable();

    /**
     * @brief widgetMovable  获取窗体是否可移动
     * @return 返回窗体是否可移动
     */
    bool widgetMovable();

    /**
     * @brief rubberBandOnMove  获取移动窗体时是否显示橡皮筋效果
     * @return 返回是否显示橡皮筋效果
     */
    bool rubberBandOnMove();

    /**
     * @brief rubberBandOnResisze  获取缩放窗体时是否显示橡皮筋效果
     * @return 返回是否显示橡皮筋效果
     */
    bool rubberBandOnResisze();

    /**
     * @brief borderWidth  获取边框宽度
     * @return 返回边框宽度
     */
    uint borderWidth();

    /**
     * @brief titleHeight  获取标题栏高度
     * @return 返回标题栏高度
     */
    uint titleHeight();

protected:
    /**
     * @brief eventFilter  事件过滤器，用于处理窗口的鼠标事件
     * @param obj  事件的目标对象
     * @param event  事件对象
     * @return 如果事件被处理，返回true；否则返回false
     */
    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    int m_nBorderWidth;  // 边框宽度
    int m_nTitleHeight;  // 标题栏高度
    FramelessHelperPrivate *d;  // 私有数据指针
};


#endif //FRAMELESS_HELPER_H
