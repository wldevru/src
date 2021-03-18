#include "wldevicewidget.h"


WLDeviceWidget::WLDeviceWidget(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::WLDeviceWidget)
{
    ui->setupUi(this);

    setModal(true);

    updateList();

    connect(ui->pbUpdate,&QPushButton::clicked,this,&WLDeviceWidget::updateList);

    ui->labelDriver->setText("<a href=\https://wldev.ru/data/driver/vcp\">VCP driver for WINDOWS</a>");
    ui->labelDriver->setOpenExternalLinks(true);

    #ifndef Q_OS_WIN
    ui->labelDriver->setVisible(false);
    #endif
}

WLDeviceWidget::~WLDeviceWidget()
{    

}


void WLDeviceWidget::updateList()
{
m_ListInfo=WLDevice::availableDevices();

ui->cbDevice->clear();

if(m_ListInfo.isEmpty()){
ui->cbDevice->addItem(tr("no device"));
}
else
foreach(WLDeviceInfo info,m_ListInfo)
{
ui->cbDevice->addItem(info.name+" ("+info.comPort+info.HA.toString()+") id:"+info.UID96);
}

}

void WLDeviceWidget::on_buttonBox_accepted()
{
done(1);
}

void WLDeviceWidget::on_buttonBox_rejected()
{
done(0);
}
