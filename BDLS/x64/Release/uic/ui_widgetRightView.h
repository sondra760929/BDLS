/********************************************************************************
** Form generated from reading UI file 'widgetRightView.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETRIGHTVIEW_H
#define UI_WIDGETRIGHTVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qpdfview.h"

QT_BEGIN_NAMESPACE

class Ui_widgetRightView
{
public:
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionContinuous;
    QHBoxLayout *horizontalLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *bookmarkTab;
    QTreeView *bookmarkView;
    QPdfView *pdfView;
    QWidget *page_2;

    void setupUi(QWidget *widgetRightView)
    {
        if (widgetRightView->objectName().isEmpty())
            widgetRightView->setObjectName(QString::fromUtf8("widgetRightView"));
        widgetRightView->resize(166, 715);
        actionZoom_In = new QAction(widgetRightView);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/BDLS/icons/zoom-in-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon);
        actionZoom_Out = new QAction(widgetRightView);
        actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/BDLS/icons/zoom-out-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Out->setIcon(icon1);
        actionContinuous = new QAction(widgetRightView);
        actionContinuous->setObjectName(QString::fromUtf8("actionContinuous"));
        actionContinuous->setCheckable(true);
        horizontalLayout_3 = new QHBoxLayout(widgetRightView);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        stackedWidget = new QStackedWidget(widgetRightView);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout = new QVBoxLayout(page);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        widget = new QWidget(page);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setIcon(icon1);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget);

        splitter = new QSplitter(page);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::West);
        bookmarkTab = new QWidget();
        bookmarkTab->setObjectName(QString::fromUtf8("bookmarkTab"));
        bookmarkView = new QTreeView(bookmarkTab);
        bookmarkView->setObjectName(QString::fromUtf8("bookmarkView"));
        bookmarkView->setGeometry(QRect(20, 60, 171, 411));
        tabWidget->addTab(bookmarkTab, QString());
        splitter->addWidget(tabWidget);
        pdfView = new QPdfView(splitter);
        pdfView->setObjectName(QString::fromUtf8("pdfView"));
        splitter->addWidget(pdfView);

        verticalLayout->addWidget(splitter);

        verticalLayout->setStretch(1, 100);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout_3->addWidget(stackedWidget);


        retranslateUi(widgetRightView);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(widgetRightView);
    } // setupUi

    void retranslateUi(QWidget *widgetRightView)
    {
        widgetRightView->setWindowTitle(QCoreApplication::translate("widgetRightView", "widgetRightView", nullptr));
        actionZoom_In->setText(QCoreApplication::translate("widgetRightView", "Zoom_In", nullptr));
#if QT_CONFIG(tooltip)
        actionZoom_In->setToolTip(QCoreApplication::translate("widgetRightView", "Zoom_In", nullptr));
#endif // QT_CONFIG(tooltip)
        actionZoom_Out->setText(QCoreApplication::translate("widgetRightView", "Zoom_Out", nullptr));
#if QT_CONFIG(tooltip)
        actionZoom_Out->setToolTip(QCoreApplication::translate("widgetRightView", "Zoom_Out", nullptr));
#endif // QT_CONFIG(tooltip)
        actionContinuous->setText(QCoreApplication::translate("widgetRightView", "Continuous", nullptr));
#if QT_CONFIG(tooltip)
        actionContinuous->setToolTip(QCoreApplication::translate("widgetRightView", "Continuous", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(bookmarkTab), QCoreApplication::translate("widgetRightView", "Bookmarks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widgetRightView: public Ui_widgetRightView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETRIGHTVIEW_H
