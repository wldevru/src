/********************************************************************************
** Form generated from reading UI file 'wledittext.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLEDITTEXT_H
#define UI_WLEDITTEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_WLEditText
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WLEditText)
    {
        if (WLEditText->objectName().isEmpty())
            WLEditText->setObjectName(QString::fromUtf8("WLEditText"));
        WLEditText->resize(475, 576);
        WLEditText->setModal(true);
        gridLayout = new QGridLayout(WLEditText);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(WLEditText);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        textEdit = new QTextEdit(WLEditText);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(WLEditText);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);


        retranslateUi(WLEditText);
        QObject::connect(buttonBox, SIGNAL(accepted()), WLEditText, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WLEditText, SLOT(reject()));

        QMetaObject::connectSlotsByName(WLEditText);
    } // setupUi

    void retranslateUi(QDialog *WLEditText)
    {
        WLEditText->setWindowTitle(QApplication::translate("WLEditText", "Edit text", nullptr));
        label->setText(QApplication::translate("WLEditText", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLEditText: public Ui_WLEditText {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLEDITTEXT_H
