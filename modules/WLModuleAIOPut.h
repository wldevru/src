#ifndef WLModuleAIOPut_H
#define WLModuleAIOPut_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "WLModule.h"
#include "WLAIOPut.h"


class WLModuleAIOPut : public WLModule
{
	Q_OBJECT

public:
    WLModuleAIOPut(QObject *parent=nullptr);
   ~WLModuleAIOPut();

    bool Init(int _sizeInputs);

private:
   QList <WLAIOPut*> Inputs;
   
   
public:	
    int getSizeInputs() {return Inputs.size();}

    WLAIOPut *getInput(int index);

public slots:
virtual void update();

public:


virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void readXMLData(QXmlStreamReader &stream);

virtual void readCommand(QByteArray data); 
};

#endif // WLModuleFreq_H

