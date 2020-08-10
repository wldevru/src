#include "WLDeviceWidget.h"


WLDeviceWidget::WLDeviceWidget(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::WLDeviceWidget)
{
    ui->setupUi(this);

    setModal(true);

    init();
}

WLDeviceWidget::~WLDeviceWidget()
{    

}


void WLDeviceWidget::init()
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



/*
QList<QSerialPortInfo> portList=QSerialPortInfo::availablePorts();

foreach(QSerialPortInfo portInfo,portList)
 {
 WLDevice  *Device = new WLDevice;

 Devices<<Device;

 connect(Device,&WLDevice::changedReady,this,&WLDeviceWidget::updateComList);
 Device->initSerialPort(portInfo.portName());
 Device->openConnect();
 }
*/
}

void WLDeviceWidget::updateComList()
{
 /*
ui->cbDevice->clear();

foreach(WLDevice  *Device,Devices)
 {
 ui->cbDevice->addItem(Device->getNameDevice()+" ("+Device->getPortName()+") id:"+Device->getUID96());
 }
*/
}

void WLDeviceWidget::on_buttonBox_accepted()
{
done(1);
}

void WLDeviceWidget::on_buttonBox_rejected()
{
done(0);
}
