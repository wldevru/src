/********************************************************************************
** Form generated from reading UI file 'wlpositionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLPOSITIONWIDGET_H
#define UI_WLPOSITIONWIDGET_H

#include <QtCore/QVariant>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "wllabel.h"

QT_BEGIN_NAMESPACE

class Ui_WLPositionWidget
{
public:
    QGridLayout *gridLayout_2;
    QToolButton *pbRotSC;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QQuickWidget *qwAxisLabelPosY;
    QQuickWidget *qwAxisLabelPosX;
    QQuickWidget *qwAxisLabelPosZ;
    QQuickWidget *qwAxisLabelPosB;
    QQuickWidget *qwAxisLabelPosA;
    QToolButton *pbReset;
    QSpacerItem *verticalSpacer;
    QToolButton *pbHome;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *labelActivGCode;
    QComboBox *cbExGCode;
    QLabel *labelConnect;
    QToolButton *pbOnMachine;
    WLLabel *rotSK;

    void setupUi(QWidget *WLPositionWidget)
    {
        if (WLPositionWidget->objectName().isEmpty())
            WLPositionWidget->setObjectName(QString::fromUtf8("WLPositionWidget"));
        WLPositionWidget->resize(295, 433);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WLPositionWidget->sizePolicy().hasHeightForWidth());
        WLPositionWidget->setSizePolicy(sizePolicy);
        WLPositionWidget->setMaximumSize(QSize(999, 99999));
        gridLayout_2 = new QGridLayout(WLPositionWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pbRotSC = new QToolButton(WLPositionWidget);
        pbRotSC->setObjectName(QString::fromUtf8("pbRotSC"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pbRotSC->sizePolicy().hasHeightForWidth());
        pbRotSC->setSizePolicy(sizePolicy1);
        pbRotSC->setMinimumSize(QSize(50, 50));
        pbRotSC->setFocusPolicy(Qt::NoFocus);
        pbRotSC->setIconSize(QSize(48, 48));
        pbRotSC->setCheckable(false);

        gridLayout_2->addWidget(pbRotSC, 0, 3, 1, 1);

        groupBox = new QGroupBox(WLPositionWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        qwAxisLabelPosY = new QQuickWidget(groupBox);
        qwAxisLabelPosY->setObjectName(QString::fromUtf8("qwAxisLabelPosY"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(qwAxisLabelPosY->sizePolicy().hasHeightForWidth());
        qwAxisLabelPosY->setSizePolicy(sizePolicy3);
        qwAxisLabelPosY->setMinimumSize(QSize(0, 30));
        qwAxisLabelPosY->setResizeMode(QQuickWidget::SizeRootObjectToView);
        qwAxisLabelPosY->setSource(QUrl(QString::fromUtf8("qrc:/AxisPosLabel.qml")));

        gridLayout_4->addWidget(qwAxisLabelPosY, 1, 0, 1, 1);

        qwAxisLabelPosX = new QQuickWidget(groupBox);
        qwAxisLabelPosX->setObjectName(QString::fromUtf8("qwAxisLabelPosX"));
        sizePolicy3.setHeightForWidth(qwAxisLabelPosX->sizePolicy().hasHeightForWidth());
        qwAxisLabelPosX->setSizePolicy(sizePolicy3);
        qwAxisLabelPosX->setMinimumSize(QSize(0, 30));
        qwAxisLabelPosX->setResizeMode(QQuickWidget::SizeRootObjectToView);
        qwAxisLabelPosX->setSource(QUrl(QString::fromUtf8("qrc:/AxisPosLabel.qml")));

        gridLayout_4->addWidget(qwAxisLabelPosX, 0, 0, 1, 1);

        qwAxisLabelPosZ = new QQuickWidget(groupBox);
        qwAxisLabelPosZ->setObjectName(QString::fromUtf8("qwAxisLabelPosZ"));
        sizePolicy3.setHeightForWidth(qwAxisLabelPosZ->sizePolicy().hasHeightForWidth());
        qwAxisLabelPosZ->setSizePolicy(sizePolicy3);
        qwAxisLabelPosZ->setMinimumSize(QSize(0, 30));
        qwAxisLabelPosZ->setResizeMode(QQuickWidget::SizeRootObjectToView);
        qwAxisLabelPosZ->setSource(QUrl(QString::fromUtf8("qrc:/AxisPosLabel.qml")));

        gridLayout_4->addWidget(qwAxisLabelPosZ, 2, 0, 1, 1);

        qwAxisLabelPosB = new QQuickWidget(groupBox);
        qwAxisLabelPosB->setObjectName(QString::fromUtf8("qwAxisLabelPosB"));
        sizePolicy3.setHeightForWidth(qwAxisLabelPosB->sizePolicy().hasHeightForWidth());
        qwAxisLabelPosB->setSizePolicy(sizePolicy3);
        qwAxisLabelPosB->setMinimumSize(QSize(0, 30));
        qwAxisLabelPosB->setResizeMode(QQuickWidget::SizeRootObjectToView);
        qwAxisLabelPosB->setSource(QUrl(QString::fromUtf8("qrc:/AxisPosLabel.qml")));

        gridLayout_4->addWidget(qwAxisLabelPosB, 5, 0, 1, 1);

        qwAxisLabelPosA = new QQuickWidget(groupBox);
        qwAxisLabelPosA->setObjectName(QString::fromUtf8("qwAxisLabelPosA"));
        sizePolicy3.setHeightForWidth(qwAxisLabelPosA->sizePolicy().hasHeightForWidth());
        qwAxisLabelPosA->setSizePolicy(sizePolicy3);
        qwAxisLabelPosA->setMinimumSize(QSize(0, 30));
        qwAxisLabelPosA->setResizeMode(QQuickWidget::SizeRootObjectToView);
        qwAxisLabelPosA->setSource(QUrl(QString::fromUtf8("qrc:/AxisPosLabel.qml")));

        gridLayout_4->addWidget(qwAxisLabelPosA, 3, 0, 1, 1);


        gridLayout->addLayout(gridLayout_4, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 6);

        pbReset = new QToolButton(WLPositionWidget);
        pbReset->setObjectName(QString::fromUtf8("pbReset"));
        pbReset->setEnabled(true);
        sizePolicy1.setHeightForWidth(pbReset->sizePolicy().hasHeightForWidth());
        pbReset->setSizePolicy(sizePolicy1);
        pbReset->setMinimumSize(QSize(50, 50));
        pbReset->setFocusPolicy(Qt::NoFocus);
        pbReset->setText(QString::fromUtf8("RESET"));
        pbReset->setIconSize(QSize(48, 48));
        pbReset->setCheckable(false);

        gridLayout_2->addWidget(pbReset, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        pbHome = new QToolButton(WLPositionWidget);
        pbHome->setObjectName(QString::fromUtf8("pbHome"));
        sizePolicy1.setHeightForWidth(pbHome->sizePolicy().hasHeightForWidth());
        pbHome->setSizePolicy(sizePolicy1);
        pbHome->setMinimumSize(QSize(50, 50));
        pbHome->setFocusPolicy(Qt::NoFocus);
        pbHome->setIconSize(QSize(48, 48));
        pbHome->setCheckable(false);

        gridLayout_2->addWidget(pbHome, 0, 2, 1, 1);

        groupBox_2 = new QGroupBox(WLPositionWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labelActivGCode = new QLabel(groupBox_2);
        labelActivGCode->setObjectName(QString::fromUtf8("labelActivGCode"));
        QFont font;
        font.setPointSize(12);
        labelActivGCode->setFont(font);

        gridLayout_3->addWidget(labelActivGCode, 3, 0, 1, 3);

        cbExGCode = new QComboBox(groupBox_2);
        cbExGCode->setObjectName(QString::fromUtf8("cbExGCode"));
        cbExGCode->setFont(font);
        cbExGCode->setEditable(true);
        cbExGCode->setInsertPolicy(QComboBox::InsertAtTop);

        gridLayout_3->addWidget(cbExGCode, 1, 0, 1, 3);


        gridLayout_2->addWidget(groupBox_2, 2, 0, 1, 6);

        labelConnect = new QLabel(WLPositionWidget);
        labelConnect->setObjectName(QString::fromUtf8("labelConnect"));

        gridLayout_2->addWidget(labelConnect, 0, 5, 1, 1);

        pbOnMachine = new QToolButton(WLPositionWidget);
        pbOnMachine->setObjectName(QString::fromUtf8("pbOnMachine"));
        sizePolicy1.setHeightForWidth(pbOnMachine->sizePolicy().hasHeightForWidth());
        pbOnMachine->setSizePolicy(sizePolicy1);
        pbOnMachine->setMinimumSize(QSize(50, 50));
        pbOnMachine->setFocusPolicy(Qt::NoFocus);
        pbOnMachine->setIconSize(QSize(48, 48));
        pbOnMachine->setCheckable(true);

        gridLayout_2->addWidget(pbOnMachine, 0, 0, 1, 1);

        rotSK = new WLLabel(WLPositionWidget);
        rotSK->setObjectName(QString::fromUtf8("rotSK"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(rotSK->sizePolicy().hasHeightForWidth());
        rotSK->setSizePolicy(sizePolicy4);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setWeight(50);
        rotSK->setFont(font1);
        rotSK->setFrameShape(QFrame::NoFrame);
        rotSK->setFrameShadow(QFrame::Sunken);
        rotSK->setText(QString::fromUtf8("A:123456"));

        gridLayout_2->addWidget(rotSK, 0, 4, 1, 1);


        retranslateUi(WLPositionWidget);

        QMetaObject::connectSlotsByName(WLPositionWidget);
    } // setupUi

    void retranslateUi(QWidget *WLPositionWidget)
    {
        WLPositionWidget->setWindowTitle(QApplication::translate("WLPositionWidget", "WLPositionWidget", nullptr));
#ifndef QT_NO_TOOLTIP
        pbRotSC->setToolTip(QApplication::translate("WLPositionWidget", "coordinate rotation", nullptr));
#endif // QT_NO_TOOLTIP
        pbRotSC->setText(QString());
        groupBox->setTitle(QApplication::translate("WLPositionWidget", "Position", nullptr));
#ifndef QT_NO_TOOLTIP
        pbReset->setToolTip(QApplication::translate("WLPositionWidget", "(esc)", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        pbReset->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_SHORTCUT
        pbReset->setShortcut(QApplication::translate("WLPositionWidget", "Esc", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        pbHome->setToolTip(QApplication::translate("WLPositionWidget", "go home position", nullptr));
#endif // QT_NO_TOOLTIP
        pbHome->setText(QString());
        groupBox_2->setTitle(QApplication::translate("WLPositionWidget", "G Code", nullptr));
        labelActivGCode->setText(QApplication::translate("WLPositionWidget", "TextLabel", nullptr));
        labelConnect->setText(QApplication::translate("WLPositionWidget", "TextLabel", nullptr));
#ifndef QT_NO_TOOLTIP
        pbOnMachine->setToolTip(QApplication::translate("WLPositionWidget", "On/Off Machine", nullptr));
#endif // QT_NO_TOOLTIP
        pbOnMachine->setText(QString());
#ifndef QT_NO_TOOLTIP
        rotSK->setToolTip(QApplication::translate("WLPositionWidget", "current rot", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class WLPositionWidget: public Ui_WLPositionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLPOSITIONWIDGET_H
