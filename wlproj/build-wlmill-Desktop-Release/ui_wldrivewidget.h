/********************************************************************************
** Form generated from reading UI file 'wldrivewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLDRIVEWIDGET_H
#define UI_WLDRIVEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <wleditiowidget.h>

QT_BEGIN_NAMESPACE

class Ui_WLDriveWidget
{
public:
    QGridLayout *gridLayout_7;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_13;
    QGroupBox *gbDim;
    QGridLayout *gridLayout;
    QDoubleSpinBox *sbDimA;
    QComboBox *cbTypeDim;
    QDoubleSpinBox *sbDimB;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_8;
    QDoubleSpinBox *sbVfind;
    QLabel *label_14;
    QLabel *labelSDDist;
    QGroupBox *gbLimit;
    QGridLayout *gridLayout_9;
    QLabel *label_9;
    QDoubleSpinBox *sbPLIM;
    QLabel *label_15;
    QDoubleSpinBox *sbMLIM;
    QGroupBox *gbInput;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_12;
    QComboBox *cbActInALM;
    WLEditIOWidget *editInALM;
    WLEditIOWidget *editInMEL;
    QComboBox *cbActInPEL;
    QComboBox *cbActInMEL;
    WLEditIOWidget *editInPEL;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QDoubleSpinBox *sbBackFindPosition;
    QComboBox *comboBoxLogicFind;
    QLabel *label_16;
    QLabel *labelOrgPosition;
    QDoubleSpinBox *sbOrgPosition;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_11;
    QComboBox *cbTypeDrive;
    QGroupBox *groupBoxORG;
    QGridLayout *gridLayout_6;
    QLabel *label_10;
    QDoubleSpinBox *sbOrgSize;
    WLEditIOWidget *editInORG;
    QGroupBox *gbOutput;
    QGridLayout *gridLayout_3;
    WLEditIOWidget *editOutENB;
    WLEditIOWidget *editOutRALM;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QCheckBox *cbInvDir;
    QComboBox *cbTypePulse;
    QCheckBox *cbInvStep;
    QGroupBox *gbDynamic;
    QGridLayout *gridLayout_10;
    QLabel *label_17;
    QDoubleSpinBox *sbDelaySCurve;
    QPushButton *pbVerError;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WLDriveWidget)
    {
        if (WLDriveWidget->objectName().isEmpty())
            WLDriveWidget->setObjectName(QString::fromUtf8("WLDriveWidget"));
        WLDriveWidget->resize(552, 443);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WLDriveWidget->sizePolicy().hasHeightForWidth());
        WLDriveWidget->setSizePolicy(sizePolicy);
        WLDriveWidget->setMinimumSize(QSize(0, 0));
        gridLayout_7 = new QGridLayout(WLDriveWidget);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        tabWidget = new QTabWidget(WLDriveWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_13 = new QGridLayout(tab);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gbDim = new QGroupBox(tab);
        gbDim->setObjectName(QString::fromUtf8("gbDim"));
        gridLayout = new QGridLayout(gbDim);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        sbDimA = new QDoubleSpinBox(gbDim);
        sbDimA->setObjectName(QString::fromUtf8("sbDimA"));
        sbDimA->setDecimals(8);
        sbDimA->setMinimum(0.000001000000000);
        sbDimA->setMaximum(99999999.000000000000000);

        gridLayout->addWidget(sbDimA, 1, 0, 1, 1);

        cbTypeDim = new QComboBox(gbDim);
        cbTypeDim->setObjectName(QString::fromUtf8("cbTypeDim"));

        gridLayout->addWidget(cbTypeDim, 0, 0, 1, 1);

        sbDimB = new QDoubleSpinBox(gbDim);
        sbDimB->setObjectName(QString::fromUtf8("sbDimB"));
        sbDimB->setDecimals(8);
        sbDimB->setMinimum(0.000001000000000);
        sbDimB->setMaximum(99999999.000000000000000);

        gridLayout->addWidget(sbDimB, 2, 0, 1, 1);


        gridLayout_13->addWidget(gbDim, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_8 = new QGridLayout(groupBox_7);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        sbVfind = new QDoubleSpinBox(groupBox_7);
        sbVfind->setObjectName(QString::fromUtf8("sbVfind"));
        sbVfind->setMaximum(12000.000000000000000);

        gridLayout_8->addWidget(sbVfind, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_8->addWidget(label_14, 0, 0, 1, 1);

        labelSDDist = new QLabel(groupBox_7);
        labelSDDist->setObjectName(QString::fromUtf8("labelSDDist"));
        labelSDDist->setText(QString::fromUtf8("slow down distance:"));

        gridLayout_8->addWidget(labelSDDist, 1, 0, 1, 2);


        gridLayout_13->addWidget(groupBox_7, 0, 1, 1, 1);

        gbLimit = new QGroupBox(tab);
        gbLimit->setObjectName(QString::fromUtf8("gbLimit"));
        gbLimit->setCheckable(true);
        gridLayout_9 = new QGridLayout(gbLimit);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_9 = new QLabel(gbLimit);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        gridLayout_9->addWidget(label_9, 0, 0, 1, 1);

        sbPLIM = new QDoubleSpinBox(gbLimit);
        sbPLIM->setObjectName(QString::fromUtf8("sbPLIM"));
        sbPLIM->setCorrectionMode(QAbstractSpinBox::CorrectToPreviousValue);
        sbPLIM->setMinimum(-999999.000000000000000);
        sbPLIM->setMaximum(999999.000000000000000);

        gridLayout_9->addWidget(sbPLIM, 0, 1, 1, 1);

        label_15 = new QLabel(gbLimit);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy1.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy1);

        gridLayout_9->addWidget(label_15, 1, 0, 1, 1);

        sbMLIM = new QDoubleSpinBox(gbLimit);
        sbMLIM->setObjectName(QString::fromUtf8("sbMLIM"));
        sbMLIM->setCorrectionMode(QAbstractSpinBox::CorrectToPreviousValue);
        sbMLIM->setMinimum(-999999.000000000000000);
        sbMLIM->setMaximum(999999.000000000000000);

        gridLayout_9->addWidget(sbMLIM, 1, 1, 1, 1);


        gridLayout_13->addWidget(gbLimit, 0, 2, 1, 1);

        gbInput = new QGroupBox(tab);
        gbInput->setObjectName(QString::fromUtf8("gbInput"));
        gridLayout_4 = new QGridLayout(gbInput);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        cbActInALM = new QComboBox(gbInput);
        cbActInALM->setObjectName(QString::fromUtf8("cbActInALM"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cbActInALM->sizePolicy().hasHeightForWidth());
        cbActInALM->setSizePolicy(sizePolicy2);

        gridLayout_12->addWidget(cbActInALM, 0, 1, 1, 1);

        editInALM = new WLEditIOWidget(gbInput);
        editInALM->setObjectName(QString::fromUtf8("editInALM"));

        gridLayout_12->addWidget(editInALM, 0, 0, 1, 1);

        editInMEL = new WLEditIOWidget(gbInput);
        editInMEL->setObjectName(QString::fromUtf8("editInMEL"));

        gridLayout_12->addWidget(editInMEL, 2, 0, 1, 1);

        cbActInPEL = new QComboBox(gbInput);
        cbActInPEL->setObjectName(QString::fromUtf8("cbActInPEL"));
        sizePolicy2.setHeightForWidth(cbActInPEL->sizePolicy().hasHeightForWidth());
        cbActInPEL->setSizePolicy(sizePolicy2);

        gridLayout_12->addWidget(cbActInPEL, 1, 1, 1, 1);

        cbActInMEL = new QComboBox(gbInput);
        cbActInMEL->setObjectName(QString::fromUtf8("cbActInMEL"));
        sizePolicy2.setHeightForWidth(cbActInMEL->sizePolicy().hasHeightForWidth());
        cbActInMEL->setSizePolicy(sizePolicy2);

        gridLayout_12->addWidget(cbActInMEL, 2, 1, 1, 1);

        editInPEL = new WLEditIOWidget(gbInput);
        editInPEL->setObjectName(QString::fromUtf8("editInPEL"));

        gridLayout_12->addWidget(editInPEL, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_12, 0, 0, 1, 1);


        gridLayout_13->addWidget(gbInput, 1, 0, 2, 1);

        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        sbBackFindPosition = new QDoubleSpinBox(groupBox_5);
        sbBackFindPosition->setObjectName(QString::fromUtf8("sbBackFindPosition"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sbBackFindPosition->sizePolicy().hasHeightForWidth());
        sbBackFindPosition->setSizePolicy(sizePolicy3);
        sbBackFindPosition->setMinimum(-999999.000000000000000);
        sbBackFindPosition->setMaximum(999999.000000000000000);
        sbBackFindPosition->setSingleStep(1.000000000000000);
        sbBackFindPosition->setValue(0.000000000000000);

        gridLayout_5->addWidget(sbBackFindPosition, 4, 1, 1, 1);

        comboBoxLogicFind = new QComboBox(groupBox_5);
        comboBoxLogicFind->setObjectName(QString::fromUtf8("comboBoxLogicFind"));

        gridLayout_5->addWidget(comboBoxLogicFind, 0, 0, 1, 2);

        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_5->addWidget(label_16, 4, 0, 1, 1);

        labelOrgPosition = new QLabel(groupBox_5);
        labelOrgPosition->setObjectName(QString::fromUtf8("labelOrgPosition"));
        labelOrgPosition->setText(QString::fromUtf8("org position"));

        gridLayout_5->addWidget(labelOrgPosition, 5, 0, 1, 1);

        sbOrgPosition = new QDoubleSpinBox(groupBox_5);
        sbOrgPosition->setObjectName(QString::fromUtf8("sbOrgPosition"));
        sizePolicy3.setHeightForWidth(sbOrgPosition->sizePolicy().hasHeightForWidth());
        sbOrgPosition->setSizePolicy(sizePolicy3);
        sbOrgPosition->setMinimum(-999999.000000000000000);
        sbOrgPosition->setMaximum(999999.000000000000000);
        sbOrgPosition->setSingleStep(1.000000000000000);
        sbOrgPosition->setValue(0.000000000000000);

        gridLayout_5->addWidget(sbOrgPosition, 5, 1, 1, 1);


        gridLayout_13->addWidget(groupBox_5, 1, 1, 2, 1);

        groupBox_10 = new QGroupBox(tab);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        gridLayout_11 = new QGridLayout(groupBox_10);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        cbTypeDrive = new QComboBox(groupBox_10);
        cbTypeDrive->addItem(QString());
        cbTypeDrive->addItem(QString());
        cbTypeDrive->setObjectName(QString::fromUtf8("cbTypeDrive"));
        cbTypeDrive->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout_11->addWidget(cbTypeDrive, 0, 0, 1, 1);


        gridLayout_13->addWidget(groupBox_10, 1, 2, 1, 1);

        groupBoxORG = new QGroupBox(tab);
        groupBoxORG->setObjectName(QString::fromUtf8("groupBoxORG"));
        gridLayout_6 = new QGridLayout(groupBoxORG);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_10 = new QLabel(groupBoxORG);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_6->addWidget(label_10, 1, 0, 1, 1);

        sbOrgSize = new QDoubleSpinBox(groupBoxORG);
        sbOrgSize->setObjectName(QString::fromUtf8("sbOrgSize"));
        sizePolicy3.setHeightForWidth(sbOrgSize->sizePolicy().hasHeightForWidth());
        sbOrgSize->setSizePolicy(sizePolicy3);
        sbOrgSize->setMinimum(0.100000000000000);
        sbOrgSize->setMaximum(99999.000000000000000);

        gridLayout_6->addWidget(sbOrgSize, 1, 1, 1, 1);

        editInORG = new WLEditIOWidget(groupBoxORG);
        editInORG->setObjectName(QString::fromUtf8("editInORG"));

        gridLayout_6->addWidget(editInORG, 0, 0, 1, 2);


        gridLayout_13->addWidget(groupBoxORG, 2, 2, 1, 1);

        gbOutput = new QGroupBox(tab);
        gbOutput->setObjectName(QString::fromUtf8("gbOutput"));
        gridLayout_3 = new QGridLayout(gbOutput);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        editOutENB = new WLEditIOWidget(gbOutput);
        editOutENB->setObjectName(QString::fromUtf8("editOutENB"));

        gridLayout_3->addWidget(editOutENB, 1, 0, 1, 1);

        editOutRALM = new WLEditIOWidget(gbOutput);
        editOutRALM->setObjectName(QString::fromUtf8("editOutRALM"));

        gridLayout_3->addWidget(editOutRALM, 0, 0, 1, 1);


        gridLayout_13->addWidget(gbOutput, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cbInvDir = new QCheckBox(groupBox_2);
        cbInvDir->setObjectName(QString::fromUtf8("cbInvDir"));

        gridLayout_2->addWidget(cbInvDir, 1, 1, 1, 1);

        cbTypePulse = new QComboBox(groupBox_2);
        cbTypePulse->setObjectName(QString::fromUtf8("cbTypePulse"));

        gridLayout_2->addWidget(cbTypePulse, 0, 0, 1, 2);

        cbInvStep = new QCheckBox(groupBox_2);
        cbInvStep->setObjectName(QString::fromUtf8("cbInvStep"));

        gridLayout_2->addWidget(cbInvStep, 1, 0, 1, 1);


        gridLayout_13->addWidget(groupBox_2, 3, 1, 1, 1);

        gbDynamic = new QGroupBox(tab);
        gbDynamic->setObjectName(QString::fromUtf8("gbDynamic"));
        gridLayout_10 = new QGridLayout(gbDynamic);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_17 = new QLabel(gbDynamic);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_10->addWidget(label_17, 0, 0, 1, 1);

        sbDelaySCurve = new QDoubleSpinBox(gbDynamic);
        sbDelaySCurve->setObjectName(QString::fromUtf8("sbDelaySCurve"));
        sizePolicy3.setHeightForWidth(sbDelaySCurve->sizePolicy().hasHeightForWidth());
        sbDelaySCurve->setSizePolicy(sizePolicy3);
        sbDelaySCurve->setDecimals(3);
        sbDelaySCurve->setMaximum(1.000000000000000);

        gridLayout_10->addWidget(sbDelaySCurve, 0, 1, 1, 1);


        gridLayout_13->addWidget(gbDynamic, 3, 2, 1, 1);

        pbVerError = new QPushButton(tab);
        pbVerError->setObjectName(QString::fromUtf8("pbVerError"));

        gridLayout_13->addWidget(pbVerError, 4, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_7->addWidget(tabWidget, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(WLDriveWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::SaveAll);
        buttonBox->setCenterButtons(false);

        gridLayout_7->addWidget(buttonBox, 1, 1, 1, 1);


        retranslateUi(WLDriveWidget);
        QObject::connect(buttonBox, SIGNAL(accepted()), WLDriveWidget, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), WLDriveWidget, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WLDriveWidget);
    } // setupUi

    void retranslateUi(QDialog *WLDriveWidget)
    {
        WLDriveWidget->setWindowTitle(QApplication::translate("WLDriveWidget", "Edit Axis ", nullptr));
        gbDim->setTitle(QApplication::translate("WLDriveWidget", "Step size", nullptr));
        groupBox_7->setTitle(QApplication::translate("WLDriveWidget", "Feed (unit/s)", nullptr));
        label_14->setText(QApplication::translate("WLDriveWidget", "Find ", nullptr));
        gbLimit->setTitle(QApplication::translate("WLDriveWidget", "Limits", nullptr));
        label_9->setText(QApplication::translate("WLDriveWidget", "Plus ", nullptr));
        label_15->setText(QApplication::translate("WLDriveWidget", "Minus", nullptr));
#ifndef QT_NO_TOOLTIP
        gbInput->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        gbInput->setTitle(QApplication::translate("WLDriveWidget", "Input", nullptr));
        groupBox_5->setTitle(QApplication::translate("WLDriveWidget", "Find position", nullptr));
        label_16->setText(QApplication::translate("WLDriveWidget", "back position", nullptr));
        groupBox_10->setTitle(QApplication::translate("WLDriveWidget", "Type", nullptr));
        cbTypeDrive->setItemText(0, QApplication::translate("WLDriveWidget", "Linear", nullptr));
        cbTypeDrive->setItemText(1, QApplication::translate("WLDriveWidget", "Rotary", nullptr));

        groupBoxORG->setTitle(QApplication::translate("WLDriveWidget", "inORG", nullptr));
        label_10->setText(QApplication::translate("WLDriveWidget", "inORG zone size", nullptr));
        gbOutput->setTitle(QApplication::translate("WLDriveWidget", "Output", nullptr));
        groupBox_2->setTitle(QApplication::translate("WLDriveWidget", "Output pulse", nullptr));
        cbInvDir->setText(QApplication::translate("WLDriveWidget", "inv.dir", nullptr));
        cbInvStep->setText(QApplication::translate("WLDriveWidget", "inv.pulse", nullptr));
        gbDynamic->setTitle(QApplication::translate("WLDriveWidget", "Dynamic", nullptr));
        label_17->setText(QApplication::translate("WLDriveWidget", "curve S", nullptr));
        sbDelaySCurve->setSuffix(QApplication::translate("WLDriveWidget", "s", nullptr));
        pbVerError->setText(QApplication::translate("WLDriveWidget", "verify error", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("WLDriveWidget", "main", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLDriveWidget: public Ui_WLDriveWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLDRIVEWIDGET_H
