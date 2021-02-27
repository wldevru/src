#include "wlmotion.h"

WLMotion::WLMotion()
{

}
 
WLMotion::~WLMotion()
{

}

WLModule *WLMotion::createModule(QString name)
{
WLModule *Module=WLDevice::createModule(name);

if(Module==nullptr)
{
if(name=="WLModuleDCan")    Module=new WLModuleDCan;
else								 
if(name=="WLModuleIOPut")   Module=new WLModuleIOPut;
else								 
if(name=="WLModuleAIOPut")  Module=new WLModuleAIOPut;
else
if(name=="WLModuleEncoder") Module=new WLModuleEncoder;
else
if(name=="WLModuleWhell"
 ||name=="WLModuleMPG")     Module=new WLModuleMPG;
else								 
if(name=="WLModulePlanner") Module=new WLModulePlanner;
else								 
if(name=="WLModuleAxis"&&getModuleIOPut())    Module=new WLModuleAxis(getModuleIOPut());
else								 
if(name=="WLModulePWM")     Module=new WLModulePWM();		  

addModule(Module);
}

return Module;
}

WLModule *WLMotion::createModule(typeModule type)
{
WLModule *Module=WLDevice::createModule(type);

if(Module==NULL)
{
switch(type)
{
case typeMDCan:   Module=new WLModuleDCan;
	              break;
case typeMIOPut:  Module=new WLModuleIOPut;
	              break;
case typeMAIOPut:  Module=new WLModuleAIOPut;
                  break;
case typeMMPG:    Module=new WLModuleMPG;
	              break;
case typeMEncoder:Module=new WLModuleEncoder;
	              break;
case typeMPlanner:Module=new WLModulePlanner;
	              break;
case typeMAxis:   if(getModuleIOPut()!=NULL)    Module=new WLModuleAxis(getModuleIOPut());
	              break;
case typeMPWM:    Module=new WLModulePWM();		  
	              break;
default: break;
}

addModule(Module);
}

return Module;
}
