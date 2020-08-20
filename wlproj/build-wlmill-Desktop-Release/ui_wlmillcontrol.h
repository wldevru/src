/********************************************************************************
** Form generated from reading UI file 'wlmillcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLMILLCONTROL_H
#define UI_WLMILLCONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "wllabel.h"

QT_BEGIN_NAMESPACE

class Ui_WLMillControl
{
public:
    QGridLayout *gridLayout_12;
    QStackedWidget *stackedWidget;
    QWidget *Tab;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_19;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout;
    QCheckBox *cbOneTool;
    QSpinBox *sbOneTool;
    QPushButton *pushButtonOnProgram;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_29;
    QCheckBox *cbAutoStart;
    QCheckBox *cbBLNextMov;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_15;
    QGridLayout *gridLayout_35;
    QDoubleSpinBox *sbSmoothDist;
    QCheckBox *cbSmooth;
    QCheckBox *cbSimpli;
    QDoubleSpinBox *sbSimpliDist;
    QWidget *tab_2;
    QGridLayout *gridLayout_8;
    QTabWidget *tabWidgetManual;
    QWidget *tab_4;
    QGridLayout *gridLayout_17;
    QGroupBox *groupBoxStepMov;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_40;
    QToolButton *pbStepInf;
    QToolButton *pbStep1;
    QToolButton *pbStep0;
    QToolButton *pbStep2;
    QGroupBox *groupBoxFmanual;
    QGridLayout *gridLayout_34;
    QGridLayout *gridLayout_16;
    QToolButton *pbPlusFman;
    QToolButton *pbMinusFman;
    QDoubleSpinBox *sbFman;
    QToolButton *pbFast;
    QGroupBox *gbDirManualKey;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_2;
    QToolButton *pbMinusX;
    QToolButton *pbPlusX;
    QToolButton *pbPlusZ;
    QToolButton *pbMinusY;
    QToolButton *pbMinusZ;
    QToolButton *pbPlusA;
    QToolButton *pbPlusY;
    QToolButton *pbMinusA;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_5;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer_6;
    QGroupBox *gbVmodeWhell;
    QGridLayout *gridLayout_26;
    QCheckBox *rbWhellVMode;
    QGroupBox *gbAxisWhell;
    QGridLayout *gridLayout_27;
    QComboBox *comboBoxWhellAxis;
    QGroupBox *gbXWhell;
    QGridLayout *gridLayout_25;
    QPushButton *pbWhellX100;
    QPushButton *pbWhellX1;
    QPushButton *pbWhellX10;
    QWidget *tab_3;
    QGridLayout *gridLayout_23;
    QPushButton *pbEditScript;
    QPushButton *pbResetScript;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBoxScript;
    QGridLayout *gridLayout_22;
    QLineEdit *leRunScript;
    QWidget *tab_6;
    QGridLayout *gridLayout_28;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_13;
    QDoubleSpinBox *sbFtouch;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_7;
    QRadioButton *rbProbeSD;
    QCheckBox *cbDSide;
    QRadioButton *rbProbeSD_2;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_24;
    QLabel *labelInProbe;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_9;
    QToolButton *pbPlusProbeX;
    QToolButton *pbMinusProbeY;
    QToolButton *pbMinusProbeX;
    QToolButton *pbMinusProbeZ;
    QToolButton *pbPlusProbeY;
    QToolButton *pbPlusProbeA;
    QToolButton *pbMinusProbeA;
    QToolButton *pbPlusProbeZ;
    QToolButton *pbMinusProbeH;
    QToolButton *pbStopTouch;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_8;
    QGridLayout *gridLayout_33;
    QPushButton *pbUpdateTool;
    QTableWidget *tableTools;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout_32;
    QLabel *labelBaseOffsetTool;
    QPushButton *pbEditOffsetTool;
    QPushButton *pbAcceptTool;
    QWidget *tab_7;
    QGridLayout *gridLayout_30;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QPushButton *pbSetSCor;
    QPushButton *pbClearSCor;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_31;
    QPushButton *pbRFindAxis;
    QPushButton *pbStartTeachAxis;
    QComboBox *cbServiceAxis;
    QPushButton *pbStartFindAxis;
    QPushButton *pbGetMSLimit;
    QPushButton *pbGetPSLimit;
    QSpacerItem *verticalSpacer_9;
    QWidget *page_2;
    QGridLayout *gridLayout_20;
    QPushButton *pushButtonPause;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_21;
    WLLabel *labelTimeLeft;
    WLLabel *labelTimeEnd;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_18;
    WLLabel *labelBufPC;
    WLLabel *labelBufDev;
    WLLabel *labelProgram;
    QPushButton *pushButtonGo;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *gbFcor;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_39;
    QDoubleSpinBox *sbFper;
    QToolButton *pbPlusF;
    QToolButton *pbMinusF;
    QToolButton *pbF100;
    WLLabel *labelF;
    QGroupBox *gbScor;
    QGridLayout *gridLayout_36;
    QHBoxLayout *horizontalLayout;
    WLLabel *labelS;
    QToolButton *pbS100;
    QDoubleSpinBox *sbSper;
    QToolButton *pbMinusS;
    QToolButton *pbPlusS;
    QButtonGroup *buttonGroup;
    QButtonGroup *buttonGroupWhellX;

    void setupUi(QWidget *WLMillControl)
    {
        if (WLMillControl->objectName().isEmpty())
            WLMillControl->setObjectName(QString::fromUtf8("WLMillControl"));
        WLMillControl->resize(371, 448);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WLMillControl->sizePolicy().hasHeightForWidth());
        WLMillControl->setSizePolicy(sizePolicy);
        WLMillControl->setMaximumSize(QSize(9999, 9999));
        WLMillControl->setFocusPolicy(Qt::StrongFocus);
        gridLayout_12 = new QGridLayout(WLMillControl);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(5, -1, 1, -1);
        stackedWidget = new QStackedWidget(WLMillControl);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QFont font;
        font.setKerning(true);
        stackedWidget->setFont(font);
        stackedWidget->setLayoutDirection(Qt::LeftToRight);
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setInputMethodHints(Qt::ImhNone);
        stackedWidget->setFrameShape(QFrame::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Raised);
        stackedWidget->setLineWidth(0);
        stackedWidget->setMidLineWidth(0);
        Tab = new QWidget();
        Tab->setObjectName(QString::fromUtf8("Tab"));
        gridLayout_3 = new QGridLayout(Tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(Tab);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(8);
        tabWidget->setFont(font1);
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setInputMethodHints(Qt::ImhNone);
        tabWidget->setTabPosition(QTabWidget::East);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_19 = new QGridLayout(tab);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        gridLayout = new QGridLayout(groupBox_6);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        cbOneTool = new QCheckBox(groupBox_6);
        cbOneTool->setObjectName(QString::fromUtf8("cbOneTool"));

        gridLayout->addWidget(cbOneTool, 2, 0, 1, 1);

        sbOneTool = new QSpinBox(groupBox_6);
        sbOneTool->setObjectName(QString::fromUtf8("sbOneTool"));
        sbOneTool->setEnabled(false);
        sbOneTool->setMinimum(1);

        gridLayout->addWidget(sbOneTool, 2, 1, 1, 1);

        pushButtonOnProgram = new QPushButton(groupBox_6);
        pushButtonOnProgram->setObjectName(QString::fromUtf8("pushButtonOnProgram"));

        gridLayout->addWidget(pushButtonOnProgram, 3, 0, 1, 2);


        gridLayout_19->addWidget(groupBox_6, 1, 0, 1, 1);

        groupBox_13 = new QGroupBox(tab);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        gridLayout_29 = new QGridLayout(groupBox_13);
        gridLayout_29->setSpacing(6);
        gridLayout_29->setContentsMargins(11, 11, 11, 11);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        cbAutoStart = new QCheckBox(groupBox_13);
        cbAutoStart->setObjectName(QString::fromUtf8("cbAutoStart"));

        gridLayout_29->addWidget(cbAutoStart, 1, 0, 1, 1);

        cbBLNextMov = new QCheckBox(groupBox_13);
        cbBLNextMov->setObjectName(QString::fromUtf8("cbBLNextMov"));
        cbBLNextMov->setEnabled(false);

        gridLayout_29->addWidget(cbBLNextMov, 0, 0, 1, 1);


        gridLayout_19->addWidget(groupBox_13, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_19->addItem(verticalSpacer, 4, 0, 1, 1);

        groupBox_15 = new QGroupBox(tab);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        gridLayout_35 = new QGridLayout(groupBox_15);
        gridLayout_35->setSpacing(6);
        gridLayout_35->setContentsMargins(11, 11, 11, 11);
        gridLayout_35->setObjectName(QString::fromUtf8("gridLayout_35"));
        sbSmoothDist = new QDoubleSpinBox(groupBox_15);
        sbSmoothDist->setObjectName(QString::fromUtf8("sbSmoothDist"));
        sbSmoothDist->setEnabled(false);
        sbSmoothDist->setDecimals(3);
        sbSmoothDist->setMinimum(0.000000000000000);
        sbSmoothDist->setMaximum(2.000000000000000);
        sbSmoothDist->setSingleStep(0.050000000000000);

        gridLayout_35->addWidget(sbSmoothDist, 0, 1, 1, 1);

        cbSmooth = new QCheckBox(groupBox_15);
        cbSmooth->setObjectName(QString::fromUtf8("cbSmooth"));

        gridLayout_35->addWidget(cbSmooth, 0, 0, 1, 1);

        cbSimpli = new QCheckBox(groupBox_15);
        cbSimpli->setObjectName(QString::fromUtf8("cbSimpli"));

        gridLayout_35->addWidget(cbSimpli, 1, 0, 1, 1);

        sbSimpliDist = new QDoubleSpinBox(groupBox_15);
        sbSimpliDist->setObjectName(QString::fromUtf8("sbSimpliDist"));
        sbSimpliDist->setEnabled(false);
        sbSimpliDist->setDecimals(3);
        sbSimpliDist->setMinimum(0.000000000000000);
        sbSimpliDist->setMaximum(2.000000000000000);
        sbSimpliDist->setSingleStep(0.050000000000000);

        gridLayout_35->addWidget(sbSimpliDist, 1, 1, 1, 1);


        gridLayout_19->addWidget(groupBox_15, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_8 = new QGridLayout(tab_2);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        tabWidgetManual = new QTabWidget(tab_2);
        tabWidgetManual->setObjectName(QString::fromUtf8("tabWidgetManual"));
        tabWidgetManual->setEnabled(true);
        tabWidgetManual->setFocusPolicy(Qt::NoFocus);
        tabWidgetManual->setTabShape(QTabWidget::Rounded);
        tabWidgetManual->setElideMode(Qt::ElideLeft);
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout_17 = new QGridLayout(tab_4);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        groupBoxStepMov = new QGroupBox(tab_4);
        groupBoxStepMov->setObjectName(QString::fromUtf8("groupBoxStepMov"));
        groupBoxStepMov->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBoxStepMov->sizePolicy().hasHeightForWidth());
        groupBoxStepMov->setSizePolicy(sizePolicy2);
        groupBoxStepMov->setFocusPolicy(Qt::NoFocus);
        groupBoxStepMov->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBoxStepMov->setFlat(false);
        groupBoxStepMov->setCheckable(false);
        groupBoxStepMov->setChecked(false);
        gridLayout_15 = new QGridLayout(groupBoxStepMov);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_40 = new QGridLayout();
        gridLayout_40->setSpacing(6);
        gridLayout_40->setObjectName(QString::fromUtf8("gridLayout_40"));
        pbStepInf = new QToolButton(groupBoxStepMov);
        pbStepInf->setObjectName(QString::fromUtf8("pbStepInf"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pbStepInf->sizePolicy().hasHeightForWidth());
        pbStepInf->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setPointSize(16);
        pbStepInf->setFont(font2);
        pbStepInf->setFocusPolicy(Qt::NoFocus);
        pbStepInf->setText(QString::fromUtf8("<-->"));
        pbStepInf->setCheckable(true);
        pbStepInf->setChecked(true);
        pbStepInf->setAutoExclusive(true);

        gridLayout_40->addWidget(pbStepInf, 0, 0, 1, 1);

        pbStep1 = new QToolButton(groupBoxStepMov);
        pbStep1->setObjectName(QString::fromUtf8("pbStep1"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pbStep1->sizePolicy().hasHeightForWidth());
        pbStep1->setSizePolicy(sizePolicy4);
        pbStep1->setFont(font2);
        pbStep1->setFocusPolicy(Qt::NoFocus);
        pbStep1->setText(QString::fromUtf8("0.1"));
        pbStep1->setCheckable(true);
        pbStep1->setAutoExclusive(true);

        gridLayout_40->addWidget(pbStep1, 0, 3, 1, 1);

        pbStep0 = new QToolButton(groupBoxStepMov);
        pbStep0->setObjectName(QString::fromUtf8("pbStep0"));
        sizePolicy4.setHeightForWidth(pbStep0->sizePolicy().hasHeightForWidth());
        pbStep0->setSizePolicy(sizePolicy4);
        pbStep0->setFont(font2);
        pbStep0->setFocusPolicy(Qt::NoFocus);
        pbStep0->setText(QString::fromUtf8("0.01"));
        pbStep0->setCheckable(true);
        pbStep0->setAutoExclusive(true);

        gridLayout_40->addWidget(pbStep0, 0, 1, 1, 1);

        pbStep2 = new QToolButton(groupBoxStepMov);
        pbStep2->setObjectName(QString::fromUtf8("pbStep2"));
        sizePolicy4.setHeightForWidth(pbStep2->sizePolicy().hasHeightForWidth());
        pbStep2->setSizePolicy(sizePolicy4);
        pbStep2->setFont(font2);
        pbStep2->setFocusPolicy(Qt::NoFocus);
        pbStep2->setText(QString::fromUtf8("1"));
        pbStep2->setCheckable(true);
        pbStep2->setAutoExclusive(true);

        gridLayout_40->addWidget(pbStep2, 0, 4, 1, 1);


        gridLayout_15->addLayout(gridLayout_40, 0, 0, 1, 1);


        gridLayout_17->addWidget(groupBoxStepMov, 0, 0, 1, 1);

        groupBoxFmanual = new QGroupBox(tab_4);
        groupBoxFmanual->setObjectName(QString::fromUtf8("groupBoxFmanual"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBoxFmanual->sizePolicy().hasHeightForWidth());
        groupBoxFmanual->setSizePolicy(sizePolicy5);
        groupBoxFmanual->setFocusPolicy(Qt::NoFocus);
        groupBoxFmanual->setContextMenuPolicy(Qt::DefaultContextMenu);
        groupBoxFmanual->setAcceptDrops(false);
        groupBoxFmanual->setCheckable(false);
        groupBoxFmanual->setChecked(false);
        gridLayout_34 = new QGridLayout(groupBoxFmanual);
        gridLayout_34->setSpacing(6);
        gridLayout_34->setContentsMargins(11, 11, 11, 11);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(6);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        pbPlusFman = new QToolButton(groupBoxFmanual);
        pbPlusFman->setObjectName(QString::fromUtf8("pbPlusFman"));
        sizePolicy3.setHeightForWidth(pbPlusFman->sizePolicy().hasHeightForWidth());
        pbPlusFman->setSizePolicy(sizePolicy3);
        pbPlusFman->setMinimumSize(QSize(32, 32));
        pbPlusFman->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/data/icons/plus2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPlusFman->setIcon(icon);
        pbPlusFman->setIconSize(QSize(32, 32));

        gridLayout_16->addWidget(pbPlusFman, 0, 4, 1, 1);

        pbMinusFman = new QToolButton(groupBoxFmanual);
        pbMinusFman->setObjectName(QString::fromUtf8("pbMinusFman"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pbMinusFman->sizePolicy().hasHeightForWidth());
        pbMinusFman->setSizePolicy(sizePolicy6);
        pbMinusFman->setMinimumSize(QSize(32, 32));
        pbMinusFman->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/data/icons/minus1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbMinusFman->setIcon(icon1);
        pbMinusFman->setIconSize(QSize(32, 32));

        gridLayout_16->addWidget(pbMinusFman, 0, 3, 1, 1);

        sbFman = new QDoubleSpinBox(groupBoxFmanual);
        sbFman->setObjectName(QString::fromUtf8("sbFman"));
        sbFman->setMinimumSize(QSize(0, 0));
        sbFman->setFont(font2);
        sbFman->setInputMethodHints(Qt::ImhFormattedNumbersOnly);
        sbFman->setFrame(true);
        sbFman->setAlignment(Qt::AlignCenter);
        sbFman->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbFman->setDecimals(2);
        sbFman->setMinimum(0.010000000000000);
        sbFman->setMaximum(100.000000000000000);
        sbFman->setSingleStep(25.000000000000000);
        sbFman->setValue(10.000000000000000);

        gridLayout_16->addWidget(sbFman, 0, 1, 1, 1);

        pbFast = new QToolButton(groupBoxFmanual);
        pbFast->setObjectName(QString::fromUtf8("pbFast"));
        sizePolicy3.setHeightForWidth(pbFast->sizePolicy().hasHeightForWidth());
        pbFast->setSizePolicy(sizePolicy3);
        pbFast->setMinimumSize(QSize(32, 32));
        pbFast->setFocusPolicy(Qt::NoFocus);
        pbFast->setText(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/data/icons/100.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFast->setIcon(icon2);
        pbFast->setIconSize(QSize(32, 32));

        gridLayout_16->addWidget(pbFast, 0, 0, 1, 1);


        gridLayout_34->addLayout(gridLayout_16, 0, 0, 1, 1);


        gridLayout_17->addWidget(groupBoxFmanual, 1, 0, 1, 1);

        gbDirManualKey = new QGroupBox(tab_4);
        gbDirManualKey->setObjectName(QString::fromUtf8("gbDirManualKey"));
        gbDirManualKey->setFocusPolicy(Qt::NoFocus);
        gbDirManualKey->setFlat(false);
        gbDirManualKey->setCheckable(false);
        gridLayout_5 = new QGridLayout(gbDirManualKey);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pbMinusX = new QToolButton(gbDirManualKey);
        pbMinusX->setObjectName(QString::fromUtf8("pbMinusX"));
        sizePolicy3.setHeightForWidth(pbMinusX->sizePolicy().hasHeightForWidth());
        pbMinusX->setSizePolicy(sizePolicy3);
        pbMinusX->setMinimumSize(QSize(32, 32));
        pbMinusX->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbMinusX, 1, 0, 1, 1);

        pbPlusX = new QToolButton(gbDirManualKey);
        pbPlusX->setObjectName(QString::fromUtf8("pbPlusX"));
        sizePolicy3.setHeightForWidth(pbPlusX->sizePolicy().hasHeightForWidth());
        pbPlusX->setSizePolicy(sizePolicy3);
        pbPlusX->setMinimumSize(QSize(32, 32));
        pbPlusX->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbPlusX, 1, 2, 1, 1);

        pbPlusZ = new QToolButton(gbDirManualKey);
        pbPlusZ->setObjectName(QString::fromUtf8("pbPlusZ"));
        sizePolicy3.setHeightForWidth(pbPlusZ->sizePolicy().hasHeightForWidth());
        pbPlusZ->setSizePolicy(sizePolicy3);
        pbPlusZ->setMinimumSize(QSize(32, 32));
        pbPlusZ->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbPlusZ, 0, 3, 1, 1);

        pbMinusY = new QToolButton(gbDirManualKey);
        pbMinusY->setObjectName(QString::fromUtf8("pbMinusY"));
        sizePolicy3.setHeightForWidth(pbMinusY->sizePolicy().hasHeightForWidth());
        pbMinusY->setSizePolicy(sizePolicy3);
        pbMinusY->setMinimumSize(QSize(32, 32));
        pbMinusY->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbMinusY, 1, 1, 1, 1);

        pbMinusZ = new QToolButton(gbDirManualKey);
        pbMinusZ->setObjectName(QString::fromUtf8("pbMinusZ"));
        sizePolicy3.setHeightForWidth(pbMinusZ->sizePolicy().hasHeightForWidth());
        pbMinusZ->setSizePolicy(sizePolicy3);
        pbMinusZ->setMinimumSize(QSize(32, 32));
        pbMinusZ->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbMinusZ, 1, 3, 1, 1);

        pbPlusA = new QToolButton(gbDirManualKey);
        pbPlusA->setObjectName(QString::fromUtf8("pbPlusA"));
        pbPlusA->setEnabled(true);
        sizePolicy3.setHeightForWidth(pbPlusA->sizePolicy().hasHeightForWidth());
        pbPlusA->setSizePolicy(sizePolicy3);
        pbPlusA->setMinimumSize(QSize(32, 32));
        pbPlusA->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbPlusA, 0, 4, 1, 1);

        pbPlusY = new QToolButton(gbDirManualKey);
        pbPlusY->setObjectName(QString::fromUtf8("pbPlusY"));
        sizePolicy3.setHeightForWidth(pbPlusY->sizePolicy().hasHeightForWidth());
        pbPlusY->setSizePolicy(sizePolicy3);
        pbPlusY->setMinimumSize(QSize(32, 32));
        pbPlusY->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbPlusY, 0, 1, 1, 1);

        pbMinusA = new QToolButton(gbDirManualKey);
        pbMinusA->setObjectName(QString::fromUtf8("pbMinusA"));
        pbMinusA->setEnabled(true);
        sizePolicy3.setHeightForWidth(pbMinusA->sizePolicy().hasHeightForWidth());
        pbMinusA->setSizePolicy(sizePolicy3);
        pbMinusA->setMinimumSize(QSize(32, 32));
        pbMinusA->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pbMinusA, 1, 4, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_2, 1, 0, 1, 1);


        gridLayout_17->addWidget(gbDirManualKey, 2, 0, 1, 1);

        tabWidgetManual->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_6 = new QGridLayout(tab_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_6, 3, 0, 1, 1);

        gbVmodeWhell = new QGroupBox(tab_5);
        gbVmodeWhell->setObjectName(QString::fromUtf8("gbVmodeWhell"));
        gridLayout_26 = new QGridLayout(gbVmodeWhell);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        rbWhellVMode = new QCheckBox(gbVmodeWhell);
        rbWhellVMode->setObjectName(QString::fromUtf8("rbWhellVMode"));
        rbWhellVMode->setMouseTracking(false);
        rbWhellVMode->setFocusPolicy(Qt::NoFocus);

        gridLayout_26->addWidget(rbWhellVMode, 0, 0, 1, 1);


        gridLayout_6->addWidget(gbVmodeWhell, 2, 0, 1, 2);

        gbAxisWhell = new QGroupBox(tab_5);
        gbAxisWhell->setObjectName(QString::fromUtf8("gbAxisWhell"));
        gridLayout_27 = new QGridLayout(gbAxisWhell);
        gridLayout_27->setSpacing(6);
        gridLayout_27->setContentsMargins(11, 11, 11, 11);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        comboBoxWhellAxis = new QComboBox(gbAxisWhell);
        comboBoxWhellAxis->addItem(QString());
        comboBoxWhellAxis->addItem(QString());
        comboBoxWhellAxis->addItem(QString());
        comboBoxWhellAxis->addItem(QString());
        comboBoxWhellAxis->addItem(QString());
        comboBoxWhellAxis->addItem(QString());
        comboBoxWhellAxis->setObjectName(QString::fromUtf8("comboBoxWhellAxis"));
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setWeight(75);
        comboBoxWhellAxis->setFont(font3);
        comboBoxWhellAxis->setFocusPolicy(Qt::NoFocus);
#ifndef QT_NO_TOOLTIP
        comboBoxWhellAxis->setToolTip(QString::fromUtf8(""));
#endif // QT_NO_TOOLTIP

        gridLayout_27->addWidget(comboBoxWhellAxis, 0, 0, 1, 1);


        gridLayout_6->addWidget(gbAxisWhell, 0, 0, 1, 2);

        gbXWhell = new QGroupBox(tab_5);
        gbXWhell->setObjectName(QString::fromUtf8("gbXWhell"));
        gridLayout_25 = new QGridLayout(gbXWhell);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        pbWhellX100 = new QPushButton(gbXWhell);
        buttonGroupWhellX = new QButtonGroup(WLMillControl);
        buttonGroupWhellX->setObjectName(QString::fromUtf8("buttonGroupWhellX"));
        buttonGroupWhellX->addButton(pbWhellX100);
        pbWhellX100->setObjectName(QString::fromUtf8("pbWhellX100"));
        pbWhellX100->setFont(font2);
        pbWhellX100->setText(QString::fromUtf8("X100"));
        pbWhellX100->setCheckable(true);
        pbWhellX100->setAutoExclusive(true);

        gridLayout_25->addWidget(pbWhellX100, 0, 2, 1, 1);

        pbWhellX1 = new QPushButton(gbXWhell);
        buttonGroupWhellX->addButton(pbWhellX1);
        pbWhellX1->setObjectName(QString::fromUtf8("pbWhellX1"));
        pbWhellX1->setFont(font2);
        pbWhellX1->setText(QString::fromUtf8("X1"));
        pbWhellX1->setCheckable(true);
        pbWhellX1->setChecked(true);
        pbWhellX1->setAutoExclusive(true);

        gridLayout_25->addWidget(pbWhellX1, 0, 0, 1, 1);

        pbWhellX10 = new QPushButton(gbXWhell);
        buttonGroupWhellX->addButton(pbWhellX10);
        pbWhellX10->setObjectName(QString::fromUtf8("pbWhellX10"));
        pbWhellX10->setFont(font2);
        pbWhellX10->setText(QString::fromUtf8("X10"));
        pbWhellX10->setCheckable(true);
        pbWhellX10->setAutoExclusive(true);

        gridLayout_25->addWidget(pbWhellX10, 0, 1, 1, 1);


        gridLayout_6->addWidget(gbXWhell, 1, 0, 1, 2);

        tabWidgetManual->addTab(tab_5, QString());

        gridLayout_8->addWidget(tabWidgetManual, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_23 = new QGridLayout(tab_3);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        pbEditScript = new QPushButton(tab_3);
        pbEditScript->setObjectName(QString::fromUtf8("pbEditScript"));

        gridLayout_23->addWidget(pbEditScript, 0, 0, 1, 1);

        pbResetScript = new QPushButton(tab_3);
        pbResetScript->setObjectName(QString::fromUtf8("pbResetScript"));
        pbResetScript->setEnabled(false);

        gridLayout_23->addWidget(pbResetScript, 0, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_23->addItem(verticalSpacer_5, 3, 0, 1, 1);

        groupBoxScript = new QGroupBox(tab_3);
        groupBoxScript->setObjectName(QString::fromUtf8("groupBoxScript"));
        gridLayout_22 = new QGridLayout(groupBoxScript);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        leRunScript = new QLineEdit(groupBoxScript);
        leRunScript->setObjectName(QString::fromUtf8("leRunScript"));

        gridLayout_22->addWidget(leRunScript, 0, 0, 1, 1);


        gridLayout_23->addWidget(groupBoxScript, 1, 0, 1, 2);

        tabWidget->addTab(tab_3, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        gridLayout_28 = new QGridLayout(tab_6);
        gridLayout_28->setSpacing(6);
        gridLayout_28->setContentsMargins(11, 11, 11, 11);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        groupBox_3 = new QGroupBox(tab_6);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_13 = new QGridLayout(groupBox_3);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        sbFtouch = new QDoubleSpinBox(groupBox_3);
        sbFtouch->setObjectName(QString::fromUtf8("sbFtouch"));
        sbFtouch->setFont(font2);
        sbFtouch->setSuffix(QString::fromUtf8("mm/m"));
        sbFtouch->setMinimum(0.010000000000000);
        sbFtouch->setMaximum(500.000000000000000);

        gridLayout_13->addWidget(sbFtouch, 0, 0, 1, 1);


        gridLayout_28->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_8 = new QGroupBox(tab_6);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout_14 = new QGridLayout(groupBox_8);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        rbProbeSD = new QRadioButton(groupBox_8);
        buttonGroup = new QButtonGroup(WLMillControl);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(rbProbeSD);
        rbProbeSD->setObjectName(QString::fromUtf8("rbProbeSD"));
        rbProbeSD->setEnabled(true);

        gridLayout_7->addWidget(rbProbeSD, 0, 0, 1, 1);

        cbDSide = new QCheckBox(groupBox_8);
        cbDSide->setObjectName(QString::fromUtf8("cbDSide"));

        gridLayout_7->addWidget(cbDSide, 1, 1, 1, 1);

        rbProbeSD_2 = new QRadioButton(groupBox_8);
        buttonGroup->addButton(rbProbeSD_2);
        rbProbeSD_2->setObjectName(QString::fromUtf8("rbProbeSD_2"));
        rbProbeSD_2->setEnabled(true);
        rbProbeSD_2->setChecked(true);

        gridLayout_7->addWidget(rbProbeSD_2, 1, 0, 1, 1);


        gridLayout_14->addLayout(gridLayout_7, 0, 0, 1, 1);


        gridLayout_28->addWidget(groupBox_8, 2, 0, 1, 2);

        groupBox_4 = new QGroupBox(tab_6);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_24 = new QGridLayout(groupBox_4);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        labelInProbe = new QLabel(groupBox_4);
        labelInProbe->setObjectName(QString::fromUtf8("labelInProbe"));
        sizePolicy2.setHeightForWidth(labelInProbe->sizePolicy().hasHeightForWidth());
        labelInProbe->setSizePolicy(sizePolicy2);
        labelInProbe->setBaseSize(QSize(6, 0));
        labelInProbe->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_24->addWidget(labelInProbe, 0, 0, 1, 1);


        gridLayout_28->addWidget(groupBox_4, 1, 1, 1, 1);

        groupBox = new QGroupBox(tab_6);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        pbPlusProbeX = new QToolButton(groupBox);
        pbPlusProbeX->setObjectName(QString::fromUtf8("pbPlusProbeX"));
        sizePolicy1.setHeightForWidth(pbPlusProbeX->sizePolicy().hasHeightForWidth());
        pbPlusProbeX->setSizePolicy(sizePolicy1);
        pbPlusProbeX->setMinimumSize(QSize(0, 0));
        pbPlusProbeX->setText(QString::fromUtf8("X+"));

        gridLayout_9->addWidget(pbPlusProbeX, 1, 2, 1, 1);

        pbMinusProbeY = new QToolButton(groupBox);
        pbMinusProbeY->setObjectName(QString::fromUtf8("pbMinusProbeY"));
        sizePolicy1.setHeightForWidth(pbMinusProbeY->sizePolicy().hasHeightForWidth());
        pbMinusProbeY->setSizePolicy(sizePolicy1);
        pbMinusProbeY->setMinimumSize(QSize(0, 0));
        pbMinusProbeY->setText(QString::fromUtf8("Y-"));

        gridLayout_9->addWidget(pbMinusProbeY, 1, 1, 1, 1);

        pbMinusProbeX = new QToolButton(groupBox);
        pbMinusProbeX->setObjectName(QString::fromUtf8("pbMinusProbeX"));
        sizePolicy1.setHeightForWidth(pbMinusProbeX->sizePolicy().hasHeightForWidth());
        pbMinusProbeX->setSizePolicy(sizePolicy1);
        pbMinusProbeX->setMinimumSize(QSize(0, 0));
        pbMinusProbeX->setText(QString::fromUtf8("X-"));

        gridLayout_9->addWidget(pbMinusProbeX, 1, 0, 1, 1);

        pbMinusProbeZ = new QToolButton(groupBox);
        pbMinusProbeZ->setObjectName(QString::fromUtf8("pbMinusProbeZ"));
        sizePolicy1.setHeightForWidth(pbMinusProbeZ->sizePolicy().hasHeightForWidth());
        pbMinusProbeZ->setSizePolicy(sizePolicy1);
        pbMinusProbeZ->setMinimumSize(QSize(0, 0));
        pbMinusProbeZ->setText(QString::fromUtf8("Z-"));

        gridLayout_9->addWidget(pbMinusProbeZ, 1, 3, 1, 1);

        pbPlusProbeY = new QToolButton(groupBox);
        pbPlusProbeY->setObjectName(QString::fromUtf8("pbPlusProbeY"));
        sizePolicy1.setHeightForWidth(pbPlusProbeY->sizePolicy().hasHeightForWidth());
        pbPlusProbeY->setSizePolicy(sizePolicy1);
        pbPlusProbeY->setMinimumSize(QSize(0, 0));
        pbPlusProbeY->setText(QString::fromUtf8("Y+"));

        gridLayout_9->addWidget(pbPlusProbeY, 0, 1, 1, 1);

        pbPlusProbeA = new QToolButton(groupBox);
        pbPlusProbeA->setObjectName(QString::fromUtf8("pbPlusProbeA"));
        sizePolicy1.setHeightForWidth(pbPlusProbeA->sizePolicy().hasHeightForWidth());
        pbPlusProbeA->setSizePolicy(sizePolicy1);
        pbPlusProbeA->setMinimumSize(QSize(0, 0));
        pbPlusProbeA->setText(QString::fromUtf8("A+"));

        gridLayout_9->addWidget(pbPlusProbeA, 0, 4, 1, 1);

        pbMinusProbeA = new QToolButton(groupBox);
        pbMinusProbeA->setObjectName(QString::fromUtf8("pbMinusProbeA"));
        sizePolicy1.setHeightForWidth(pbMinusProbeA->sizePolicy().hasHeightForWidth());
        pbMinusProbeA->setSizePolicy(sizePolicy1);
        pbMinusProbeA->setMinimumSize(QSize(0, 0));
        pbMinusProbeA->setText(QString::fromUtf8("A-"));

        gridLayout_9->addWidget(pbMinusProbeA, 1, 4, 1, 1);

        pbPlusProbeZ = new QToolButton(groupBox);
        pbPlusProbeZ->setObjectName(QString::fromUtf8("pbPlusProbeZ"));
        sizePolicy1.setHeightForWidth(pbPlusProbeZ->sizePolicy().hasHeightForWidth());
        pbPlusProbeZ->setSizePolicy(sizePolicy1);
        pbPlusProbeZ->setMinimumSize(QSize(0, 0));
        pbPlusProbeZ->setText(QString::fromUtf8("Z+"));

        gridLayout_9->addWidget(pbPlusProbeZ, 0, 3, 1, 1);

        pbMinusProbeH = new QToolButton(groupBox);
        pbMinusProbeH->setObjectName(QString::fromUtf8("pbMinusProbeH"));
        sizePolicy1.setHeightForWidth(pbMinusProbeH->sizePolicy().hasHeightForWidth());
        pbMinusProbeH->setSizePolicy(sizePolicy1);
        pbMinusProbeH->setMinimumSize(QSize(0, 0));
        pbMinusProbeH->setText(QString::fromUtf8("H"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/data/icons/H.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbMinusProbeH->setIcon(icon3);
        pbMinusProbeH->setIconSize(QSize(32, 32));

        gridLayout_9->addWidget(pbMinusProbeH, 0, 2, 1, 1);

        pbStopTouch = new QToolButton(groupBox);
        pbStopTouch->setObjectName(QString::fromUtf8("pbStopTouch"));
        sizePolicy1.setHeightForWidth(pbStopTouch->sizePolicy().hasHeightForWidth());
        pbStopTouch->setSizePolicy(sizePolicy1);
        pbStopTouch->setMinimumSize(QSize(0, 0));
        pbStopTouch->setText(QString::fromUtf8("STOP"));

        gridLayout_9->addWidget(pbStopTouch, 0, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 0, 0, 1, 1);


        gridLayout_28->addWidget(groupBox, 3, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_28->addItem(verticalSpacer_3, 4, 1, 1, 1);

        tabWidget->addTab(tab_6, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        gridLayout_33 = new QGridLayout(tab_8);
        gridLayout_33->setSpacing(6);
        gridLayout_33->setContentsMargins(11, 11, 11, 11);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        pbUpdateTool = new QPushButton(tab_8);
        pbUpdateTool->setObjectName(QString::fromUtf8("pbUpdateTool"));

        gridLayout_33->addWidget(pbUpdateTool, 2, 0, 1, 1);

        tableTools = new QTableWidget(tab_8);
        tableTools->setObjectName(QString::fromUtf8("tableTools"));

        gridLayout_33->addWidget(tableTools, 1, 0, 1, 3);

        groupBox_14 = new QGroupBox(tab_8);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        gridLayout_32 = new QGridLayout(groupBox_14);
        gridLayout_32->setSpacing(6);
        gridLayout_32->setContentsMargins(11, 11, 11, 11);
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        labelBaseOffsetTool = new QLabel(groupBox_14);
        labelBaseOffsetTool->setObjectName(QString::fromUtf8("labelBaseOffsetTool"));
        labelBaseOffsetTool->setText(QString::fromUtf8("Base offset"));

        gridLayout_32->addWidget(labelBaseOffsetTool, 0, 0, 1, 1);

        pbEditOffsetTool = new QPushButton(groupBox_14);
        pbEditOffsetTool->setObjectName(QString::fromUtf8("pbEditOffsetTool"));

        gridLayout_32->addWidget(pbEditOffsetTool, 0, 1, 1, 1);


        gridLayout_33->addWidget(groupBox_14, 0, 0, 1, 3);

        pbAcceptTool = new QPushButton(tab_8);
        pbAcceptTool->setObjectName(QString::fromUtf8("pbAcceptTool"));

        gridLayout_33->addWidget(pbAcceptTool, 2, 2, 1, 1);

        tabWidget->addTab(tab_8, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        gridLayout_30 = new QGridLayout(tab_7);
        gridLayout_30->setSpacing(6);
        gridLayout_30->setContentsMargins(11, 11, 11, 11);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        groupBox_2 = new QGroupBox(tab_7);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pbSetSCor = new QPushButton(groupBox_2);
        pbSetSCor->setObjectName(QString::fromUtf8("pbSetSCor"));

        gridLayout_4->addWidget(pbSetSCor, 0, 0, 1, 1);

        pbClearSCor = new QPushButton(groupBox_2);
        pbClearSCor->setObjectName(QString::fromUtf8("pbClearSCor"));

        gridLayout_4->addWidget(pbClearSCor, 0, 1, 1, 1);


        gridLayout_30->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_5 = new QGroupBox(tab_7);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        gridLayout_31 = new QGridLayout(groupBox_5);
        gridLayout_31->setSpacing(6);
        gridLayout_31->setContentsMargins(11, 11, 11, 11);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        pbRFindAxis = new QPushButton(groupBox_5);
        pbRFindAxis->setObjectName(QString::fromUtf8("pbRFindAxis"));

        gridLayout_31->addWidget(pbRFindAxis, 1, 0, 1, 1);

        pbStartTeachAxis = new QPushButton(groupBox_5);
        pbStartTeachAxis->setObjectName(QString::fromUtf8("pbStartTeachAxis"));

        gridLayout_31->addWidget(pbStartTeachAxis, 0, 1, 1, 1);

        cbServiceAxis = new QComboBox(groupBox_5);
        cbServiceAxis->addItem(QString());
        cbServiceAxis->addItem(QString());
        cbServiceAxis->addItem(QString());
        cbServiceAxis->addItem(QString());
        cbServiceAxis->addItem(QString());
        cbServiceAxis->setObjectName(QString::fromUtf8("cbServiceAxis"));

        gridLayout_31->addWidget(cbServiceAxis, 0, 0, 1, 1);

        pbStartFindAxis = new QPushButton(groupBox_5);
        pbStartFindAxis->setObjectName(QString::fromUtf8("pbStartFindAxis"));

        gridLayout_31->addWidget(pbStartFindAxis, 1, 1, 1, 1);

        pbGetMSLimit = new QPushButton(groupBox_5);
        pbGetMSLimit->setObjectName(QString::fromUtf8("pbGetMSLimit"));

        gridLayout_31->addWidget(pbGetMSLimit, 2, 0, 1, 1);

        pbGetPSLimit = new QPushButton(groupBox_5);
        pbGetPSLimit->setObjectName(QString::fromUtf8("pbGetPSLimit"));

        gridLayout_31->addWidget(pbGetPSLimit, 2, 1, 1, 1);


        gridLayout_30->addWidget(groupBox_5, 0, 0, 1, 1);

        verticalSpacer_9 = new QSpacerItem(20, 289, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_30->addItem(verticalSpacer_9, 2, 0, 1, 1);

        tabWidget->addTab(tab_7, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(Tab);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_20 = new QGridLayout(page_2);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        pushButtonPause = new QPushButton(page_2);
        pushButtonPause->setObjectName(QString::fromUtf8("pushButtonPause"));
        pushButtonPause->setCheckable(false);

        gridLayout_20->addWidget(pushButtonPause, 4, 1, 1, 1);

        groupBox_10 = new QGroupBox(page_2);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        gridLayout_21 = new QGridLayout(groupBox_10);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        labelTimeLeft = new WLLabel(groupBox_10);
        labelTimeLeft->setObjectName(QString::fromUtf8("labelTimeLeft"));

        gridLayout_21->addWidget(labelTimeLeft, 0, 0, 1, 1);

        labelTimeEnd = new WLLabel(groupBox_10);
        labelTimeEnd->setObjectName(QString::fromUtf8("labelTimeEnd"));

        gridLayout_21->addWidget(labelTimeEnd, 1, 0, 1, 1);


        gridLayout_20->addWidget(groupBox_10, 3, 0, 1, 2);

        groupBox_7 = new QGroupBox(page_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        gridLayout_18 = new QGridLayout(groupBox_7);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        labelBufPC = new WLLabel(groupBox_7);
        labelBufPC->setObjectName(QString::fromUtf8("labelBufPC"));

        gridLayout_18->addWidget(labelBufPC, 1, 0, 1, 1);

        labelBufDev = new WLLabel(groupBox_7);
        labelBufDev->setObjectName(QString::fromUtf8("labelBufDev"));

        gridLayout_18->addWidget(labelBufDev, 2, 0, 1, 1);

        labelProgram = new WLLabel(groupBox_7);
        labelProgram->setObjectName(QString::fromUtf8("labelProgram"));

        gridLayout_18->addWidget(labelProgram, 0, 0, 1, 1);


        gridLayout_20->addWidget(groupBox_7, 2, 0, 1, 2);

        pushButtonGo = new QPushButton(page_2);
        pushButtonGo->setObjectName(QString::fromUtf8("pushButtonGo"));
        pushButtonGo->setCheckable(false);

        gridLayout_20->addWidget(pushButtonGo, 4, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_20->addItem(verticalSpacer_4, 5, 0, 1, 1);

        gbFcor = new QGroupBox(page_2);
        gbFcor->setObjectName(QString::fromUtf8("gbFcor"));
        gridLayout_11 = new QGridLayout(gbFcor);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(6, -1, -1, -1);
        gridLayout_39 = new QGridLayout();
        gridLayout_39->setSpacing(6);
        gridLayout_39->setObjectName(QString::fromUtf8("gridLayout_39"));
        gridLayout_39->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_39->setContentsMargins(0, -1, -1, -1);
        sbFper = new QDoubleSpinBox(gbFcor);
        sbFper->setObjectName(QString::fromUtf8("sbFper"));
        sizePolicy1.setHeightForWidth(sbFper->sizePolicy().hasHeightForWidth());
        sbFper->setSizePolicy(sizePolicy1);
        sbFper->setFont(font2);
        sbFper->setAlignment(Qt::AlignCenter);
        sbFper->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbFper->setDecimals(1);
        sbFper->setMinimum(0.100000000000000);
        sbFper->setMaximum(300.000000000000000);
        sbFper->setSingleStep(0.100000000000000);
        sbFper->setValue(100.000000000000000);

        gridLayout_39->addWidget(sbFper, 3, 3, 1, 1);

        pbPlusF = new QToolButton(gbFcor);
        pbPlusF->setObjectName(QString::fromUtf8("pbPlusF"));
        pbPlusF->setFocusPolicy(Qt::NoFocus);
        pbPlusF->setIcon(icon);
        pbPlusF->setIconSize(QSize(32, 32));
        pbPlusF->setAutoRepeat(true);

        gridLayout_39->addWidget(pbPlusF, 3, 6, 1, 1);

        pbMinusF = new QToolButton(gbFcor);
        pbMinusF->setObjectName(QString::fromUtf8("pbMinusF"));
        pbMinusF->setFocusPolicy(Qt::NoFocus);
        pbMinusF->setIcon(icon1);
        pbMinusF->setIconSize(QSize(32, 32));
        pbMinusF->setAutoRepeat(true);

        gridLayout_39->addWidget(pbMinusF, 3, 5, 1, 1);

        pbF100 = new QToolButton(gbFcor);
        pbF100->setObjectName(QString::fromUtf8("pbF100"));
        pbF100->setFocusPolicy(Qt::NoFocus);
        pbF100->setIcon(icon2);
        pbF100->setIconSize(QSize(32, 32));

        gridLayout_39->addWidget(pbF100, 3, 2, 1, 1);

        labelF = new WLLabel(gbFcor);
        labelF->setObjectName(QString::fromUtf8("labelF"));
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(labelF->sizePolicy().hasHeightForWidth());
        labelF->setSizePolicy(sizePolicy7);
        labelF->setMinimumSize(QSize(85, 0));
        labelF->setMaximumSize(QSize(85, 16777215));
        labelF->setFont(font2);
        labelF->setScaledContents(false);
        labelF->setWordWrap(false);

        gridLayout_39->addWidget(labelF, 3, 1, 1, 1);


        gridLayout_11->addLayout(gridLayout_39, 0, 0, 1, 1);


        gridLayout_20->addWidget(gbFcor, 1, 0, 1, 2);

        stackedWidget->addWidget(page_2);
        groupBox_7->raise();
        pushButtonGo->raise();
        pushButtonPause->raise();
        groupBox_10->raise();
        gbFcor->raise();

        gridLayout_12->addWidget(stackedWidget, 2, 0, 1, 1);

        gbScor = new QGroupBox(WLMillControl);
        gbScor->setObjectName(QString::fromUtf8("gbScor"));
        gridLayout_36 = new QGridLayout(gbScor);
        gridLayout_36->setSpacing(6);
        gridLayout_36->setContentsMargins(11, 11, 11, 11);
        gridLayout_36->setObjectName(QString::fromUtf8("gridLayout_36"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelS = new WLLabel(gbScor);
        labelS->setObjectName(QString::fromUtf8("labelS"));
        sizePolicy7.setHeightForWidth(labelS->sizePolicy().hasHeightForWidth());
        labelS->setSizePolicy(sizePolicy7);
        labelS->setMinimumSize(QSize(85, 0));
        labelS->setMaximumSize(QSize(85, 16777215));
        labelS->setFont(font2);
        labelS->setScaledContents(false);
        labelS->setWordWrap(false);

        horizontalLayout->addWidget(labelS);

        pbS100 = new QToolButton(gbScor);
        pbS100->setObjectName(QString::fromUtf8("pbS100"));
        pbS100->setFocusPolicy(Qt::NoFocus);
        pbS100->setIcon(icon2);
        pbS100->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(pbS100);

        sbSper = new QDoubleSpinBox(gbScor);
        sbSper->setObjectName(QString::fromUtf8("sbSper"));
        sizePolicy1.setHeightForWidth(sbSper->sizePolicy().hasHeightForWidth());
        sbSper->setSizePolicy(sizePolicy1);
        sbSper->setFont(font2);
        sbSper->setAlignment(Qt::AlignCenter);
        sbSper->setButtonSymbols(QAbstractSpinBox::NoButtons);
        sbSper->setCorrectionMode(QAbstractSpinBox::CorrectToPreviousValue);
        sbSper->setDecimals(1);
        sbSper->setMinimum(0.100000000000000);
        sbSper->setMaximum(300.000000000000000);
        sbSper->setSingleStep(0.100000000000000);
        sbSper->setValue(100.000000000000000);

        horizontalLayout->addWidget(sbSper);

        pbMinusS = new QToolButton(gbScor);
        pbMinusS->setObjectName(QString::fromUtf8("pbMinusS"));
        pbMinusS->setFocusPolicy(Qt::NoFocus);
        pbMinusS->setIcon(icon1);
        pbMinusS->setIconSize(QSize(32, 32));
        pbMinusS->setAutoRepeat(true);

        horizontalLayout->addWidget(pbMinusS);

        pbPlusS = new QToolButton(gbScor);
        pbPlusS->setObjectName(QString::fromUtf8("pbPlusS"));
        pbPlusS->setFocusPolicy(Qt::NoFocus);
        pbPlusS->setIcon(icon);
        pbPlusS->setIconSize(QSize(30, 32));
        pbPlusS->setAutoRepeat(true);

        horizontalLayout->addWidget(pbPlusS);


        gridLayout_36->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_12->addWidget(gbScor, 1, 0, 1, 1);


        retranslateUi(WLMillControl);
        QObject::connect(cbSmooth, SIGNAL(toggled(bool)), sbSmoothDist, SLOT(setEnabled(bool)));
        QObject::connect(cbOneTool, SIGNAL(toggled(bool)), sbOneTool, SLOT(setEnabled(bool)));
        QObject::connect(cbSimpli, SIGNAL(toggled(bool)), sbSimpliDist, SLOT(setEnabled(bool)));

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);
        tabWidgetManual->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WLMillControl);
    } // setupUi

    void retranslateUi(QWidget *WLMillControl)
    {
        WLMillControl->setWindowTitle(QApplication::translate("WLMillControl", "WLMillControl", nullptr));
        groupBox_6->setTitle(QApplication::translate("WLMillControl", "Program", nullptr));
        cbOneTool->setText(QApplication::translate("WLMillControl", "one tool", nullptr));
        pushButtonOnProgram->setText(QApplication::translate("WLMillControl", "Load traj", nullptr));
        groupBox_13->setTitle(QApplication::translate("WLMillControl", "Config", nullptr));
        cbAutoStart->setText(QApplication::translate("WLMillControl", "autostart", nullptr));
        cbBLNextMov->setText(QApplication::translate("WLMillControl", "advance backlash", nullptr));
        groupBox_15->setTitle(QApplication::translate("WLMillControl", "trajectory change", nullptr));
        cbSmooth->setText(QApplication::translate("WLMillControl", "smooth", nullptr));
        cbSimpli->setText(QApplication::translate("WLMillControl", "simplification", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("WLMillControl", "Auto", nullptr));
#ifndef QT_NO_TOOLTIP
        groupBoxStepMov->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupBoxStepMov->setTitle(QApplication::translate("WLMillControl", "Step", nullptr));
#ifndef QT_NO_TOOLTIP
        groupBoxFmanual->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupBoxFmanual->setTitle(QApplication::translate("WLMillControl", "Feed", nullptr));
        pbPlusFman->setText(QString());
#ifndef QT_NO_SHORTCUT
        pbPlusFman->setShortcut(QApplication::translate("WLMillControl", "+", nullptr));
#endif // QT_NO_SHORTCUT
        pbMinusFman->setText(QApplication::translate("WLMillControl", "-", nullptr));
#ifndef QT_NO_SHORTCUT
        pbMinusFman->setShortcut(QApplication::translate("WLMillControl", "-", nullptr));
#endif // QT_NO_SHORTCUT
        sbFman->setPrefix(QApplication::translate("WLMillControl", "F:", nullptr));
        sbFman->setSuffix(QApplication::translate("WLMillControl", "%", nullptr));
#ifndef QT_NO_TOOLTIP
        pbFast->setToolTip(QApplication::translate("WLMillControl", "Feed = 100% (SHIFT)", nullptr));
#endif // QT_NO_TOOLTIP
        gbDirManualKey->setTitle(QApplication::translate("WLMillControl", "Direction", nullptr));
        pbMinusX->setText(QApplication::translate("WLMillControl", "X-", nullptr));
        pbPlusX->setText(QApplication::translate("WLMillControl", "X+", nullptr));
#ifndef QT_NO_SHORTCUT
        pbPlusX->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        pbPlusZ->setText(QApplication::translate("WLMillControl", "Z+", nullptr));
        pbMinusY->setText(QApplication::translate("WLMillControl", "Y-", nullptr));
        pbMinusZ->setText(QApplication::translate("WLMillControl", "Z-", nullptr));
        pbPlusA->setText(QApplication::translate("WLMillControl", "A+", nullptr));
        pbPlusY->setText(QApplication::translate("WLMillControl", "Y+", nullptr));
        pbMinusA->setText(QApplication::translate("WLMillControl", "A-", nullptr));
        tabWidgetManual->setTabText(tabWidgetManual->indexOf(tab_4), QApplication::translate("WLMillControl", "Keyboard", nullptr));
        gbVmodeWhell->setTitle(QApplication::translate("WLMillControl", "Mode", nullptr));
        rbWhellVMode->setText(QApplication::translate("WLMillControl", "Vellocity", nullptr));
        gbAxisWhell->setTitle(QApplication::translate("WLMillControl", "Axis", nullptr));
        comboBoxWhellAxis->setItemText(0, QApplication::translate("WLMillControl", "OFF", nullptr));
        comboBoxWhellAxis->setItemText(1, QApplication::translate("WLMillControl", "X", nullptr));
        comboBoxWhellAxis->setItemText(2, QApplication::translate("WLMillControl", "Y", nullptr));
        comboBoxWhellAxis->setItemText(3, QApplication::translate("WLMillControl", "Z", nullptr));
        comboBoxWhellAxis->setItemText(4, QApplication::translate("WLMillControl", "A", nullptr));
        comboBoxWhellAxis->setItemText(5, QApplication::translate("WLMillControl", "B", nullptr));

        gbXWhell->setTitle(QApplication::translate("WLMillControl", "Scale", nullptr));
        tabWidgetManual->setTabText(tabWidgetManual->indexOf(tab_5), QApplication::translate("WLMillControl", "Whell", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("WLMillControl", "Manual", nullptr));
        pbEditScript->setText(QApplication::translate("WLMillControl", "Edit Script", nullptr));
        pbResetScript->setText(QApplication::translate("WLMillControl", "Reser Script", nullptr));
        groupBoxScript->setTitle(QApplication::translate("WLMillControl", "Script", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("WLMillControl", "Script", nullptr));
        groupBox_3->setTitle(QApplication::translate("WLMillControl", "Feed", nullptr));
        sbFtouch->setPrefix(QString());
        groupBox_8->setTitle(QApplication::translate("WLMillControl", "Mode", nullptr));
        rbProbeSD->setText(QApplication::translate("WLMillControl", "Slow down stop", nullptr));
        cbDSide->setText(QApplication::translate("WLMillControl", "2 side", nullptr));
        rbProbeSD_2->setText(QApplication::translate("WLMillControl", "EMG Stop", nullptr));
        groupBox_4->setTitle(QApplication::translate("WLMillControl", "Input", nullptr));
        labelInProbe->setText(QApplication::translate("WLMillControl", "Probe", nullptr));
        groupBox->setTitle(QApplication::translate("WLMillControl", "Direction", nullptr));
#ifndef QT_NO_SHORTCUT
        pbPlusProbeX->setShortcut(QString());
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_SHORTCUT
        pbStopTouch->setShortcut(QApplication::translate("WLMillControl", "Space", nullptr));
#endif // QT_NO_SHORTCUT
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("WLMillControl", "Probe", nullptr));
        pbUpdateTool->setText(QApplication::translate("WLMillControl", "Update", nullptr));
        groupBox_14->setTitle(QApplication::translate("WLMillControl", "config", nullptr));
        pbEditOffsetTool->setText(QApplication::translate("WLMillControl", "\320\270\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pbAcceptTool->setText(QApplication::translate("WLMillControl", "Accept", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("WLMillControl", "Tools", nullptr));
        groupBox_2->setTitle(QApplication::translate("WLMillControl", "out S correct", nullptr));
        pbSetSCor->setText(QApplication::translate("WLMillControl", "add point", nullptr));
        pbClearSCor->setText(QApplication::translate("WLMillControl", "clear", nullptr));
        groupBox_5->setTitle(QApplication::translate("WLMillControl", "Axis", nullptr));
        pbRFindAxis->setText(QApplication::translate("WLMillControl", "Reset Find", nullptr));
        pbStartTeachAxis->setText(QApplication::translate("WLMillControl", "Teach", nullptr));
        cbServiceAxis->setItemText(0, QApplication::translate("WLMillControl", "X", nullptr));
        cbServiceAxis->setItemText(1, QApplication::translate("WLMillControl", "Y", nullptr));
        cbServiceAxis->setItemText(2, QApplication::translate("WLMillControl", "Z", nullptr));
        cbServiceAxis->setItemText(3, QApplication::translate("WLMillControl", "A", nullptr));
        cbServiceAxis->setItemText(4, QApplication::translate("WLMillControl", "B", nullptr));

        pbStartFindAxis->setText(QApplication::translate("WLMillControl", "Find", nullptr));
        pbGetMSLimit->setText(QApplication::translate("WLMillControl", "Get Minus Soft Limit", nullptr));
        pbGetPSLimit->setText(QApplication::translate("WLMillControl", "Get Plus Soft Limit", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("WLMillControl", "Service", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonPause->setToolTip(QApplication::translate("WLMillControl", "(space)", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonPause->setText(QApplication::translate("WLMillControl", "Pause", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButtonPause->setShortcut(QApplication::translate("WLMillControl", "Space", nullptr));
#endif // QT_NO_SHORTCUT
        groupBox_10->setTitle(QApplication::translate("WLMillControl", "Times", nullptr));
        labelTimeLeft->setText(QApplication::translate("WLMillControl", "Left:", nullptr));
        labelTimeEnd->setText(QApplication::translate("WLMillControl", "End:", nullptr));
        groupBox_7->setTitle(QApplication::translate("WLMillControl", "Buffers", nullptr));
        labelBufPC->setText(QApplication::translate("WLMillControl", "PC:", nullptr));
        labelBufDev->setText(QApplication::translate("WLMillControl", "Device:", nullptr));
        labelProgram->setText(QApplication::translate("WLMillControl", "Program:", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonGo->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonGo->setText(QApplication::translate("WLMillControl", "Go", nullptr));
        gbFcor->setTitle(QString());
        sbFper->setPrefix(QString());
        sbFper->setSuffix(QApplication::translate("WLMillControl", "%", nullptr));
        pbPlusF->setText(QString());
        pbMinusF->setText(QString());
#ifndef QT_NO_SHORTCUT
        pbMinusF->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        pbF100->setText(QApplication::translate("WLMillControl", "100", nullptr));
#ifndef QT_NO_SHORTCUT
        pbF100->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        labelF->setText(QApplication::translate("WLMillControl", "F:20000", nullptr));
        gbScor->setTitle(QString());
        labelS->setText(QApplication::translate("WLMillControl", "S:20000", nullptr));
        pbS100->setText(QString());
#ifndef QT_NO_SHORTCUT
        pbS100->setShortcut(QString());
#endif // QT_NO_SHORTCUT
        sbSper->setPrefix(QString());
        sbSper->setSuffix(QApplication::translate("WLMillControl", "%", nullptr));
        pbMinusS->setText(QString());
        pbPlusS->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WLMillControl: public Ui_WLMillControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLMILLCONTROL_H
