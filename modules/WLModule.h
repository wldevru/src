#ifndef WLMODULE_H
#define WLMODULE_H

#include <QObject>
#include <QTimer>
#include <QDataStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "WLElement.h"
#include "WLFlags.h"

#define idAxis 0
#define idCut  10

#define idLine  100
#define idCirc  101
#define idBuff  102
#define idWhell 103

enum typeModule {typeDevice=0
                ,typeMAxis//1
                ,typeMWhell//2
                ,typeMPWM//3
                ,typeMFreq//4
                ,typeMIOPut	 //5
                ,typeMPlanner//6
                ,typeMCut//7
                ,typeMEncoder//8
                ,typeMConnect//9
                ,typeMFW//10
                ,typeMDCan//11
                ,typeMCKey//12
                ,typeMAIOPut//13
                ,typeHeart=255
                };


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

    WLModule(QObject *parent=nullptr);
  ~WLModule();

typeModule getType() {return m_type;}
      void setType(typeModule _type) {m_type=_type;}

private:
 typeModule m_type;

public slots:
virtual void reset();	
virtual void callProp();	
virtual void update() {}

public slots:
 void setCommand(QByteArray data);

public:

virtual void  readCommand(QByteArray)     {}

static QString getErrorStr(QString str,int);
};

#endif // WLMODULE_H
