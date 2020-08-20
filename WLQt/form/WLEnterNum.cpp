#include "wlenternum.h"

WLEnterNum::WLEnterNum(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.doubleSpinBox->setFocus();
	ui.doubleSpinBox->selectAll();
}

WLEnterNum::~WLEnterNum()
{

}
