#ifndef WLDCANM_H
#define WLDCANM_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include <QDebug>
#include <QStringList>
#include "WLModule.h"

#define comDCan_empty 0

#define comDCan_setOutputs 1
#define comDCan_setPWM     2  

#define comDCan_setAddress  10
#define comDCan_initInput  11
#define comDCan_initOutput 12
#define comDCan_setEnable  13
#define comDCan_addRemElement 14
#define comDCan_clearAllRemElement 15
#define comDCan_getData 16

#define comDCan_getInputsData      50

#define sendDCan_inputsData 100
//#define sendDCan_error 255

#define DCF_changeInput   1<<0
#define DCF_changeOutput  1<<1
#define DCF_enable        1<<2


#define defTimerTx 100
#define defTimerRx 150

#define error_sizecan    1
#define error_connectcan 2

const QString errorDCan("0,no error\
,1,size CAN\
,2,error connect");


struct WLRemElement
{
typeElement typeE;
quint8 indexLocal;   
quint8 indexRemote;  

WLRemElement() {indexLocal=indexRemote=0; typeE=typeEEmpty;}
/*
QString toString()
{
QStringList Names=namesTypeElement.split(",");
Names[typeE];
if(master)
 return  Names[typeE]+" "+QString::number(indexLocal)+"<<>>>"+;
}
                            */
void writeXMLData(QXmlStreamWriter &stream)
{
QStringList Names=namesTypeElement.split(",");

if(typeE<Names.size())
{
stream.writeStartElement(Names[typeE]);  
  stream.writeAttribute("ilocal",QString::number(indexLocal));
  stream.writeAttribute("iremote",QString::number(indexRemote));
stream.writeEndElement();
}

}

void readXMLData(QXmlStreamReader &stream)
{
QStringList Names=namesTypeElement.split(",");

for(int i=0;i<Names.size();i++)
	if(stream.name()==Names[i]) 
	 {
     typeE=static_cast<typeElement>(i);
	 break;
	 };

indexLocal   =stream.attributes().value("ilocal").toString().toInt();
indexRemote  =stream.attributes().value("iremote").toString().toInt();
}

};

class WLDCan : public WLElement
{
	Q_OBJECT

public:
	
 WLDCan(QObject *parent=0);
~WLDCan();

private:
 quint8  error;
 quint8  flag;
 quint16 adrCan;

 QList<WLRemElement> remEList;

public:
 quint16 getAdrCan() {return adrCan;}
    bool setAdrCan(quint16 _adrCan);

	
	void setError(quint8 _error) {emit ChangedError(error=_error);}

signals:

 void ChangedError(quint8);

public:

	bool addRemoteElement(WLRemElement remE);
	bool clearAllRemoteElement();
	bool setEnable(bool enable);

    bool sendGetData();


public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
};



#endif // WLDCAN_H
