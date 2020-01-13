#ifndef WLMotion_H
#define WLMotion_H

#include "WLDevice.h"

#include "modules/WLModuleDCan.h"
#include "modules/WLModuleIOPut.h"
#include "modules/WLModuleEncoder.h"
#include "modules/WLModuleAxis.h"
#include "modules/WLModuleWhell.h"
#include "modules/WLModulePlanner.h"
#include "modules/WLModulePWM.h"

class WLMotion: public WLDevice
{
	Q_OBJECT

public:
		
	 WLMotion();
	~WLMotion();

protected:
virtual WLModule *createModule(QString name);
virtual WLModule *createModule(typeModule type);

public:
WLModulePlanner* getModulePlanner() {return static_cast<WLModulePlanner*>(getModule(typeMPlanner));}
WLModuleAxis*    getModuleAxis()    {return static_cast<WLModuleAxis*>(getModule(typeMAxis));}
WLModuleIOPut*   getModuleIOPut()   {return static_cast<WLModuleIOPut*>(getModule(typeMIOPut));}
WLModuleWhell*   getModuleWhell()   {return static_cast<WLModuleWhell*>(getModule(typeMWhell));}
WLModulePWM*     getModulePWM()     {return static_cast<WLModulePWM*>(getModule(typeMPWM));}
WLModuleEncoder* getModuleEncoder() {return static_cast<WLModuleEncoder*>(getModule(typeMEncoder));}
};

#endif //WLMOTION_H
