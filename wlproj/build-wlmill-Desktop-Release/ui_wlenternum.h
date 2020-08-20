/********************************************************************************
** Form generated from reading UI file 'wlenternum.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLENTERNUM_H
#define UI_WLENTERNUM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_WLEnterNum
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label;

    void setupUi(QDialog *WLEnterNum)
    {
        if (WLEnterNum->objectName().isEmpty())
            WLEnterNum->setObjectName(QString::fromUtf8("WLEnterNum"));
        WLEnterNum->resize(227, 67);
        WLEnterNum->setSizeGripEnabled(false);
        WLEnterNum->setModal(true);
        gridLayout = new QGridLayout(WLEnterNum);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(WLEnterNum);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        gridLayout->addWidget(buttonBox, 1, 2, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(WLEnterNum);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setDecimals(3);
        doubleSpinBox->setMinimum(-100000.000000000000000);
        doubleSpinBox->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBox, 0, 2, 1, 1);

        label = new QLabel(WLEnterNum);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(WLEnterNum);
        QObject::connect(buttonBox, SIGNAL(accepted()), WLEnterNum, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WLEnterNum, SLOT(reject()));

        QMetaObject::connectSlotsByName(WLEnterNum);
    } // setupUi

    void retranslateUi(QDialog *WLEnterNum)
    {
        WLEnterNum->setWindowTitle(QApplication::translate("WLEnterNum", "Enter value", nullptr));
        label->setText(QApplication::translate("WLEnterNum", "Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLEnterNum: public Ui_WLEnterNum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLENTERNUM_H
