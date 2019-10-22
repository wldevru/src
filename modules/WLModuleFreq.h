#ifndef WLModuleFreq_H
#define WLModuleFreq_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "WLModule.h"
#include "WLFreq.h"


class WLModuleFreq : public WLModule
{
	Q_OBJECT

public:
	WLModuleFreq(QObject *parent=0);
   ~WLModuleFreq();

	bool Init(int _sizeOutFreq);	

private:
   QList <WLFreq*> outFreq;	
   
   
public:	
	int getSizeOutFreq() {return outFreq.size();}
	WLFreq* getOutFreq(int index) {if(index>=getSizeOutFreq()) index=0; return outFreq[index];}

public:


public:

//virtual void callProp();
//virtual void writeXMLData(QXmlStreamWriter &stream);
//virtual void  readXMLData(QXmlStreamReader &stream);

virtual void readCommand(QByteArray data); 
};

#endif // WLModuleFreq_H

