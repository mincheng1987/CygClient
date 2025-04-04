#include "framelesshelper.h"
#include <QRect>
#include <QRubberBand>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QApplication>



class WidgetData;
//class FramelessHelperPrivate;

/*****
 * FramelessHelperPrivate
 * 存储界面对应的数据集合，以及是否可移动、可缩放属性
*****/
class FramelessHelperPrivate
{
public:
    QHash<QWidget*, WidgetData*> m_widgetDataHash;
    bool m_bWidgetMovable        : true;
    bool m_bWidgetResizable      : true;
    bool m_bRubberBandOnResize   : true;
    bool m_bRubberBandOnMove     : true;
};

/*****
 * CursorPosCalculator
 * 计算鼠标是否位于左、上、右、下、左上角、左下角、右上角、右下角
*****/
class CursorPosCalculator
{
public:
    explicit CursorPosCalculator();
    void reset();
    void recalculate(const QPoint &globalMousePos, const QRect &frameRect,int nBorder);

public:
    bool m_bOnEdges              : true;
    bool m_bOnLeftEdge           : true;
    bool m_bOnRightEdge          : true;
    bool m_bOnTopEdge            : true;
    bool m_bOnBottomEdge         : true;
    bool m_bOnTopLeftEdge        : true;
    bool m_bOnBottomLeftEdge     : true;
    bool m_bOnTopRightEdge       : true;
    bool m_bOnBottomRightEdge    : true;
};

/***** CursorPosCalculator *****/
CursorPosCalculator::CursorPosCalculator()
{
    reset();
}

void CursorPosCalculator::reset()
{
    m_bOnEdges = false;
    m_bOnLeftEdge = false;
    m_bOnRightEdge = false;
    m_bOnTopEdge = false;
    m_bOnBottomEdge = false;
    m_bOnTopLeftEdge = false;
    m_bOnBottomLeftEdge = false;
    m_bOnTopRightEdge  = false;
    m_bOnBottomRightEdge = false;
}

void CursorPosCalculator::recalculate(const QPoint &gMousePos, const QRect &frameRect,int nBorder)
{
    int globalMouseX = gMousePos.x();
    int globalMouseY = gMousePos.y();

    int frameX = frameRect.x();
    int frameY = frameRect.y();

    int frameWidth = frameRect.width();
    int frameHeight = frameRect.height();

    m_bOnLeftEdge = (globalMouseX >= frameX &&
                     globalMouseX <= frameX + nBorder );


    m_bOnRightEdge = (globalMouseX >= frameX + frameWidth - nBorder &&
                      globalMouseX <= frameX + frameWidth);

    m_bOnTopEdge = (globalMouseY >= frameY &&
                    globalMouseY <= frameY + nBorder );

    m_bOnBottomEdge = (globalMouseY >= frameY + frameHeight - nBorder &&
                       globalMouseY <= frameY + frameHeight);

    m_bOnTopLeftEdge = m_bOnTopEdge && m_bOnLeftEdge;
    m_bOnBottomLeftEdge = m_bOnBottomEdge && m_bOnLeftEdge;
    m_bOnTopRightEdge = m_bOnTopEdge && m_bOnRightEdge;
    m_bOnBottomRightEdge = m_bOnBottomEdge && m_bOnRightEdge;

    m_bOnEdges = m_bOnLeftEdge || m_bOnRightEdge || m_bOnTopEdge || m_bOnBottomEdge;
}

