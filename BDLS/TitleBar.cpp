#include "TitleBar.h"
#include <QStyle>

TitleBar::TitleBar(QWidget* parent) : QWidget(parent)
{
    setFixedHeight(30);
    setWindowFlags(Qt::FramelessWindowHint);
    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(20, 20);
    m_iconLabel->setScaledContents(true);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_minimizeButton = new QPushButton(this);
    m_minimizeButton->setFixedSize(24, 24);
    m_minimizeButton->setObjectName("minimizeButton");
    m_minimizeButton->setFlat(true);
    m_minimizeButton->setIcon(QIcon(":/BDLS/icons/window_minimize_solid_icon.png"));

    m_maximizeButton = new QPushButton(this);
    m_maximizeButton->setFixedSize(24, 24);
    m_maximizeButton->setObjectName("maximizeButton");
    m_maximizeButton->setFlat(true);
    m_maximizeButton->setIcon(QIcon(":/BDLS/icons/window_maximize_icon.png"));

    m_closeButton = new QPushButton(this);
    m_closeButton->setFixedSize(24, 24);
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setFlat(true);
    m_closeButton->setIcon(QIcon(":/BDLS/icons/window_close_icon.png"));

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_iconLabel);
    layout->addStretch(1);
    layout->addWidget(m_titleLabel);
    layout->addStretch(1);
    layout->addWidget(m_minimizeButton);
    layout->addWidget(m_maximizeButton);
    layout->addWidget(m_closeButton);
    setLayout(layout);

    setProperty("titleBar", true);
    setObjectName("titleBar");
    connect(m_minimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_maximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_closeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

void TitleBar::setWindowTitle(const QString& title)
{
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setText(title);
}

void TitleBar::SetTitleBarIcon(const QString& iconPath)
{
    QPixmap map(iconPath);
    m_iconLabel->setPixmap(map);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    m_maximizeButton->click();
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
    //Left mouse button press event
    if (event->button() == Qt::LeftButton)
    {
        //Record the left mouse button status
        m_leftButtonPressed = true;
        //Record the position of the mouse on the screen
        m_start = event->globalPos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
    //Press and hold continuously to do the corresponding event
    if (m_leftButtonPressed)
    {
        //Move the parent form to the original position of the parent form plus the position where the mouse moves: Event - > globalpos() - M_ start
        parentWidget()->move(parentWidget()->geometry().topLeft() +
            event->globalPos() - m_start);
        //Replace the position of the mouse in the screen with the new position
        m_start = event->globalPos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event)
{
    //Left mouse button release
    if (event->button() == Qt::LeftButton)
    {
        //Record mouse status
        m_leftButtonPressed = false;
    }
}

bool TitleBar::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type())
    {
        //Set title
    case QEvent::WindowTitleChange:
    {
        QWidget* pWidget = qobject_cast<QWidget*>(obj);
        if (pWidget)
        {
            m_titleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }

    //Settings Icon
    case QEvent::WindowIconChange:
    {
        QWidget* pWidget = qobject_cast<QWidget*>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_iconLabel->setPixmap(icon.pixmap(m_iconLabel->size()));
            return true;
        }
    }

    //Window state change and window size change
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    }

    return QWidget::eventFilter(obj, event);
}

void TitleBar::updateMaximize()
{
    QWidget* pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_maximizeButton->setToolTip(tr("Restore"));
            m_maximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_maximizeButton->setProperty("maximizeProperty", "maximize");
            m_maximizeButton->setToolTip(tr("Maximize"));
        }
        m_maximizeButton->setStyle(QApplication::style());
    }
}

void TitleBar::onClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    QWidget* pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_minimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_maximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_closeButton)
        {
            pWindow->close();
        }
    }
}