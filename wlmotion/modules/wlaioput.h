#ifndef WLAIOPut_H
#define WLAIOPut_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QDebug>
#include <qstringlist.h>
#include "wlmodule.h"
#include "wlflags.h"


#define comAIOPut_setDataInput  128
#define comAIOPut_getDataInput  129

#define comAIOPut_setDataOutput 130
#define comAIOPut_getDataOutput 131


#define AIOPF_inv       1<<2
#define AIOPF_enable    1<<3
#define AIOPF_input     1<<4
#define AIOPF_asend     1<<5

#define AIOPF_invalid   1<<7


const QString errorAIOPut("0,no error\
,1,--\
,2,--");



class WLAIOPut: public WLElement
{        
Q_OBJECT

private:
 enum  typeDataAIOPut
     {
     dataAIOPut_hist=0,
     dataAIOPut_value,
     dataAIOPut_inv,
     dataAIOPut_flag,
     dataAIOPut_enable,
     };


public:

Q_PROPERTY(bool inv READ isInv() WRITE setInv() NOTIFY changedInv())

private:
         WLFlags Flags;

         float m_value;
         float m_histValue;
		 
public:
    WLAIOPut (QString _comment="",bool input=false);
	
void setInv(bool _inv=true);
void togInv()  {setInv(!isInv());}

float getHist() {return m_histValue;}
void setHist(float _hist) {if(_hist>0) m_histValue=_hist;}

bool isInv(void)      {return Flags.get(AIOPF_inv);}
bool isEnable()       {return Flags.get(AIOPF_enable);}
bool isInvalid(void)  {return Flags.get(AIOPF_invalid);}

QString toString() {
                   QString ret=QString::number(getIndex());
                   return ret;
                   }
void fromString(QString data) 
                    {
	                QStringList List=data.split(",");
					if(List.size()==1||List.size()==3)
                      {
                      setIndex(List[0].toInt());
                      }
                    }


void sendGetData();
void sendGetData(enum  typeDataAIOPut);

void setData(QDataStream&);

float value() {return  m_value;}
 void setValue(float _value);

bool isInput() {return  Flags.get(AIOPF_input);}

signals:
  void changedValue(float);
  void changedHistValue(float);
  void changedEnable(bool);

  void changedInv(bool);

  void changed(int);

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);

};

#endif //WLAIOPut_H
