#include "wlframewidget.h"

WLFrameWidget::WLFrameWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonCancel,SIGNAL(clicked()),SLOT(onButtonCancel()));
	connect(ui.pushButtonOk,SIGNAL(clicked()),SLOT(onButtonOk()));
	connect(ui.pushButtonFromStr,SIGNAL(clicked()),SLOT(onButtonFromStr()));
	
	//setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint);

	connect(ui.doubleSpinBoxX,SIGNAL(valueChanged(double)),SLOT(updateFrameData()));
	connect(ui.doubleSpinBoxY,SIGNAL(valueChanged(double)),SLOT(updateFrameData()));
	connect(ui.doubleSpinBoxZ,SIGNAL(valueChanged(double)),SLOT(updateFrameData()));
	connect(ui.doubleSpinBoxA,SIGNAL(valueChanged(double)),SLOT(updateFrameData()));
	connect(ui.doubleSpinBoxB,SIGNAL(valueChanged(double)),SLOT(updateFrameData()));
	connect(ui.doubleSpinBoxC,SIGNAL(valueChanged(double)),SLOT(updateFrameData()));
}

WLFrameWidget::~WLFrameWidget()
{

}

void WLFrameWidget::updateFrameData()
{
curFramen.x=ui.doubleSpinBoxX->value();
curFramen.y=ui.doubleSpinBoxY->value();
curFramen.z=ui.doubleSpinBoxZ->value();
curFramen.a=ui.doubleSpinBoxA->value();
curFramen.b=ui.doubleSpinBoxB->value();
curFramen.c=ui.doubleSpinBoxC->value();
curFramen.name=ui.nameFrame->text();

ui.dataFrame->setText(curFramen.toString());

WLFrame Frame=curFramen;

emit changedFrame(Frame);
emit changedFramen(curFramen);
}



void WLFrameWidget::setFramen(WLFramen Framen)
{
curFramen=Framen;
baseFramen=curFramen;

ui.nameFrame->setText(baseFramen.name);

ui.doubleSpinBoxX->setValue(baseFramen.x);
ui.doubleSpinBoxY->setValue(baseFramen.y);
ui.doubleSpinBoxZ->setValue(baseFramen.z);
ui.doubleSpinBoxA->setValue(baseFramen.a);
ui.doubleSpinBoxB->setValue(baseFramen.b);
ui.doubleSpinBoxC->setValue(baseFramen.c);

ui.dataFrame->setText(baseFramen.toString());
}

void WLFrameWidget::setFrame(WLFrame Frame)
{
curFramen=Frame;
baseFramen=curFramen;

ui.nameFrame->setDisabled(true);

ui.doubleSpinBoxX->setValue(baseFramen.x);
ui.doubleSpinBoxY->setValue(baseFramen.y);
ui.doubleSpinBoxZ->setValue(baseFramen.z);
ui.doubleSpinBoxA->setValue(baseFramen.a);
ui.doubleSpinBoxB->setValue(baseFramen.b);
ui.doubleSpinBoxC->setValue(baseFramen.c);

ui.dataFrame->setText(baseFramen.toString());
}

void WLFrameWidget::onButtonFromStr()
{
WLFrame buf=baseFramen;

curFramen.fromString(ui.dataFrame->text());
setFramen(curFramen);

baseFramen=buf;
}