/*****
 * WidgetData
 * 更新鼠标样式、移动窗体、缩放窗体
*****/
class WidgetData
{
public:
    explicit WidgetData(FramelessHelperPrivate *d, QWidget *pTopLevelWidget);
    ~WidgetData();
    QWidget* widget();
    // 处理鼠标事件-划过、按下、释放、移动
    void handleWidgetEvent(QEvent *event);
    // 更新橡皮筋状态
    void updateRubberBandStatus();
    // 设置边框的宽度
    void setBorderWidth(uint width);
    // 设置标题栏高度
    void setTitleHeight(uint height);
private:
    // 更新鼠标样式
    void updateCursorShape(const QPoint &gMousePos);
    // 重置窗体大小
    void resizeWidget(const QPoint &gMousePos);
    // 移动窗体
    void moveWidget(const QPoint &gMousePos);
    // 处理鼠标按下
    void handleMousePressEvent(QMouseEvent *event);
    // 处理鼠标释放
    void handleMouseReleaseEvent(QMouseEvent *event);
    // 处理鼠标移动
    void handleMouseMoveEvent(QMouseEvent *event);
    // 处理鼠标离开
    void handleLeaveEvent(QEvent *event);
    // 处理鼠标进入
    void handleHoverMoveEvent(QHoverEvent *event);

private:
    FramelessHelperPrivate *d = nullptr;
    QRubberBand *m_pRubberBand = nullptr;
    QWidget *m_pWidget = nullptr;
    QPoint m_ptDragPos;
    double m_dLeftScale; // 鼠标位置距离最窗口最左边的距离占整个宽度的比例
    int m_nRightLength; // 鼠标位置距离最窗口最右边的距离
    CursorPosCalculator m_pressedMousePos;
    CursorPosCalculator m_moveMousePos;
    bool m_bLeftButtonPressed;
    bool m_bCursorShapeChanged;
    bool m_bLeftButtonTitlePressed;
    Qt::WindowFlags m_windowFlags;
    int nHeight_ = 30;
    int borderWidth_=5;
};

/***** WidgetData *****/
WidgetData::WidgetData(FramelessHelperPrivate *_d, QWidget *pTopLevelWidget)
{
    d = _d;
    m_pWidget = pTopLevelWidget;
    m_bLeftButtonPressed = false;
    m_bCursorShapeChanged = false;
    m_bLeftButtonTitlePressed = false;
    m_pRubberBand = NULL;

    m_windowFlags = m_pWidget->windowFlags();
    m_pWidget->setMouseTracking(true);
    m_pWidget->setAttribute(Qt::WA_Hover, true);

    updateRubberBandStatus();
}

WidgetData::~WidgetData()
{
    if(m_pRubberBand)
    {
        delete m_pRubberBand;
        m_pRubberBand = NULL;
    }
}

QWidget* WidgetData::widget()
{
    return m_pWidget;
}

void WidgetData::handleWidgetEvent(QEvent *event)
{
    switch (event->type())
    {
    default:
        break;
    case QEvent::MouseButtonPress:
        handleMousePressEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseButtonRelease:
        handleMouseReleaseEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseMove:
        handleMouseMoveEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::Leave:
        handleLeaveEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::HoverMove:
        handleHoverMoveEvent(static_cast<QHoverEvent*>(event));
        break;
    }
}

void WidgetData::updateRubberBandStatus()
{
    if (d->m_bRubberBandOnMove || d->m_bRubberBandOnResize)
    {
        if (NULL == m_pRubberBand)
            m_pRubberBand = new QRubberBand(QRubberBand::Rectangle);
    }
    else if(m_pRubberBand)
    {
        delete m_pRubberBand;
        m_pRubberBand = NULL;
    }
}

void WidgetData::setBorderWidth(uint width)
{
    borderWidth_ = width;
}

void WidgetData::setTitleHeight(uint height)
{
    nHeight_ = height;
}

