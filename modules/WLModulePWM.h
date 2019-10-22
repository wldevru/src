#ifndef WLModulePWM_H
#define WLModulePWM_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "WLDCan.h"
#include "WLModule.h"
#include "WLPWM.h"


class WLModulePWM : public WLModule
{
	Q_OBJECT

public:
	WLModulePWM(QObject *parent=0);
   ~WLModulePWM();

    bool Init(int _sizeOutPWM) {return  InitOut(_sizeOutPWM);};	
	bool InitOut(int _sizeOutPWM);	

private:
   QList <WLPWM*> outPWM;	
   QList <int> outputInvList;
public:
	int getSizeOutPWM() {return outPWM.size();}
	WLPWM* getOutPWM(int index) {if(index>=getSizeOutPWM()) index=0; return outPWM[index];}
public:

	/*
	bool setOutPWM(int index,float perpower);
    bool setInvOutPWM(int index,bool inv);
	bool setEnableOutPWM(int index,bool enable);
	bool setPmaxOutPWM(quint8 index,float Pmax);
	bool sendGetDataOutPWM(int i);
	bool setKOutPWM(int index,float k);
    bool setFOutPWM(int index,float f);
*/
/*
signals:
	void ChangedDataOutPWM(int index,float per);	
*/
public:

//virtual void callProp();
virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModulePWM_H

