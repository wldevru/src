#include "widget.h"
#include "ui_widget.h"
#include "WLMotion.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
QList <WLDeviceInfo> List=WLDevice::availableDevices();

qDebug()<<"total device : "<<List.size();

foreach(WLDeviceInfo info, List)
{
qDebug()<<"Name:"<<info.name<<" v:"<<info.version<<" port:"<<info.comPort;

WLMotion Device;

Device.setInfo(info);
Device.openConnect();

qDebug()<<"Modules:";

auto modules=Device.getModules();

 foreach(WLModule *mod,modules)
  {
  qDebug()<<mod->metaObject()->className();
  }

Device.closeConnect();
}


}
