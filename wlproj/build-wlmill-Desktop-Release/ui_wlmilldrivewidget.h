/********************************************************************************
** Form generated from reading UI file 'wlmilldrivewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLMILLDRIVEWIDGET_H
#define UI_WLMILLDRIVEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_WLMillDriveWidget
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QDoubleSpinBox *sbBacklash;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *WLMillDriveWidget)
    {
        if (WLMillDriveWidget->objectName().isEmpty())
            WLMillDriveWidget->setObjectName(QString::fromUtf8("WLMillDriveWidget"));
        WLMillDriveWidget->resize(400, 300);
        gridLayout_2 = new QGridLayout(WLMillDriveWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(WLMillDriveWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Save);

        gridLayout_2->addWidget(buttonBox, 2, 1, 1, 1);

        groupBox = new QGroupBox(WLMillDriveWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sbBacklash = new QDoubleSpinBox(groupBox);
        sbBacklash->setObjectName(QString::fromUtf8("sbBacklash"));
        sbBacklash->setDecimals(4);
        sbBacklash->setMaximum(20.000000000000000);

        gridLayout->addWidget(sbBacklash, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);


        retranslateUi(WLMillDriveWidget);
        QObject::connect(buttonBox, SIGNAL(accepted()), WLMillDriveWidget, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WLMillDriveWidget, SLOT(reject()));

        QMetaObject::connectSlotsByName(WLMillDriveWidget);
    } // setupUi

    void retranslateUi(QDialog *WLMillDriveWidget)
    {
        WLMillDriveWidget->setWindowTitle(QApplication::translate("WLMillDriveWidget", "mill", nullptr));
        groupBox->setTitle(QApplication::translate("WLMillDriveWidget", "backlash", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLMillDriveWidget: public Ui_WLMillDriveWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLMILLDRIVEWIDGET_H
