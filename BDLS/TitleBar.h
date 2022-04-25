#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPoint>
#include <QPixmap>
#include <QString>
/**
 * @brief Title block interface components
 * @author
 */

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget* parent = NULL);
    /**
     * @brief Set title block title
     * @param title£¬Parameter, set title
     */
    void setWindowTitle(const QString& title);
    /**
     * @brief Sets the icon for the title block
     * @param iconPath£¬Parameter, path of Icon
     */
    void SetTitleBarIcon(const QString& iconPath);

protected:
    /**
     * @brief Double click the event handler
     * @param event£¬Parameters, events
     * @note Double click the title bar to maximize / restore the interface
     */
    virtual void mouseDoubleClickEvent(QMouseEvent* event);

    /**
     * @brief Mouse down event handler
     * @param event£¬Parameters, events
     * @note Press the left mouse button
     */
    virtual void mousePressEvent(QMouseEvent* event);

    /**
     * @brief Mouse movement event handler
     * @param event£¬Parameters, events
     * @note Move mouse
     */
    virtual void mouseMoveEvent(QMouseEvent* event);

    /**
     * @brief Mouse release event handler
     * @param event£¬Parameters, events
     * @note Release the mouse
     */
    virtual void mouseReleaseEvent(QMouseEvent* event);

    /**
     * @brief Event filter processor
     * @param obj£¬parameter
     * @param event£¬Parameters, events
     * @return Return true for success and false for failure
     * @note Set title and Icon
     */
    virtual bool eventFilter(QObject* obj, QEvent* event);

    /**
     * @brief Maximize / restore
     */
    void updateMaximize();
protected slots:
    /**
     * @brief Slot functions that respond when the minimize, maximize / restore, and close buttons are clicked
     */
    void onClicked();

private:
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QPushButton* m_minimizeButton;
    QPushButton* m_maximizeButton;
    QPushButton* m_closeButton;
    QPoint m_start;//starting point
    QPoint m_end;//End point
    bool m_leftButtonPressed;//Press the mark with the left mouse button
};

#endif // TITLEBAR_H