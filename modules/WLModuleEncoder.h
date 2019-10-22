#ifndef WLModuleEncoder_H
#define WLModuleEncoder_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "WLModule.h"
#include "WLEncoder.h"

#define comEnc_setSendChgData 1
#define comEnc_setEnable      2
#define comEnc_setScale       3
#define comEnc_setPos         4

#define comEnc_getData  100

#define sendEnc_data 200


class WLModuleEncoder : public WLModule
{
	Q_OBJECT

public:
	WLModuleEncoder(QObject *parent=0);
   ~WLModuleEncoder();

	bool Init(int _sizeOutEncoder);	

private:
   QList <WLEncoder*> Encoder;	   
   
public:	
	int getSizeEncoder() {return Encoder.size();}
	WLEncoder* getEncoder(int index) {if(index>=getSizeEncoder()) index=0; return Encoder[index];}

public:


public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);

virtual void readCommand(QByteArray data); 
};

#endif // WLModuleEncoder_H

