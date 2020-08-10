#include "WLMillDriveWidget.h"
#include "ui_WLMillDriveWidget.h"

WLMillDriveWidget::WLMillDriveWidget(WLMillDrive *_drive,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLMillDriveWidget)
{
    m_MDrive=_drive;

    ui->setupUi(this);

    ui->sbBacklash->setValue(m_MDrive->getBacklash());
}

WLMillDriveWidget::~WLMillDriveWidget()
{
    delete ui;
}
