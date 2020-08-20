/********************************************************************************
** Form generated from reading UI file 'wlpamlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLPAMLISTWIDGET_H
#define UI_WLPAMLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_WLPamListWidget
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QTableWidget *tableWidget;
    QPushButton *pbAdd;
    QPushButton *pbRem;

    void setupUi(QDialog *WLPamListWidget)
    {
        if (WLPamListWidget->objectName().isEmpty())
            WLPamListWidget->setObjectName(QString::fromUtf8("WLPamListWidget"));
        WLPamListWidget->setWindowModality(Qt::WindowModal);
        WLPamListWidget->resize(400, 300);
        gridLayout = new QGridLayout(WLPamListWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(WLPamListWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Save);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 2);

        tableWidget = new QTableWidget(WLPamListWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidget, 1, 0, 1, 2);

        pbAdd = new QPushButton(WLPamListWidget);
        pbAdd->setObjectName(QString::fromUtf8("pbAdd"));

        gridLayout->addWidget(pbAdd, 0, 0, 1, 1);

        pbRem = new QPushButton(WLPamListWidget);
        pbRem->setObjectName(QString::fromUtf8("pbRem"));

        gridLayout->addWidget(pbRem, 0, 1, 1, 1);


        retranslateUi(WLPamListWidget);
        QObject::connect(buttonBox, SIGNAL(accepted()), WLPamListWidget, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WLPamListWidget, SLOT(reject()));

        QMetaObject::connectSlotsByName(WLPamListWidget);
    } // setupUi

    void retranslateUi(QDialog *WLPamListWidget)
    {
        WLPamListWidget->setWindowTitle(QApplication::translate("WLPamListWidget", "motion parameters", nullptr));
        pbAdd->setText(QApplication::translate("WLPamListWidget", "add", nullptr));
        pbRem->setText(QApplication::translate("WLPamListWidget", "remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLPamListWidget: public Ui_WLPamListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLPAMLISTWIDGET_H