void WidgetData::updateCursorShape(const QPoint &gMousePos)
{
    if (m_pWidget->isFullScreen() || m_pWidget->isMaximized())
    {
        if (m_bCursorShapeChanged)
        {
            m_pWidget->unsetCursor();
        }
        return;
    }

    m_moveMousePos.recalculate(gMousePos, m_pWidget->frameGeometry(),borderWidth_);

    if(m_moveMousePos.m_bOnTopLeftEdge || m_moveMousePos.m_bOnBottomRightEdge)
    {
        m_pWidget->setCursor( Qt::SizeFDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopRightEdge || m_moveMousePos.m_bOnBottomLeftEdge)
    {
        m_pWidget->setCursor( Qt::SizeBDiagCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnLeftEdge || m_moveMousePos.m_bOnRightEdge)
    {
        m_pWidget->setCursor( Qt::SizeHorCursor );
        m_bCursorShapeChanged = true;
    }
    else if(m_moveMousePos.m_bOnTopEdge || m_moveMousePos.m_bOnBottomEdge)
    {
        m_pWidget->setCursor( Qt::SizeVerCursor );
        m_bCursorShapeChanged = true;
    }
    else
    {
        if (m_bCursorShapeChanged)
        {
            m_pWidget->unsetCursor();
            m_bCursorShapeChanged = false;
        }
    }
}

void WidgetData::resizeWidget(const QPoint &gMousePos)
{
    QRect origRect;

    if (d->m_bRubberBandOnResize && m_pRubberBand)
        origRect = m_pRubberBand->frameGeometry();
    else
        origRect = m_pWidget->frameGeometry();

    int left = origRect.left();
    int top = origRect.top();
    int right = origRect.right();
    int bottom = origRect.bottom();
    origRect.getCoords(&left, &top, &right, &bottom);

    int minWidth = m_pWidget->minimumWidth();
    int minHeight = m_pWidget->minimumHeight();

    if (m_pressedMousePos.m_bOnTopLeftEdge)
    {
        left = gMousePos.x();
        top = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomLeftEdge)
    {
        left = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnTopRightEdge)
    {
        right = gMousePos.x();
        top = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomRightEdge)
    {
        right = gMousePos.x();
        bottom = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnLeftEdge)
    {
        left = gMousePos.x();
    }
    else if (m_pressedMousePos.m_bOnRightEdge)
    {
        right = gMousePos.x();
    }
    else if (m_pressedMousePos.m_bOnTopEdge)
    {
        top = gMousePos.y();
    }
    else if (m_pressedMousePos.m_bOnBottomEdge)
    {
        bottom = gMousePos.y();
    }

    QRect newRect(QPoint(left, top), QPoint(right, bottom));

    if (newRect.isValid())
    {
        if (minWidth > newRect.width())
        {
            if (left != origRect.left())
                newRect.setLeft(origRect.left());
            else
                newRect.setRight(origRect.right());
        }
        if (minHeight > newRect.height())
        {
            if (top != origRect.top())
                newRect.setTop(origRect.top());
            else
                newRect.setBottom(origRect.bottom());
        }

        if (d->m_bRubberBandOnResize && m_pRubberBand)
        {
            m_pRubberBand->setGeometry(newRect);
        }
        else
        {
            m_pWidget->setGeometry(newRect);
        }
    }
}


void WidgetData::moveWidget(const QPoint &gMousePos)
{
    if (d->m_bRubberBandOnMove && m_pRubberBand)
    {
        m_pRubberBand->move(gMousePos - m_ptDragPos);
    }
    else
    {
        // 如果全屏时移动窗口，窗口按点击位置还原
        if (m_pWidget->isMaximized() || m_pWidget->isFullScreen())
        {
            if (m_dLeftScale <= 0.3) { }
            else if (m_dLeftScale > 0.3 && m_dLeftScale < 0.7)
            {
                m_ptDragPos.setX(m_pWidget->normalGeometry().width() * m_dLeftScale);
            }
            else if (m_dLeftScale >= 0.7)
            {
                m_ptDragPos.setX(m_pWidget->normalGeometry().width() - m_nRightLength);
            }

            //            m_pWidget->setGeometry(0, 0, m_pWidget->normalGeometry().width(), m_pWidget->normalGeometry().height());
        }
        m_pWidget->resize(m_pWidget->normalGeometry().size());
        m_pWidget->showNormal();
        m_pWidget->move(gMousePos - m_ptDragPos);
    }
}

void WidgetData::handleMousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPressed = true;
        m_bLeftButtonTitlePressed = event->pos().y() < nHeight_;

        QRect frameRect = m_pWidget->frameGeometry();
        m_pressedMousePos.recalculate(event->globalPosition().toPoint(), frameRect, borderWidth_);

        m_ptDragPos = event->globalPosition().toPoint() - frameRect.topLeft();
        m_dLeftScale = double(m_ptDragPos.x()) / double(frameRect.width());
        m_nRightLength = frameRect.width() - m_ptDragPos.x();

        if (m_pressedMousePos.m_bOnEdges)
        {
            if (d->m_bRubberBandOnResize)
            {
                m_pRubberBand->setGeometry(frameRect);
                m_pRubberBand->show();
            }
        }
        else if (d->m_bRubberBandOnMove)
        {
            m_pRubberBand->setGeometry(frameRect);
            m_pRubberBand->show();
        }
    }
}

