#include "WLDialog.h"

WLDialog::WLDialog(QWidget *parent)
	: QWidget(parent)
{

}

WLDialog::~WLDialog()
{

}

void WLDialog::showEnterNum(QString txt)
{
WLEnterNum EnterNum(this);
EnterNum.setMinMaxNow(-10000,10000,0);
EnterNum.setDecimals(0);
EnterNum.setLabel(txt);
EnterNum.show();

if(EnterNum.exec())
  emit enterNum(EnterNum.getNow());
else
  emit enterCancel();

}

void WLDialog::showEnterString(QString txt)
{

WLEnterString EnterString(this);

EnterString.setLabel(txt);
EnterString.show();

if(EnterString.exec())
  emit enterString(EnterString.getString());
else
  emit enterCancel();
}

void WLDialog::showSaveFile(QString txt,QString lastFile)
{
QString fileName = QFileDialog::getSaveFileName(this, txt,lastFile,"(*.txt)");

if(!fileName.isEmpty())
  emit enterString(fileName);
else
  emit enterCancel();
}



void WLDialog::showMessage(QString txt)
{
QMessageBox::information(this, tr("Message: "),txt,QMessageBox::Ok);
emit enterCancel();
}
