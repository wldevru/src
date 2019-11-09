#ifndef WLModuleDCAN_H
#define WLModuleDCAN_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "WLModule.h"
#include "WLDCan.h"


class WLModuleDCan : public WLModule
{
	Q_OBJECT

public:
	WLModuleDCan(QObject *parent=0);
   ~WLModuleDCan();

	bool Init(int sizeDCAN);	
	
private:
   QList <WLDCan*> DCan;	   

public:
	
	int getSizeDCan() {return DCan.size();}

	WLDCan* getDCan(int index) {if(index>=getSizeDCan()) index=0; return DCan[index];}

public slots:
virtual void update();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModuleDCAN_H

