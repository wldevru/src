/********************************************************************************
** Form generated from reading UI file 'wlmessmanager.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLMESSMANAGER_H
#define UI_WLMESSMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLMessManager
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButtonCErr;

    void setupUi(QWidget *WLMessManager)
    {
        if (WLMessManager->objectName().isEmpty())
            WLMessManager->setObjectName(QString::fromUtf8("WLMessManager"));
        WLMessManager->resize(633, 43);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WLMessManager->sizePolicy().hasHeightForWidth());
        WLMessManager->setSizePolicy(sizePolicy);
        WLMessManager->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(WLMessManager);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(WLMessManager);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setText(QString::fromUtf8("icon"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(WLMessManager);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(500, 0));
        comboBox->setMinimumContentsLength(0);
        comboBox->setModelColumn(0);

        horizontalLayout->addWidget(comboBox);

        pushButtonCErr = new QPushButton(WLMessManager);
        pushButtonCErr->setObjectName(QString::fromUtf8("pushButtonCErr"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonCErr->sizePolicy().hasHeightForWidth());
        pushButtonCErr->setSizePolicy(sizePolicy2);
        pushButtonCErr->setCheckable(false);

        horizontalLayout->addWidget(pushButtonCErr);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(WLMessManager);

        QMetaObject::connectSlotsByName(WLMessManager);
    } // setupUi

    void retranslateUi(QWidget *WLMessManager)
    {
        WLMessManager->setWindowTitle(QApplication::translate("WLMessManager", "WLMessManager", nullptr));
        pushButtonCErr->setText(QApplication::translate("WLMessManager", "clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLMessManager: public Ui_WLMessManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLMESSMANAGER_H
