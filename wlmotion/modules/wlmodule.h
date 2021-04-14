#ifndef WLMODULE_H
#define WLMODULE_H

#include <QObject>
#include <QTimer>
#include <QDataStream>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "wlelement.h"
#include "wlflags.h"

#define idAxis 0
#define idCut  10

#define idLine  100
#define idCirc  101
#define idBuff  102
#define idWhell 103

enum typeModule {typeDevice=0
                ,typeMAxis//1
                ,typeMMPG//2
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

typeModule type() {return m_type;}
      void setType(typeModule _type) {m_type=_type;}
      bool isReady() {return m_ready;}
private:
 typeModule m_type;
       bool m_ready;

public slots:

virtual void reset();	
virtual void callProp();	

virtual void setReady(bool);

public slots:
 void setCommand(QByteArray data);

public:
virtual void  readCommand(QByteArray)     {}

static QString getErrorStr(QString str,int);

signals:
  void changedReady(bool);
};

#endif // WLMODULE_H
