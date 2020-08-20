#include "wledittext.h"

WLEditText::WLEditText(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

}

WLEditText::~WLEditText()
{

}

void WLEditText::setText(QString txt)
{
ui.textEdit->setText(txt);
}
