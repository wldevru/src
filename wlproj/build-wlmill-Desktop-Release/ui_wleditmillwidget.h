/********************************************************************************
** Form generated from reading UI file 'wleditmillwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLEDITMILLWIDGET_H
#define UI_WLEDITMILLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "wleditiowidget.h"

QT_BEGIN_NAMESPACE

class Ui_WLEditMillWidget
{
public:
    QGridLayout *gridLayout_8;
    QDialogButtonBox *buttonBox;
    QGroupBox *gbCorrectSOut;
    QGridLayout *gridLayout_10;
    QTableWidget *twCorrectS;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_12;
    QCheckBox *cbHPause;
    QDoubleSpinBox *sbHPause;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QDoubleSpinBox *sbSmoothAng;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    WLEditIOWidget *editInEMG;
    WLEditIOWidget *editInProbe;
    WLEditIOWidget *editInSD;
    QGroupBox *gbPWMOut;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QDoubleSpinBox *sbSmax;
    QDoubleSpinBox *sbSminOut;
    QLabel *label;
    QDoubleSpinBox *sbSmin;
    QLabel *label_3;
    QDoubleSpinBox *sbSmaxOut;
    QLabel *label_2;
    QCheckBox *cbInvPWM;
    QLabel *label_5;
    QSpinBox *sbFreqPWM;
    QSpinBox *sbIndexOutPWM;
    QLabel *label_7;
    QPushButton *pbVerError;
    QGroupBox *gbWhell;
    QGridLayout *gridLayout_7;
    QLabel *label_19;
    QSpinBox *sbWEncoder;
    QSpinBox *sbWhellSize;
    QLabel *label_16;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QDoubleSpinBox *sbFbls;
    QLabel *label_10;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_9;
    QLabel *label_18;
    QDoubleSpinBox *sbTabletHProbe;
    QDoubleSpinBox *sbBackZHProbe;
    QLabel *label_17;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_13;
    QLabel *label_21;
    QDoubleSpinBox *sbXYFreeTouch;
    QLabel *label_20;
    QDoubleSpinBox *sbZFreeTouch;
    QLabel *label_22;
    QDoubleSpinBox *sbDiametrTouch;

    void setupUi(QWidget *WLEditMillWidget)
    {
        if (WLEditMillWidget->objectName().isEmpty())
            WLEditMillWidget->setObjectName(QString::fromUtf8("WLEditMillWidget"));
        WLEditMillWidget->resize(938, 371);
        gridLayout_8 = new QGridLayout(WLEditMillWidget);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        buttonBox = new QDialogButtonBox(WLEditMillWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_8->addWidget(buttonBox, 3, 10, 1, 1);

        gbCorrectSOut = new QGroupBox(WLEditMillWidget);
        gbCorrectSOut->setObjectName(QString::fromUtf8("gbCorrectSOut"));
        gbCorrectSOut->setCheckable(true);
        gridLayout_10 = new QGridLayout(gbCorrectSOut);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        twCorrectS = new QTableWidget(gbCorrectSOut);
        twCorrectS->setObjectName(QString::fromUtf8("twCorrectS"));

        gridLayout_10->addWidget(twCorrectS, 0, 0, 1, 1);


        gridLayout_8->addWidget(gbCorrectSOut, 0, 6, 1, 5);

        groupBox_6 = new QGroupBox(WLEditMillWidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        gridLayout_12 = new QGridLayout(groupBox_6);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        cbHPause = new QCheckBox(groupBox_6);
        cbHPause->setObjectName(QString::fromUtf8("cbHPause"));

        gridLayout_12->addWidget(cbHPause, 0, 0, 1, 1);

        sbHPause = new QDoubleSpinBox(groupBox_6);
        sbHPause->setObjectName(QString::fromUtf8("sbHPause"));
        sbHPause->setDecimals(2);
        sbHPause->setMaximum(300.000000000000000);

        gridLayout_12->addWidget(sbHPause, 0, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_6, 1, 2, 1, 1);

        groupBox_3 = new QGroupBox(WLEditMillWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        sbSmoothAng = new QDoubleSpinBox(groupBox_3);
        sbSmoothAng->setObjectName(QString::fromUtf8("sbSmoothAng"));
        sbSmoothAng->setMaximum(30.000000000000000);

        gridLayout_2->addWidget(sbSmoothAng, 0, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_3, 2, 2, 1, 1);

        groupBox_4 = new QGroupBox(WLEditMillWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        editInEMG = new WLEditIOWidget(groupBox_4);
        editInEMG->setObjectName(QString::fromUtf8("editInEMG"));

        gridLayout_4->addWidget(editInEMG, 0, 0, 1, 1);

        editInProbe = new WLEditIOWidget(groupBox_4);
        editInProbe->setObjectName(QString::fromUtf8("editInProbe"));

        gridLayout_4->addWidget(editInProbe, 2, 0, 1, 1);

        editInSD = new WLEditIOWidget(groupBox_4);
        editInSD->setObjectName(QString::fromUtf8("editInSD"));

        gridLayout_4->addWidget(editInSD, 1, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_4, 1, 1, 2, 1);

        gbPWMOut = new QGroupBox(WLEditMillWidget);
        gbPWMOut->setObjectName(QString::fromUtf8("gbPWMOut"));
        gbPWMOut->setCheckable(true);
        gridLayout_3 = new QGridLayout(gbPWMOut);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_2 = new QGroupBox(gbPWMOut);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        sbSmax = new QDoubleSpinBox(groupBox_2);
        sbSmax->setObjectName(QString::fromUtf8("sbSmax"));
        sbSmax->setMaximum(100000.000000000000000);

        gridLayout->addWidget(sbSmax, 0, 1, 1, 1);

        sbSminOut = new QDoubleSpinBox(groupBox_2);
        sbSminOut->setObjectName(QString::fromUtf8("sbSminOut"));
        sbSminOut->setMaximum(100.000000000000000);

        gridLayout->addWidget(sbSminOut, 1, 3, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 2, 1, 1);

        sbSmin = new QDoubleSpinBox(groupBox_2);
        sbSmin->setObjectName(QString::fromUtf8("sbSmin"));
        sbSmin->setMaximum(100000.000000000000000);

        gridLayout->addWidget(sbSmin, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        sbSmaxOut = new QDoubleSpinBox(groupBox_2);
        sbSmaxOut->setObjectName(QString::fromUtf8("sbSmaxOut"));
        sbSmaxOut->setMaximum(100.000000000000000);

        gridLayout->addWidget(sbSmaxOut, 0, 3, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 3, 1, 1, 2);

        cbInvPWM = new QCheckBox(gbPWMOut);
        cbInvPWM->setObjectName(QString::fromUtf8("cbInvPWM"));

        gridLayout_3->addWidget(cbInvPWM, 2, 2, 1, 1);

        label_5 = new QLabel(gbPWMOut);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_5, 1, 1, 1, 1);

        sbFreqPWM = new QSpinBox(gbPWMOut);
        sbFreqPWM->setObjectName(QString::fromUtf8("sbFreqPWM"));
        sbFreqPWM->setMinimum(50);
        sbFreqPWM->setMaximum(15000);

        gridLayout_3->addWidget(sbFreqPWM, 1, 2, 1, 1);

        sbIndexOutPWM = new QSpinBox(gbPWMOut);
        sbIndexOutPWM->setObjectName(QString::fromUtf8("sbIndexOutPWM"));
        sbIndexOutPWM->setMinimum(50);
        sbIndexOutPWM->setMaximum(15000);

        gridLayout_3->addWidget(sbIndexOutPWM, 0, 2, 1, 1);

        label_7 = new QLabel(gbPWMOut);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_7, 0, 1, 1, 1);


        gridLayout_8->addWidget(gbPWMOut, 0, 1, 1, 5);

        pbVerError = new QPushButton(WLEditMillWidget);
        pbVerError->setObjectName(QString::fromUtf8("pbVerError"));

        gridLayout_8->addWidget(pbVerError, 3, 1, 1, 1);

        gbWhell = new QGroupBox(WLEditMillWidget);
        gbWhell->setObjectName(QString::fromUtf8("gbWhell"));
        gbWhell->setCheckable(false);
        gridLayout_7 = new QGridLayout(gbWhell);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_19 = new QLabel(gbWhell);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_7->addWidget(label_19, 2, 0, 1, 1);

        sbWEncoder = new QSpinBox(gbWhell);
        sbWEncoder->setObjectName(QString::fromUtf8("sbWEncoder"));
        sbWEncoder->setMinimum(10);
        sbWEncoder->setMaximum(10000);

        gridLayout_7->addWidget(sbWEncoder, 2, 1, 1, 1);

        sbWhellSize = new QSpinBox(gbWhell);
        sbWhellSize->setObjectName(QString::fromUtf8("sbWhellSize"));
        sbWhellSize->setMinimum(10);
        sbWhellSize->setMaximum(10000);

        gridLayout_7->addWidget(sbWhellSize, 0, 1, 1, 1);

        label_16 = new QLabel(gbWhell);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_7->addWidget(label_16, 0, 0, 1, 1);


        gridLayout_8->addWidget(gbWhell, 1, 3, 2, 1);

        groupBox = new QGroupBox(WLEditMillWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        sbFbls = new QDoubleSpinBox(groupBox);
        sbFbls->setObjectName(QString::fromUtf8("sbFbls"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(sbFbls->sizePolicy().hasHeightForWidth());
        sbFbls->setSizePolicy(sizePolicy2);
        sbFbls->setMinimumSize(QSize(70, 0));
        sbFbls->setDecimals(1);
        sbFbls->setMinimum(0.000000000000000);
        sbFbls->setMaximum(60000.000000000000000);

        gridLayout_6->addWidget(sbFbls, 0, 2, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy3);

        gridLayout_6->addWidget(label_10, 0, 0, 1, 1);


        gridLayout_8->addWidget(groupBox, 1, 8, 2, 1);

        groupBox_7 = new QGroupBox(WLEditMillWidget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_9 = new QGridLayout(groupBox_7);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_18 = new QLabel(groupBox_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_9->addWidget(label_18, 1, 0, 1, 1);

        sbTabletHProbe = new QDoubleSpinBox(groupBox_7);
        sbTabletHProbe->setObjectName(QString::fromUtf8("sbTabletHProbe"));
        sbTabletHProbe->setDecimals(2);
        sbTabletHProbe->setMinimum(-9999999.000000000000000);
        sbTabletHProbe->setMaximum(9999999.000000000000000);

        gridLayout_9->addWidget(sbTabletHProbe, 0, 1, 1, 1);

        sbBackZHProbe = new QDoubleSpinBox(groupBox_7);
        sbBackZHProbe->setObjectName(QString::fromUtf8("sbBackZHProbe"));
        sbBackZHProbe->setDecimals(2);
        sbBackZHProbe->setMinimum(-9999999.000000000000000);
        sbBackZHProbe->setMaximum(9999999.000000000000000);

        gridLayout_9->addWidget(sbBackZHProbe, 1, 1, 1, 1);

        label_17 = new QLabel(groupBox_7);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_9->addWidget(label_17, 0, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_7, 1, 9, 2, 1);

        groupBox_8 = new QGroupBox(WLEditMillWidget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout_13 = new QGridLayout(groupBox_8);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_21 = new QLabel(groupBox_8);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_13->addWidget(label_21, 1, 0, 1, 1);

        sbXYFreeTouch = new QDoubleSpinBox(groupBox_8);
        sbXYFreeTouch->setObjectName(QString::fromUtf8("sbXYFreeTouch"));
        sbXYFreeTouch->setDecimals(2);
        sbXYFreeTouch->setMinimum(0.000000000000000);
        sbXYFreeTouch->setMaximum(15.000000000000000);

        gridLayout_13->addWidget(sbXYFreeTouch, 0, 1, 1, 1);

        label_20 = new QLabel(groupBox_8);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_13->addWidget(label_20, 0, 0, 1, 1);

        sbZFreeTouch = new QDoubleSpinBox(groupBox_8);
        sbZFreeTouch->setObjectName(QString::fromUtf8("sbZFreeTouch"));
        sbZFreeTouch->setDecimals(2);
        sbZFreeTouch->setMinimum(0.000000000000000);
        sbZFreeTouch->setMaximum(15.000000000000000);

        gridLayout_13->addWidget(sbZFreeTouch, 1, 1, 1, 1);

        label_22 = new QLabel(groupBox_8);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_13->addWidget(label_22, 2, 0, 1, 1);

        sbDiametrTouch = new QDoubleSpinBox(groupBox_8);
        sbDiametrTouch->setObjectName(QString::fromUtf8("sbDiametrTouch"));
        sbDiametrTouch->setDecimals(2);
        sbDiametrTouch->setMinimum(1.000000000000000);
        sbDiametrTouch->setMaximum(50.000000000000000);

        gridLayout_13->addWidget(sbDiametrTouch, 2, 1, 1, 1);


        gridLayout_8->addWidget(groupBox_8, 1, 10, 2, 1);


        retranslateUi(WLEditMillWidget);
        QObject::connect(cbHPause, SIGNAL(toggled(bool)), sbHPause, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(WLEditMillWidget);
    } // setupUi

    void retranslateUi(QWidget *WLEditMillWidget)
    {
        WLEditMillWidget->setWindowTitle(QApplication::translate("WLEditMillWidget", "Edit WLMill", nullptr));
        gbCorrectSOut->setTitle(QApplication::translate("WLEditMillWidget", "Correct S Out", nullptr));
        groupBox_6->setTitle(QApplication::translate("WLEditMillWidget", "Pause", nullptr));
        cbHPause->setText(QApplication::translate("WLEditMillWidget", "G53 Z", nullptr));
        groupBox_3->setTitle(QApplication::translate("WLEditMillWidget", "Smooth", nullptr));
        label_6->setText(QApplication::translate("WLEditMillWidget", "Angle", nullptr));
        groupBox_4->setTitle(QApplication::translate("WLEditMillWidget", "Input", nullptr));
        gbPWMOut->setTitle(QApplication::translate("WLEditMillWidget", "PWM S output", nullptr));
        groupBox_2->setTitle(QApplication::translate("WLEditMillWidget", "Calc", nullptr));
        label_4->setText(QApplication::translate("WLEditMillWidget", "S max", nullptr));
        label->setText(QApplication::translate("WLEditMillWidget", "PWM min", nullptr));
        label_3->setText(QApplication::translate("WLEditMillWidget", "S min", nullptr));
        label_2->setText(QApplication::translate("WLEditMillWidget", "PWM max", nullptr));
        cbInvPWM->setText(QApplication::translate("WLEditMillWidget", "Invers outPWM", nullptr));
        label_5->setText(QApplication::translate("WLEditMillWidget", "Frequency", nullptr));
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QApplication::translate("WLEditMillWidget", "PWM OUT controler", nullptr));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("WLEditMillWidget", "Index", nullptr));
        pbVerError->setText(QApplication::translate("WLEditMillWidget", "verify error", nullptr));
        gbWhell->setTitle(QApplication::translate("WLEditMillWidget", "Whell", nullptr));
        label_19->setText(QApplication::translate("WLEditMillWidget", "Encoder", nullptr));
        label_16->setText(QApplication::translate("WLEditMillWidget", "Size", nullptr));
        groupBox->setTitle(QApplication::translate("WLEditMillWidget", "Backlash", nullptr));
        sbFbls->setSuffix(QApplication::translate("WLEditMillWidget", "mm/min", nullptr));
        label_10->setText(QApplication::translate("WLEditMillWidget", "Feed", nullptr));
        groupBox_7->setTitle(QApplication::translate("WLEditMillWidget", "Probe H", nullptr));
        label_18->setText(QApplication::translate("WLEditMillWidget", "back Z:", nullptr));
        label_17->setText(QApplication::translate("WLEditMillWidget", "height:", nullptr));
        groupBox_8->setTitle(QApplication::translate("WLEditMillWidget", "Touch", nullptr));
        label_21->setText(QApplication::translate("WLEditMillWidget", "Z,free (mm)", nullptr));
        label_20->setText(QApplication::translate("WLEditMillWidget", "X,Y free (mm)", nullptr));
        label_22->setText(QApplication::translate("WLEditMillWidget", "Diametr (mm)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLEditMillWidget: public Ui_WLEditMillWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLEDITMILLWIDGET_H
