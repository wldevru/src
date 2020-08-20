/********************************************************************************
** Form generated from reading UI file 'wliowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLIOWIDGET_H
#define UI_WLIOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLIOPutWidget
{
public:

    void setupUi(QWidget *WLIOWidget)
    {
        if (WLIOWidget->objectName().isEmpty())
            WLIOWidget->setObjectName(QString::fromUtf8("WLIOWidget"));
        WLIOWidget->resize(400, 300);

        retranslateUi(WLIOWidget);

        QMetaObject::connectSlotsByName(WLIOWidget);
    } // setupUi

    void retranslateUi(QWidget *WLIOWidget)
    {
        WLIOWidget->setWindowTitle(QApplication::translate("WLIOPutWidget", "Input/Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLIOPutWidget: public Ui_WLIOPutWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLIOWIDGET_H
