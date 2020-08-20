/********************************************************************************
** Form generated from reading UI file 'wlenterstring.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLENTERSTRING_H
#define UI_WLENTERSTRING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_WLEnterString
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WLEnterString)
    {
        if (WLEnterString->objectName().isEmpty())
            WLEnterString->setObjectName(QString::fromUtf8("WLEnterString"));
        WLEnterString->resize(400, 67);
        WLEnterString->setModal(true);
        gridLayout = new QGridLayout(WLEnterString);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(WLEnterString);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(WLEnterString);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(WLEnterString);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(WLEnterString);
        QObject::connect(buttonBox, SIGNAL(accepted()), WLEnterString, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WLEnterString, SLOT(reject()));

        QMetaObject::connectSlotsByName(WLEnterString);
    } // setupUi

    void retranslateUi(QDialog *WLEnterString)
    {
        WLEnterString->setWindowTitle(QApplication::translate("WLEnterString", "Input String", nullptr));
        label->setText(QApplication::translate("WLEnterString", "String", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLEnterString: public Ui_WLEnterString {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLENTERSTRING_H
