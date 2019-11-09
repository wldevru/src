#ifndef WLModuleEncoder_H
#define WLModuleEncoder_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "WLModule.h"
#include "WLEncoder.h"

//Encoder
#define comEnc_setASendData   1 //set autosend data
#define comEnc_setEnable      2 //set enable encoder
#define comEnc_setScale       3 //set scale count
#define comEnc_setPos         4 //set cur position

#define comEnc_getData  100 //call data encoder

#define sendEnc_data 200 //send data encoder

#define ENCF_enable  1<<0
#define ENCF_asend   1<<1


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


public slots:
virtual void update();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);

virtual void readCommand(QByteArray data); 
};

#endif // WLModuleEncoder_H

