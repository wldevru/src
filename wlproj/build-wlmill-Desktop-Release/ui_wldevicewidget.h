/********************************************************************************
** Form generated from reading UI file 'wldevicewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLDEVICEWIDGET_H
#define UI_WLDEVICEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLDeviceWidget
{
public:
    QGridLayout *gridLayout;
    QComboBox *cbDevice;
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QWidget *WLDeviceWidget)
    {
        if (WLDeviceWidget->objectName().isEmpty())
            WLDeviceWidget->setObjectName(QString::fromUtf8("WLDeviceWidget"));
        WLDeviceWidget->resize(400, 89);
        gridLayout = new QGridLayout(WLDeviceWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbDevice = new QComboBox(WLDeviceWidget);
        cbDevice->setObjectName(QString::fromUtf8("cbDevice"));

        gridLayout->addWidget(cbDevice, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(WLDeviceWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);

        label = new QLabel(WLDeviceWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setText(QString::fromUtf8("Please select device:"));

        gridLayout->addWidget(label, 0, 0, 1, 2);


        retranslateUi(WLDeviceWidget);

        QMetaObject::connectSlotsByName(WLDeviceWidget);
    } // setupUi

    void retranslateUi(QWidget *WLDeviceWidget)
    {
        WLDeviceWidget->setWindowTitle(QApplication::translate("WLDeviceWidget", "Select Device", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLDeviceWidget: public Ui_WLDeviceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLDEVICEWIDGET_H