void WidgetData::handleMouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bLeftButtonPressed = false;
        m_bLeftButtonTitlePressed = false;
        m_pressedMousePos.reset();
        if (m_pRubberBand && m_pRubberBand->isVisible())
        {
            m_pRubberBand->hide();
            m_pWidget->setGeometry(m_pRubberBand->geometry());
        }
    }
}

void WidgetData::handleMouseMoveEvent(QMouseEvent *event)
{
    if (m_bLeftButtonPressed)
    {
        if (d->m_bWidgetResizable && m_pressedMousePos.m_bOnEdges)
        {
            resizeWidget(event->globalPosition().toPoint());
        }
        else if (d->m_bWidgetMovable && m_bLeftButtonTitlePressed)
        {
            moveWidget(event->globalPosition().toPoint());
        }
    }
    else if (d->m_bWidgetResizable)
    {
        updateCursorShape(event->globalPosition().toPoint());
    }
}

void WidgetData::handleLeaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if (!m_bLeftButtonPressed)
    {
        m_pWidget->unsetCursor();
    }
}

void WidgetData::handleHoverMoveEvent(QHoverEvent *event)
{
    if (d->m_bWidgetResizable)
    {
        updateCursorShape(m_pWidget->mapToGlobal(event->position().toPoint()));
    }
}

/*****FramelessHelper*****/
FramelessHelper::FramelessHelper(QObject *parent)
    : QObject(parent),
    d(new FramelessHelperPrivate())
{
    d->m_bWidgetMovable = true;
    d->m_bWidgetResizable = true;
    d->m_bRubberBandOnResize = false;
    d->m_bRubberBandOnMove = false;
}

FramelessHelper::~FramelessHelper()
{
    QList<QWidget*> keys = d->m_widgetDataHash.keys();
    int size = keys.size();
    for (int i = 0; i < size; ++i)
    {
        delete d->m_widgetDataHash.take(keys[i]);
    }

    delete d;
}

