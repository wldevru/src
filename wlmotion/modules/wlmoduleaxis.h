#ifndef WLMODULEAXIS_H
#define WLMODULEAXIS_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include "wlaxis.h"
#include "wlmodule.h"
#include "wlmoduleioput.h"

enum typeInputMAXIS{MAXIS_inEMGStop,MAXIS_inSDStop,MAXIS_inProbe};

class WLModuleAxis : public WLModule
{
	Q_OBJECT

public:
	enum FlagMAxis{
	              MAF_latchProbe2=1<<0,
				  MAF_latchProbe3=1<<1
	              };

public:
	 WLModuleAxis(WLModuleIOPut *_ModuleIOPut,QObject *parent=0);
	~WLModuleAxis();


bool isLatchProbe2() {return Flags.get(MAF_latchProbe2);}
bool isLatchProbe3() {return Flags.get(MAF_latchProbe3);}

void resetLatchProbe() {Flags.set(MAF_latchProbe2|MAF_latchProbe2,false);}

void resetAllAxis() {for(int i=0;i<Axis.size();i++) Axis[i]->reset();}

bool Init(int size);

WLModuleIOPut *getModuleIOPut() {return  ModuleIOPut;}

WLAxis *getAxis(int m_index);

private:
	WLModuleIOPut *ModuleIOPut;
	QList <WLAxis*> Axis;	

//private:
   WLIOPut *inEMGStop;
   WLIOPut *inSDStop;
   WLIOPut *inProbe;
   
public:
WLIOPut *getInput(typeInputMAXIS type);

void setInEMGStop(int m_index);
void setInSDStop(int m_index);
void setInProbe(int m_index);

 int getSizeAxis() {return Axis.size();}

private:
	QTimer *updateTimer;

	QList <long> posLatchProbe2;
	QList <long> posLatchProbe3;

	WLFlags Flags;

    float Fmax;
public:
    Q_INVOKABLE	 float getFmax()   {return Fmax;}
	Q_INVOKABLE double getLatchProbe2(int index) {if(index>=getSizeAxis()) index=0;  return posLatchProbe2[index];}
	Q_INVOKABLE double getLatchProbe3(int index) {if(index>=getSizeAxis()) index=0;  return posLatchProbe3[index];}

private slots:
	void setLatchProbe2(qint32 *Pos,quint8);
	void setLatchProbe3(qint32 *Pos,quint8);
	void callDataAxis();
    void callPosAxis();

public slots:
virtual void update();
virtual void backup();

public:
    bool setInputMAxis(typeIOPutAXIS type,quint8 num);
    bool setActInProbe(typeActIOPutAxis typeAct);

signals:
    void changedInEMGStop();
    void changedInSDStop();
	

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void  readCommand(QByteArray data);  
};

#endif // WLMODULEAXIS_H
