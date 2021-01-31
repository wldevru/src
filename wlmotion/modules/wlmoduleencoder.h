#ifndef WLModuleEncoder_H
#define WLModuleEncoder_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "wlmodule.h"
#include "wlencoder.h"

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
    WLEncoder* getEncoder(int m_index);


private slots:
void  updateEncoder();

public slots:
virtual void update();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);

virtual void readCommand(QByteArray data); 


signals:
  void changedEncoder(int);
};

#endif // WLModuleEncoder_H

