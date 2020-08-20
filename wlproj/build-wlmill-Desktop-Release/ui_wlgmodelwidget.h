/********************************************************************************
** Form generated from reading UI file 'wlgmodelwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLGMODELWIDGET_H
#define UI_WLGMODELWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLGModelWidget
{
public:

    void setupUi(QWidget *WLGModelWidget)
    {
        if (WLGModelWidget->objectName().isEmpty())
            WLGModelWidget->setObjectName(QString::fromUtf8("WLGModelWidget"));
        WLGModelWidget->resize(571, 467);

        retranslateUi(WLGModelWidget);

        QMetaObject::connectSlotsByName(WLGModelWidget);
    } // setupUi

    void retranslateUi(QWidget *WLGModelWidget)
    {
        WLGModelWidget->setWindowTitle(QApplication::translate("WLGModelWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLGModelWidget: public Ui_WLGModelWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLGMODELWIDGET_H
