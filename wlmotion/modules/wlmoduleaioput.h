#ifndef WLModuleAIOPut_H
#define WLModuleAIOPut_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "wlmodule.h"
#include "wlaioput.h"


class WLModuleAIOPut : public WLModule
{
	Q_OBJECT

public:
    WLModuleAIOPut(QObject *parent=nullptr);
   ~WLModuleAIOPut();

    bool Init(int _sizeInputs,int _sizeOutputs);
    bool InitInputs(int _sizeInputs);
    bool InitOutputs(int _sizeOutputs);

private:
   QList <WLAIOPut*> Inputs;
   QList <WLAIOPut*> Outputs;
      
public:	
    int getSizeInputs()  {return Inputs.size();}
    int getSizeOutputs() {return Outputs.size();}

    WLAIOPut *getInput(int index);
    WLAIOPut *getOutput(int index);

public slots:
virtual void update();
virtual void backup();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void readXMLData(QXmlStreamReader &stream);

virtual void readCommand(QByteArray data); 

signals:
  void changedInput(int);
  void changedOutput(int);


};

#endif // WLModuleFreq_H

