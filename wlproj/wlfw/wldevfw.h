#ifndef WLDEVGW_H
#define WLDEVGW_H

#include <QTimer>
#include <QMutex>
#include <QString>
#include <QStringList>

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include "wlmotion.h"
#include "modules/wlmodulefw.h"

//#define PAGESIZE 2048

//#define sizeBlockFW 16

class WLDevFW: public WLMotion
{
	Q_OBJECT

public:	
	 WLDevFW();
	~WLDevFW();
	
bool init(QString portName);

protected:
virtual WLModule *createModule(QString name);
virtual WLModule *createModule(typeModule type);

public:
    WLModuleFW*    getModuleFW() {return static_cast<WLModuleFW*>(getModule(typeMFW));}
};

#endif //WLFWDEVICE_H
