/********************************************************************************
** Form generated from reading UI file 'widgetBottomView.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETBOTTOMVIEW_H
#define UI_WIDGETBOTTOMVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widgetBottomView
{
public:

    void setupUi(QWidget *widgetBottomView)
    {
        if (widgetBottomView->objectName().isEmpty())
            widgetBottomView->setObjectName("widgetBottomView");
        widgetBottomView->resize(647, 507);

        retranslateUi(widgetBottomView);

        QMetaObject::connectSlotsByName(widgetBottomView);
    } // setupUi

    void retranslateUi(QWidget *widgetBottomView)
    {
        widgetBottomView->setWindowTitle(QCoreApplication::translate("widgetBottomView", "widgetBottomView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widgetBottomView: public Ui_widgetBottomView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETBOTTOMVIEW_H
