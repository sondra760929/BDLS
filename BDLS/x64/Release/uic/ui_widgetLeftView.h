/********************************************************************************
** Form generated from reading UI file 'widgetLeftView.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETLEFTVIEW_H
#define UI_WIDGETLEFTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgetLeftView
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *fileview;
    QVBoxLayout *verticalLayout_2;
    QTreeView *tvFiles;
    QWidget *searchview;
    QWidget *noteview;

    void setupUi(QWidget *widgetLeftView)
    {
        if (widgetLeftView->objectName().isEmpty())
            widgetLeftView->setObjectName(QString::fromUtf8("widgetLeftView"));
        widgetLeftView->resize(469, 783);
        verticalLayout = new QVBoxLayout(widgetLeftView);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(widgetLeftView);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        fileview = new QWidget();
        fileview->setObjectName(QString::fromUtf8("fileview"));
        verticalLayout_2 = new QVBoxLayout(fileview);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        tvFiles = new QTreeView(fileview);
        tvFiles->setObjectName(QString::fromUtf8("tvFiles"));

        verticalLayout_2->addWidget(tvFiles);

        tabWidget->addTab(fileview, QString());
        searchview = new QWidget();
        searchview->setObjectName(QString::fromUtf8("searchview"));
        tabWidget->addTab(searchview, QString());
        noteview = new QWidget();
        noteview->setObjectName(QString::fromUtf8("noteview"));
        tabWidget->addTab(noteview, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(widgetLeftView);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(widgetLeftView);
    } // setupUi

    void retranslateUi(QWidget *widgetLeftView)
    {
        widgetLeftView->setWindowTitle(QCoreApplication::translate("widgetLeftView", "widgetLeftView", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(fileview), QCoreApplication::translate("widgetLeftView", "File", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(searchview), QCoreApplication::translate("widgetLeftView", "Search", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(noteview), QCoreApplication::translate("widgetLeftView", "Note", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widgetLeftView: public Ui_widgetLeftView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETLEFTVIEW_H
