#include "WLDialogObj.h"

WLDialogObj::WLDialogObj(QObject *parent)
	: QObject(parent)
{
reset();
}

WLDialogObj::~WLDialogObj()
{

}

void WLDialogObj::setWidgetDialog(WLDialog *_DialogW)
{
DialogW=_DialogW;

connect(this,SIGNAL(buildMessage(QString)),DialogW,SLOT(showMessage(QString)));
connect(this,SIGNAL(buildEnterNum(QString)),DialogW,SLOT(showEnterNum(QString)));
connect(this,SIGNAL(buildEnterString(QString)),DialogW,SLOT(showEnterString(QString)));
connect(this,SIGNAL(buildSaveFile(QString,QString)),DialogW,SLOT(showSaveFile(QString,QString)));

connect(DialogW,SIGNAL(enterNum(double)),SLOT(setNum(double)));
connect(DialogW,SIGNAL(enterString(QString)),SLOT(setString(QString)));
connect(DialogW,SIGNAL(enterCancel()),SLOT(setCancel()));
}

void WLDialogObj::reset()
{
show=false;
dataNum=0;
dataStr="";
}