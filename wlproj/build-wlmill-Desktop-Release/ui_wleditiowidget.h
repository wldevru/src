/********************************************************************************
** Form generated from reading UI file 'wleditiowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLEDITIOWIDGET_H
#define UI_WLEDITIOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLEditIOWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox;

    void setupUi(QWidget *WLEditIOWidget)
    {
        if (WLEditIOWidget->objectName().isEmpty())
            WLEditIOWidget->setObjectName(QString::fromUtf8("WLEditIOWidget"));
        WLEditIOWidget->resize(192, 47);
        WLEditIOWidget->setWindowOpacity(1.000000000000000);
        gridLayout = new QGridLayout(WLEditIOWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(WLEditIOWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(WLEditIOWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setButtonSymbols(QAbstractSpinBox::PlusMinus);

        gridLayout->addWidget(spinBox, 0, 1, 1, 1);


        retranslateUi(WLEditIOWidget);

        QMetaObject::connectSlotsByName(WLEditIOWidget);
    } // setupUi

    void retranslateUi(QWidget *WLEditIOWidget)
    {
        WLEditIOWidget->setWindowTitle(QApplication::translate("WLEditIOWidget", "Form", nullptr));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("WLEditIOWidget", "right key - menu", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("WLEditIOWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLEditIOWidget: public Ui_WLEditIOWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLEDITIOWIDGET_H
