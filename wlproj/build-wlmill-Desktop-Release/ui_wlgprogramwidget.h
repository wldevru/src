/********************************************************************************
** Form generated from reading UI file 'wlgprogramwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLGPROGRAMWIDGET_H
#define UI_WLGPROGRAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLGProgramWidget
{
public:
    QGridLayout *gridLayout_3;
    QToolButton *pbUpdate;
    QToolButton *pbReload;
    QPushButton *pbBackup;
    QPushButton *pbAccept;
    QProgressBar *progressBar;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout;
    QListWidget *listProgram;
    QScrollBar *vsbProgram;
    QSpinBox *sbPosition;
    QWidget *page_2;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *textProgram;
    QLabel *labelName;

    void setupUi(QWidget *WLGProgramWidget)
    {
        if (WLGProgramWidget->objectName().isEmpty())
            WLGProgramWidget->setObjectName(QString::fromUtf8("WLGProgramWidget"));
        WLGProgramWidget->resize(301, 320);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WLGProgramWidget->sizePolicy().hasHeightForWidth());
        WLGProgramWidget->setSizePolicy(sizePolicy);
        WLGProgramWidget->setLayoutDirection(Qt::LeftToRight);
        gridLayout_3 = new QGridLayout(WLGProgramWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pbUpdate = new QToolButton(WLGProgramWidget);
        pbUpdate->setObjectName(QString::fromUtf8("pbUpdate"));
        pbUpdate->setMinimumSize(QSize(40, 40));
        pbUpdate->setMaximumSize(QSize(40, 40));
        pbUpdate->setText(QString::fromUtf8(""));
        pbUpdate->setIconSize(QSize(30, 30));

        gridLayout_3->addWidget(pbUpdate, 1, 1, 1, 1);

        pbReload = new QToolButton(WLGProgramWidget);
        pbReload->setObjectName(QString::fromUtf8("pbReload"));
        pbReload->setMinimumSize(QSize(40, 40));
        pbReload->setMaximumSize(QSize(40, 40));
        pbReload->setText(QString::fromUtf8(""));
        pbReload->setIconSize(QSize(30, 30));

        gridLayout_3->addWidget(pbReload, 1, 7, 1, 1);

        pbBackup = new QPushButton(WLGProgramWidget);
        pbBackup->setObjectName(QString::fromUtf8("pbBackup"));
        pbBackup->setMinimumSize(QSize(40, 40));
        pbBackup->setMaximumSize(QSize(40, 40));
        pbBackup->setText(QString::fromUtf8(""));
        pbBackup->setIconSize(QSize(30, 30));

        gridLayout_3->addWidget(pbBackup, 1, 6, 1, 1);

        pbAccept = new QPushButton(WLGProgramWidget);
        pbAccept->setObjectName(QString::fromUtf8("pbAccept"));
        pbAccept->setMinimumSize(QSize(40, 40));
        pbAccept->setMaximumSize(QSize(40, 40));
        pbAccept->setText(QString::fromUtf8(""));
        pbAccept->setIconSize(QSize(30, 30));

        gridLayout_3->addWidget(pbAccept, 1, 5, 1, 1);

        progressBar = new QProgressBar(WLGProgramWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setValue(24);
        progressBar->setTextVisible(false);
        progressBar->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(progressBar, 1, 2, 1, 1);

        stackedWidget = new QStackedWidget(WLGProgramWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout = new QGridLayout(page);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listProgram = new QListWidget(page);
        listProgram->setObjectName(QString::fromUtf8("listProgram"));
        listProgram->setFrameShape(QFrame::NoFrame);
        listProgram->setFrameShadow(QFrame::Sunken);
        listProgram->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listProgram->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listProgram->setAutoScroll(true);
        listProgram->setAutoScrollMargin(12);
        listProgram->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listProgram->setAlternatingRowColors(true);
        listProgram->setSelectionMode(QAbstractItemView::NoSelection);
        listProgram->setSelectionBehavior(QAbstractItemView::SelectItems);
        listProgram->setProperty("isWrapping", QVariant(false));
        listProgram->setLayoutMode(QListView::SinglePass);
        listProgram->setBatchSize(10);
        listProgram->setSelectionRectVisible(false);

        gridLayout->addWidget(listProgram, 0, 0, 1, 1);

        vsbProgram = new QScrollBar(page);
        vsbProgram->setObjectName(QString::fromUtf8("vsbProgram"));
        vsbProgram->setPageStep(50);
        vsbProgram->setValue(1);
        vsbProgram->setOrientation(Qt::Vertical);
        vsbProgram->setInvertedControls(false);

        gridLayout->addWidget(vsbProgram, 0, 1, 1, 1);

        sbPosition = new QSpinBox(page);
        sbPosition->setObjectName(QString::fromUtf8("sbPosition"));
        sbPosition->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout->addWidget(sbPosition, 1, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_2 = new QGridLayout(page_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textProgram = new QPlainTextEdit(page_2);
        textProgram->setObjectName(QString::fromUtf8("textProgram"));

        gridLayout_2->addWidget(textProgram, 0, 1, 1, 1);

        stackedWidget->addWidget(page_2);

        gridLayout_3->addWidget(stackedWidget, 2, 1, 7, 7);

        labelName = new QLabel(WLGProgramWidget);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(labelName->sizePolicy().hasHeightForWidth());
        labelName->setSizePolicy(sizePolicy3);
        labelName->setMaximumSize(QSize(290, 16777215));
        labelName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(labelName, 0, 1, 1, 7);

        stackedWidget->raise();
        labelName->raise();
        pbReload->raise();
        pbBackup->raise();
        pbAccept->raise();
        pbUpdate->raise();
        progressBar->raise();

        retranslateUi(WLGProgramWidget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WLGProgramWidget);
    } // setupUi

    void retranslateUi(QWidget *WLGProgramWidget)
    {
        WLGProgramWidget->setWindowTitle(QApplication::translate("WLGProgramWidget", "WLGProgamWidget", nullptr));
#ifndef QT_NO_TOOLTIP
        pbUpdate->setToolTip(QApplication::translate("WLGProgramWidget", "redraw", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pbReload->setToolTip(QApplication::translate("WLGProgramWidget", "reload file", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pbBackup->setToolTip(QApplication::translate("WLGProgramWidget", "backup", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pbAccept->setToolTip(QApplication::translate("WLGProgramWidget", "accept", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sbPosition->setToolTip(QApplication::translate("WLGProgramWidget", "enter number position", nullptr));
#endif // QT_NO_TOOLTIP
        textProgram->setPlainText(QApplication::translate("WLGProgramWidget", "text\n"
"", nullptr));
        labelName->setText(QApplication::translate("WLGProgramWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WLGProgramWidget: public Ui_WLGProgramWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLGPROGRAMWIDGET_H
