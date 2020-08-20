/********************************************************************************
** Form generated from reading UI file 'wleditpoint.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLEDITPOINT_H
#define UI_WLEDITPOINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WLEditPoint
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonOk;
    QPushButton *pushButtonCancle;
    QLabel *label;

    void setupUi(QDialog *WLEditPoint)
    {
        if (WLEditPoint->objectName().isEmpty())
            WLEditPoint->setObjectName(QString::fromUtf8("WLEditPoint"));
        WLEditPoint->setEnabled(true);
        WLEditPoint->resize(246, 245);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WLEditPoint->sizePolicy().hasHeightForWidth());
        WLEditPoint->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(WLEditPoint);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox = new QGroupBox(WLEditPoint);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 2);

        pushButtonOk = new QPushButton(WLEditPoint);
        pushButtonOk->setObjectName(QString::fromUtf8("pushButtonOk"));

        gridLayout_2->addWidget(pushButtonOk, 2, 0, 1, 1);

        pushButtonCancle = new QPushButton(WLEditPoint);
        pushButtonCancle->setObjectName(QString::fromUtf8("pushButtonCancle"));

        gridLayout_2->addWidget(pushButtonCancle, 2, 1, 1, 1);

        label = new QLabel(WLEditPoint);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label, 0, 0, 1, 2);


        retranslateUi(WLEditPoint);

        QMetaObject::connectSlotsByName(WLEditPoint);
    } // setupUi

    void retranslateUi(QDialog *WLEditPoint)
    {
        WLEditPoint->setWindowTitle(QApplication::translate("WLEditPoint", "WLEditPoint", nullptr));
        groupBox->setTitle(QApplication::translate("WLEditPoint", "Coordinates", nullptr));
        pushButtonOk->setText(QApplication::translate("WLEditPoint", "Accept", nullptr));
        pushButtonCancle->setText(QApplication::translate("WLEditPoint", "Cancle", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WLEditPoint: public Ui_WLEditPoint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLEDITPOINT_H
