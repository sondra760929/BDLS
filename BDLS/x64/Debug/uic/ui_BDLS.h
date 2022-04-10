/********************************************************************************
** Form generated from reading UI file 'BDLS.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BDLS_H
#define UI_BDLS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BDLSClass
{
public:
    QAction *actionAddRow;
    QAction *actionDelRow;
    QAction *actionDBUpdate;
    QAction *actionSearchList;
    QAction *actionSearchContent;
    QAction *actionSearchFileName;
    QAction *actionLockFile;
    QAction *actionUnLockFile;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BDLSClass)
    {
        if (BDLSClass->objectName().isEmpty())
            BDLSClass->setObjectName(QString::fromUtf8("BDLSClass"));
        BDLSClass->resize(720, 697);
        actionAddRow = new QAction(BDLSClass);
        actionAddRow->setObjectName(QString::fromUtf8("actionAddRow"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/BDLS/icons/add_row.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddRow->setIcon(icon);
        actionDelRow = new QAction(BDLSClass);
        actionDelRow->setObjectName(QString::fromUtf8("actionDelRow"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/BDLS/icons/del_row.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelRow->setIcon(icon1);
        actionDBUpdate = new QAction(BDLSClass);
        actionDBUpdate->setObjectName(QString::fromUtf8("actionDBUpdate"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/BDLS/icons/savedb.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDBUpdate->setIcon(icon2);
        actionSearchList = new QAction(BDLSClass);
        actionSearchList->setObjectName(QString::fromUtf8("actionSearchList"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/BDLS/icons/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSearchList->setIcon(icon3);
        actionSearchContent = new QAction(BDLSClass);
        actionSearchContent->setObjectName(QString::fromUtf8("actionSearchContent"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/BDLS/icons/search_doc.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSearchContent->setIcon(icon4);
        actionSearchFileName = new QAction(BDLSClass);
        actionSearchFileName->setObjectName(QString::fromUtf8("actionSearchFileName"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/BDLS/icons/search_files.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSearchFileName->setIcon(icon5);
        actionLockFile = new QAction(BDLSClass);
        actionLockFile->setObjectName(QString::fromUtf8("actionLockFile"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/BDLS/icons/lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLockFile->setIcon(icon6);
        actionUnLockFile = new QAction(BDLSClass);
        actionUnLockFile->setObjectName(QString::fromUtf8("actionUnLockFile"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/BDLS/icons/unlock.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUnLockFile->setIcon(icon7);
        centralWidget = new QWidget(BDLSClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setStyleSheet(QString::fromUtf8(" QTreeView {\n"
"     show-decoration-selected: 1;\n"
" }\n"
"\n"
" QTreeView::item {\n"
"      border: 1px solid #d9d9d9;\n"
"     border-top-color: transparent;\n"
"     border-bottom-color: transparent;\n"
" }\n"
"\n"
" QTreeView::item:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);\n"
"     border: 1px solid #bfcde4;\n"
" }\n"
"\n"
" QTreeView::item:selected {\n"
"     border: 1px solid #567dbc;\n"
" }\n"
"\n"
" QTreeView::item:selected:active{\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);\n"
" }\n"
"\n"
" QTreeView::item:selected:!active {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);\n"
" }\n"
"\n"
"QHeaderView::section{background-color: rgb(200, 200, 200);font:bold;}"));

        horizontalLayout->addWidget(treeView);

        BDLSClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(BDLSClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setBaseSize(QSize(24, 24));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        mainToolBar->setFont(font);
        mainToolBar->setAutoFillBackground(false);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        BDLSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BDLSClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BDLSClass->setStatusBar(statusBar);

        retranslateUi(BDLSClass);

        QMetaObject::connectSlotsByName(BDLSClass);
    } // setupUi

    void retranslateUi(QMainWindow *BDLSClass)
    {
        BDLSClass->setWindowTitle(QCoreApplication::translate("BDLSClass", "BDLS", nullptr));
        actionAddRow->setText(QCoreApplication::translate("BDLSClass", "\355\226\211 \354\266\224\352\260\200", nullptr));
#if QT_CONFIG(tooltip)
        actionAddRow->setToolTip(QCoreApplication::translate("BDLSClass", "\355\226\211 \354\266\224\352\260\200", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDelRow->setText(QCoreApplication::translate("BDLSClass", "\355\226\211 \354\202\255\354\240\234", nullptr));
#if QT_CONFIG(tooltip)
        actionDelRow->setToolTip(QCoreApplication::translate("BDLSClass", "\355\226\211 \354\202\255\354\240\234", nullptr));
#endif // QT_CONFIG(tooltip)
        actionDBUpdate->setText(QCoreApplication::translate("BDLSClass", "DB \354\227\205\353\215\260\354\235\264\355\212\270", nullptr));
#if QT_CONFIG(tooltip)
        actionDBUpdate->setToolTip(QCoreApplication::translate("BDLSClass", "DB \354\227\205\353\215\260\354\235\264\355\212\270", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSearchList->setText(QCoreApplication::translate("BDLSClass", "\353\246\254\354\212\244\355\212\270 \352\262\200\354\203\211", nullptr));
#if QT_CONFIG(tooltip)
        actionSearchList->setToolTip(QCoreApplication::translate("BDLSClass", "\353\246\254\354\212\244\355\212\270 \352\262\200\354\203\211", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSearchContent->setText(QCoreApplication::translate("BDLSClass", "\353\202\264\354\232\251 \352\262\200\354\203\211", nullptr));
#if QT_CONFIG(tooltip)
        actionSearchContent->setToolTip(QCoreApplication::translate("BDLSClass", "\353\202\264\354\232\251 \352\262\200\354\203\211", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSearchFileName->setText(QCoreApplication::translate("BDLSClass", "\355\214\214\354\235\274\353\252\205 \352\262\200\354\203\211", nullptr));
#if QT_CONFIG(tooltip)
        actionSearchFileName->setToolTip(QCoreApplication::translate("BDLSClass", "\355\214\214\354\235\274\353\252\205 \352\262\200\354\203\211", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLockFile->setText(QCoreApplication::translate("BDLSClass", "\354\225\224\355\230\270 \354\204\244\354\240\225", nullptr));
#if QT_CONFIG(tooltip)
        actionLockFile->setToolTip(QCoreApplication::translate("BDLSClass", "\354\225\224\355\230\270 \354\204\244\354\240\225", nullptr));
#endif // QT_CONFIG(tooltip)
        actionUnLockFile->setText(QCoreApplication::translate("BDLSClass", "\354\225\224\355\230\270 \355\225\264\354\240\234", nullptr));
#if QT_CONFIG(tooltip)
        actionUnLockFile->setToolTip(QCoreApplication::translate("BDLSClass", "\354\225\224\355\230\270 \355\225\264\354\240\234", nullptr));
#endif // QT_CONFIG(tooltip)
        mainToolBar->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class BDLSClass: public Ui_BDLSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BDLS_H
