#ifndef WLMotion_H
#define WLMotion_H

#include "wldevice.h"

#include "modules/wlmoduledcan.h"
#include "modules/wlmoduleioput.h"
#include "modules/wlmoduleaioput.h"
#include "modules/wlmoduleencoder.h"
#include "modules/wlmoduleaxis.h"
#include "modules/wlmodulempg.h"
#include "modules/wlmoduleplanner.h"
#include "modules/wlmodulepwm.h"

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
WLModuleAIOPut*  getModuleAIOPut()  {return static_cast<WLModuleAIOPut*>(getModule(typeMAIOPut));}
WLModuleMPG*     getModuleMPG()     {return static_cast<WLModuleMPG*>(getModule(typeMMPG));}
WLModulePWM*     getModulePWM()     {return static_cast<WLModulePWM*>(getModule(typeMPWM));}
WLModuleEncoder* getModuleEncoder() {return static_cast<WLModuleEncoder*>(getModule(typeMEncoder));}
};

#endif //WLMOTION_H
