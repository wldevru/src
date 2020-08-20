/********************************************************************************
** Form generated from reading UI file 'wlpamwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLPAMWIDGET_H
#define UI_WLPAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_WLPamWidget
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *sbVst;
    QDoubleSpinBox *sbAac;
    QDoubleSpinBox *sbVma;
    QDoubleSpinBox *sbAde;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_3;
    QComboBox *cbEditName;

    void setupUi(QDialog *WLPamWidget)
    {
        if (WLPamWidget->objectName().isEmpty())
            WLPamWidget->setObjectName(QString::fromUtf8("WLPamWidget"));
        WLPamWidget->resize(484, 151);
        WLPamWidget->setMinimumSize(QSize(0, 150));
        gridLayout = new QGridLayout(WLPamWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(WLPamWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        sbVst = new QDoubleSpinBox(WLPamWidget);
        sbVst->setObjectName(QString::fromUtf8("sbVst"));
        sbVst->setMinimumSize(QSize(70, 0));
        sbVst->setFrame(false);
        sbVst->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbVst->setMaximum(1000000.000000000000000);

        horizontalLayout->addWidget(sbVst);

        sbAac = new QDoubleSpinBox(WLPamWidget);
        sbAac->setObjectName(QString::fromUtf8("sbAac"));
        sbAac->setMinimumSize(QSize(70, 0));
        sbAac->setFrame(false);
        sbAac->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbAac->setDecimals(2);

        horizontalLayout->addWidget(sbAac);

        sbVma = new QDoubleSpinBox(WLPamWidget);
        sbVma->setObjectName(QString::fromUtf8("sbVma"));
        sbVma->setMinimumSize(QSize(70, 0));
        sbVma->setFrame(false);
        sbVma->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbVma->setMaximum(1000000.000000000000000);

        horizontalLayout->addWidget(sbVma);

        sbAde = new QDoubleSpinBox(WLPamWidget);
        sbAde->setObjectName(QString::fromUtf8("sbAde"));
        sbAde->setMinimumSize(QSize(70, 0));
        sbAde->setFrame(false);
        sbAde->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbAde->setDecimals(2);

        horizontalLayout->addWidget(sbAde);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(WLPamWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
#ifndef QT_NO_ACCESSIBILITY
        label_2->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY

        horizontalLayout_2->addWidget(label_2);

        label = new QLabel(WLPamWidget);
        label->setObjectName(QString::fromUtf8("label"));
#ifndef QT_NO_ACCESSIBILITY
        label->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY

        horizontalLayout_2->addWidget(label);

        label_4 = new QLabel(WLPamWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
#ifndef QT_NO_ACCESSIBILITY
        label_4->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY

        horizontalLayout_2->addWidget(label_4);

        label_3 = new QLabel(WLPamWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
#ifndef QT_NO_ACCESSIBILITY
        label_3->setAccessibleDescription(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY

        horizontalLayout_2->addWidget(label_3);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 2);

        cbEditName = new QComboBox(WLPamWidget);
        cbEditName->setObjectName(QString::fromUtf8("cbEditName"));
        cbEditName->setMinimumSize(QSize(128, 0));
        cbEditName->setEditable(true);

        gridLayout->addWidget(cbEditName, 1, 0, 1, 1);


        retranslateUi(WLPamWidget);

        QMetaObject::connectSlotsByName(WLPamWidget);
    } // setupUi

    void retranslateUi(QDialog *WLPamWidget)
    {
        WLPamWidget->setWindowTitle(QApplication::translate("WLPamWidget", "Motion parameters", nullptr));
        sbVst->setPrefix(QString());
        sbVst->setSuffix(QString());
        label_2->setText(QApplication::translate("WLPamWidget", "Vst (1/s)", nullptr));
        label->setText(QApplication::translate("WLPamWidget", "Acc (1/s^2)", nullptr));
        label_4->setText(QApplication::translate("WLPamWidget", "Vma(1/s)", nullptr));
        label_3->setText(QApplication::translate("WLPamWidget", "Ade (1/s^2)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLPamWidget: public Ui_WLPamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLPAMWIDGET_H
