#include "WLDevFW.h"
#include <QDebug>

WLDevFW::WLDevFW()
{
//connect(this,SIGNAL(startSend(QByteArray)),SLOT(sendData(QByteArray)),Qt::QueuedConnection);
setNameDevice("WLDevFW");

WLModuleFW *ModuleFW=new WLModuleFW;
addModule(ModuleFW);
}
 
WLDevFW::~WLDevFW()
{

}

bool WLDevFW::init(QString portName)
{
qDebug()<<"Init WLDevFW ";
/*
if(getModuleFW()==NULL)
 {
 WLModuleFW *ModuleFW=new WLModuleFW;
 addModule(ModuleFW);
 }*/
WLDevice::initSerialPort(portName);
return true;
}


WLModule *WLDevFW::createModule(QString name)
{
WLModule *Module=WLMotion::createModule(name);

if(Module==NULL)
{
if(name=="WLModuleFW")    Module=new WLModuleFW;
addModule(Module);
}

return Module;
}

WLModule *WLDevFW::createModule(typeModule type)
{
WLModule *Module=WLMotion::createModule(type);

if(Module==NULL)
{
switch(type)
 {
 case typeMFW:     Module=new WLModuleFW;
 	              break;
 }
addModule(Module);
}

return Module;
}
