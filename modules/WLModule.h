#ifndef WLMODULE_H
#define WLMODULE_H

#include <QObject>
#include <QTimer>
#include <QDataStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "WLElement.h"
#include "wlflags.h"

#define idAxis 0
#define idCut  10

#define idLine  100
#define idCirc  101
#define idBuff  102
#define idWhell 103

enum typeModule {typeDevice=0
                ,typeMAxis
                ,typeMWhell
                ,typeMPWM
                ,typeMFreq
                ,typeMIOPut
                ,typeMPlanner
                ,typeMCut
                ,typeMEncoder
                ,typeMConnect
                ,typeMFW
                ,typeMDCan
                ,typeMCKey};


#define comModule_getProp 255 //call property module
#define comModule_reset   254 //reset module

#define sendModule_error  255 //send error module
#define sendModule_prop   254 //send property

#define errorModule_index    254

#define startIndexErrorModule 230

const QString errorModule("0,no error\
,254,wrong index element\
,255,no modulet");

class WLModule : public WLElement
{
 Q_OBJECT

public:

	WLModule(QObject *parent=0);
  ~WLModule();

typeModule getTypeModule() {return typeM;};
      void setTypeModule(typeModule _type) {typeM=_type;}

private:
 typeModule typeM;

signals:
  void sendCommand(QByteArray data);
  void sendMessage(QString,QString,int); 

public slots:
virtual void reset();	
virtual void callProp();	

private slots:
 void setCommand(QByteArray data);

public:

virtual void  readCommand(QByteArray data)     {}
static QString getErrorStr(QString str,int);
};

#endif // WLMODULE_H