bool FramelessHelper::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::MouseMove:
    case QEvent::HoverMove:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::Leave:
    {
        WidgetData *data = d->m_widgetDataHash.value(static_cast<QWidget*>(obj));
        if (data)
        {
            data->handleWidgetEvent(event);
            //            return true;

        }
    }
    case QEvent::None:
    case QEvent::Timer:
    case QEvent::MouseButtonDblClick:
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::FocusIn:
    case QEvent::FocusOut:
    case QEvent::FocusAboutToChange:
    case QEvent::Enter:
    case QEvent::Paint:
    case QEvent::Move:
    case QEvent::Resize:
    case QEvent::Create:
    case QEvent::Destroy:
    case QEvent::Show:
    case QEvent::Hide:
    case QEvent::Close:
    case QEvent::Quit:
    case QEvent::ParentChange:
    case QEvent::ParentAboutToChange:
    case QEvent::ThreadChange:
    case QEvent::WindowActivate:
    case QEvent::WindowDeactivate:
    case QEvent::ShowToParent:
    case QEvent::HideToParent:
    case QEvent::Wheel:
    case QEvent::WindowTitleChange:
    case QEvent::WindowIconChange:
    case QEvent::ApplicationWindowIconChange:
    case QEvent::ApplicationFontChange:
    case QEvent::ApplicationLayoutDirectionChange:
    case QEvent::ApplicationPaletteChange:
    case QEvent::PaletteChange:
    case QEvent::Clipboard:
    case QEvent::Speech:
    case QEvent::MetaCall:
    case QEvent::SockAct:
    case QEvent::WinEventAct:
    case QEvent::DeferredDelete:
    case QEvent::DragEnter:
    case QEvent::DragMove:
    case QEvent::DragLeave:
    case QEvent::Drop:
    case QEvent::DragResponse:
    case QEvent::ChildAdded:
    case QEvent::ChildPolished:
    case QEvent::ChildRemoved:
    case QEvent::ShowWindowRequest:
    case QEvent::PolishRequest:
    case QEvent::Polish:
    case QEvent::LayoutRequest:
    case QEvent::UpdateRequest:
    case QEvent::UpdateLater:
    case QEvent::EmbeddingControl:
    case QEvent::ActivateControl:
    case QEvent::DeactivateControl:
    case QEvent::ContextMenu:
    case QEvent::InputMethod:
    case QEvent::TabletMove:
    case QEvent::LocaleChange:
    case QEvent::LanguageChange:
    case QEvent::LayoutDirectionChange:
    case QEvent::Style:
    case QEvent::TabletPress:
    case QEvent::TabletRelease:
    case QEvent::OkRequest:
    case QEvent::HelpRequest:
    case QEvent::IconDrag:
    case QEvent::FontChange:
    case QEvent::EnabledChange:
    case QEvent::ActivationChange:
    case QEvent::StyleChange:
    case QEvent::IconTextChange:
    case QEvent::ModifiedChange:
    case QEvent::MouseTrackingChange:
    case QEvent::WindowBlocked:
    case QEvent::WindowUnblocked:
    case QEvent::WindowStateChange:
    case QEvent::ReadOnlyChange:
    case QEvent::ToolTip:
    case QEvent::WhatsThis:
    case QEvent::StatusTip:
    case QEvent::ActionChanged:
    case QEvent::ActionAdded:
    case QEvent::ActionRemoved:
    case QEvent::FileOpen:
    case QEvent::Shortcut:
    case QEvent::ShortcutOverride:
    case QEvent::WhatsThisClicked:
    case QEvent::ToolBarChange:
    case QEvent::ApplicationActivate:
    case QEvent::ApplicationDeactivate:
    case QEvent::QueryWhatsThis:
    case QEvent::EnterWhatsThisMode:
    case QEvent::LeaveWhatsThisMode:
    case QEvent::ZOrderChange:
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    case QEvent::AcceptDropsChange:
    case QEvent::ZeroTimerEvent:
    case QEvent::GraphicsSceneMouseMove:
    case QEvent::GraphicsSceneMousePress:
    case QEvent::GraphicsSceneMouseRelease:
    case QEvent::GraphicsSceneMouseDoubleClick:
    case QEvent::GraphicsSceneContextMenu:
    case QEvent::GraphicsSceneHoverEnter:
    case QEvent::GraphicsSceneHoverMove:
    case QEvent::GraphicsSceneHoverLeave:
    case QEvent::GraphicsSceneHelp:
    case QEvent::GraphicsSceneDragEnter:
    case QEvent::GraphicsSceneDragMove:
    case QEvent::GraphicsSceneDragLeave:
    case QEvent::GraphicsSceneDrop:
    case QEvent::GraphicsSceneWheel:
    case QEvent::GraphicsSceneLeave:
    case QEvent::KeyboardLayoutChange:
    case QEvent::DynamicPropertyChange:
    case QEvent::TabletEnterProximity:
    case QEvent::TabletLeaveProximity:
    case QEvent::NonClientAreaMouseMove:
    case QEvent::NonClientAreaMouseButtonPress:
    case QEvent::NonClientAreaMouseButtonRelease:
    case QEvent::NonClientAreaMouseButtonDblClick:
    case QEvent::MacSizeChange:
    case QEvent::ContentsRectChange:
    case QEvent::MacGLWindowChange:
    case QEvent::FutureCallOut:
    case QEvent::GraphicsSceneResize:
    case QEvent::GraphicsSceneMove:
    case QEvent::CursorChange:
    case QEvent::ToolTipChange:
    case QEvent::NetworkReplyUpdated:
    case QEvent::GrabMouse:
    case QEvent::UngrabMouse:
    case QEvent::GrabKeyboard:
    case QEvent::UngrabKeyboard:
    case QEvent::StateMachineSignal:
    case QEvent::StateMachineWrapped:
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    case QEvent::NativeGesture:
    case QEvent::RequestSoftwareInputPanel:
    case QEvent::CloseSoftwareInputPanel:
    case QEvent::WinIdChange:
    case QEvent::Gesture:
    case QEvent::GestureOverride:
    case QEvent::ScrollPrepare:
    case QEvent::Scroll:
    case QEvent::Expose:
    case QEvent::InputMethodQuery:
    case QEvent::OrientationChange:
    case QEvent::TouchCancel:
    case QEvent::ThemeChange:
    case QEvent::SockClose:
    case QEvent::PlatformPanel:
    case QEvent::StyleAnimationUpdate:
    case QEvent::ApplicationStateChange:
    case QEvent::WindowChangeInternal:
    case QEvent::ScreenChangeInternal:
    case QEvent::PlatformSurface:
    case QEvent::Pointer:
    case QEvent::TabletTrackingChange:
    case QEvent::WindowAboutToChangeInternal:
    case QEvent::DevicePixelRatioChange:
    case QEvent::ChildWindowAdded:
    case QEvent::ChildWindowRemoved:
    case QEvent::ParentWindowAboutToChange:
    case QEvent::ParentWindowChange:
    //case QEvent::SafeAreaMarginsChange:
    case QEvent::User:
    case QEvent::MaxUser:
        break;
    }
    return QObject::eventFilter(obj, event);
}

