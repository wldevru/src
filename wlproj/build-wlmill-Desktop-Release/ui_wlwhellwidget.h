/********************************************************************************
** Form generated from reading UI file 'wlwhellwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLWHELLWIDGET_H
#define UI_WLWHELLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include "wleditiowidget.h"

QT_BEGIN_NAMESPACE

class Ui_WLWhellWidget
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *cbInv;
    QGroupBox *gbInV;
    QGridLayout *gridLayout_2;
    WLEditIOWidget *editInV;
    QGroupBox *gbInX;
    QGridLayout *gridLayout_7;
    QHBoxLayout *vLayoutInputX;
    QCheckBox *cbInXbianry;
    QGroupBox *gbInA;
    QGridLayout *gridLayout_6;
    QHBoxLayout *vLayoutInputAxis;
    QCheckBox *cbInAbianry;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    WLEditIOWidget *editOutENB;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WLWhellWidget)
    {
        if (WLWhellWidget->objectName().isEmpty())
            WLWhellWidget->setObjectName(QString::fromUtf8("WLWhellWidget"));
        WLWhellWidget->resize(595, 266);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WLWhellWidget->sizePolicy().hasHeightForWidth());
        WLWhellWidget->setSizePolicy(sizePolicy);
        WLWhellWidget->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(WLWhellWidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(WLWhellWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbInv = new QCheckBox(groupBox);
        cbInv->setObjectName(QString::fromUtf8("cbInv"));

        gridLayout->addWidget(cbInv, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 3, 1, 1);

        gbInV = new QGroupBox(WLWhellWidget);
        gbInV->setObjectName(QString::fromUtf8("gbInV"));
        gbInV->setCheckable(true);
        gridLayout_2 = new QGridLayout(gbInV);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        editInV = new WLEditIOWidget(gbInV);
        editInV->setObjectName(QString::fromUtf8("editInV"));

        gridLayout_2->addWidget(editInV, 0, 0, 1, 1);


        gridLayout_3->addWidget(gbInV, 1, 1, 1, 1);

        gbInX = new QGroupBox(WLWhellWidget);
        gbInX->setObjectName(QString::fromUtf8("gbInX"));
        gbInX->setCheckable(true);
        gridLayout_7 = new QGridLayout(gbInX);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        vLayoutInputX = new QHBoxLayout();
        vLayoutInputX->setObjectName(QString::fromUtf8("vLayoutInputX"));

        gridLayout_7->addLayout(vLayoutInputX, 1, 0, 1, 1);

        cbInXbianry = new QCheckBox(gbInX);
        cbInXbianry->setObjectName(QString::fromUtf8("cbInXbianry"));

        gridLayout_7->addWidget(cbInXbianry, 0, 0, 1, 1);


        gridLayout_3->addWidget(gbInX, 1, 0, 1, 1);

        gbInA = new QGroupBox(WLWhellWidget);
        gbInA->setObjectName(QString::fromUtf8("gbInA"));
        gbInA->setCheckable(true);
        gridLayout_6 = new QGridLayout(gbInA);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        vLayoutInputAxis = new QHBoxLayout();
        vLayoutInputAxis->setObjectName(QString::fromUtf8("vLayoutInputAxis"));

        gridLayout_6->addLayout(vLayoutInputAxis, 1, 0, 1, 1);

        cbInAbianry = new QCheckBox(gbInA);
        cbInAbianry->setObjectName(QString::fromUtf8("cbInAbianry"));

        gridLayout_6->addWidget(cbInAbianry, 0, 0, 1, 1);


        gridLayout_3->addWidget(gbInA, 0, 0, 1, 4);

        groupBox_4 = new QGroupBox(WLWhellWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        editOutENB = new WLEditIOWidget(groupBox_4);
        editOutENB->setObjectName(QString::fromUtf8("editOutENB"));

        gridLayout_5->addWidget(editOutENB, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 1, 2, 1, 1);

        buttonBox = new QDialogButtonBox(WLWhellWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        gridLayout_3->addWidget(buttonBox, 2, 2, 1, 1);


        retranslateUi(WLWhellWidget);
        QObject::connect(buttonBox, SIGNAL(accepted()), WLWhellWidget, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WLWhellWidget, SLOT(reject()));

        QMetaObject::connectSlotsByName(WLWhellWidget);
    } // setupUi

    void retranslateUi(QDialog *WLWhellWidget)
    {
        WLWhellWidget->setWindowTitle(QApplication::translate("WLWhellWidget", "Edit Whell", nullptr));
        groupBox->setTitle(QApplication::translate("WLWhellWidget", "Other", nullptr));
        cbInv->setText(QApplication::translate("WLWhellWidget", "inverse", nullptr));
        gbInV->setTitle(QApplication::translate("WLWhellWidget", "Input", nullptr));
        gbInX->setTitle(QApplication::translate("WLWhellWidget", "Input", nullptr));
        cbInXbianry->setText(QApplication::translate("WLWhellWidget", "binary", nullptr));
        gbInA->setTitle(QApplication::translate("WLWhellWidget", "Input", nullptr));
        cbInAbianry->setText(QApplication::translate("WLWhellWidget", "binary", nullptr));
        groupBox_4->setTitle(QApplication::translate("WLWhellWidget", "Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLWhellWidget: public Ui_WLWhellWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLWHELLWIDGET_H