void FramelessHelper::activateOn(QWidget *topLevelWidget)
{
    if (!d->m_widgetDataHash.contains(topLevelWidget))
    {
        WidgetData *data = new WidgetData(d, topLevelWidget);
        d->m_widgetDataHash.insert(topLevelWidget, data);

        topLevelWidget->installEventFilter(this);
    }
}

void FramelessHelper::removeFrom(QWidget *topLevelWidget)
{
    WidgetData *data = d->m_widgetDataHash.take(topLevelWidget);
    if (data)
    {
        topLevelWidget->removeEventFilter(this);
        delete data;
    }
}

void FramelessHelper::setRubberBandOnMove(bool movable)
{
    d->m_bRubberBandOnMove = movable;
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

void FramelessHelper::setWidgetMovable(bool movable)
{
    d->m_bWidgetMovable = movable;
}

void FramelessHelper::setWidgetResizable(bool resizable)
{
    d->m_bWidgetResizable = resizable;
}

void FramelessHelper::setRubberBandOnResize(bool resizable)
{
    d->m_bRubberBandOnResize = resizable;
    QList<WidgetData*> list = d->m_widgetDataHash.values();
    foreach (WidgetData *data, list)
    {
        data->updateRubberBandStatus();
    }
}

void FramelessHelper::setBorderWidth(uint width)
{
    if (width > 0)
    {
        if(d)
        {
            for(auto it = d->m_widgetDataHash.begin();it != d->m_widgetDataHash.end();it++)
            {
                it.value()->setBorderWidth(width);
            }
        }
        m_nBorderWidth = width;
    }
}

void FramelessHelper::setTitleHeight(uint height)
{
    if (height > 0)
    {
        if(d)
        {
            for(auto it = d->m_widgetDataHash.begin();it != d->m_widgetDataHash.end();it++)
            {
                it.value()->setTitleHeight(height);
            }
        }
        m_nTitleHeight = height;
    }
}

bool FramelessHelper::widgetMovable()
{
    return d->m_bWidgetMovable;
}

bool FramelessHelper::widgetResizable()
{
    return d->m_bWidgetResizable;
}

bool FramelessHelper::rubberBandOnMove()
{
    return d->m_bRubberBandOnMove;
}

bool FramelessHelper::rubberBandOnResisze()
{
    return d->m_bRubberBandOnResize;
}

uint FramelessHelper::borderWidth()
{
    return m_nBorderWidth;
}

uint FramelessHelper::titleHeight()
{
    return m_nTitleHeight;
}
