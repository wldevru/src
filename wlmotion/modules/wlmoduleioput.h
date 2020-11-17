#ifndef WLModuleIOPut_H
#define WLModuleIOPut_H

#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QDebug>
#include <qstringlist.h>
#include "wlmodule.h"
#include "wlioput.h"
#include "wldcan.h"



class WLModuleIOPut: public WLModule
{        
Q_OBJECT
	
public:
    WLModuleIOPut(QObject *parent=nullptr);
   ~WLModuleIOPut();
   
public:

bool Init(int _sizeInputs,int _sizeOutputs);
bool InitInputs(int _sizeInputs);
bool InitOutputs(int _sizeOutputs);

WLIOPut* getInput(int m_index);
WLIOPut* getOutput(int m_index);

void setInputInvStr(QString data);
QString getInputInvStr();

   void setOutputInvStr(QString data);
QString getOutputInvStr();

private:
QList <WLIOPut*> Inputs;
QList <WLIOPut*> Outputs;
	
public:

int getSizeInputs()  {return Inputs.size();}
int getSizeOutputs() {return Outputs.size();}	

Q_INVOKABLE   bool input(int index) {return getInput(index)->getNow();}
Q_INVOKABLE   quint8 byte(int in7,int in6,int in5,int in4,int in3,int in2,int in1,int in0)
                              {return (input(in7)? 1<<7:0)
								     |(input(in6)? 1<<6:0)
								     |(input(in5)? 1<<5:0)
								     |(input(in4)? 1<<4:0)
								     |(input(in3)? 1<<3:0)
								     |(input(in2)? 1<<2:0)
								     |(input(in1)? 1<<1:0)
								     |(input(in0)? 1<<0:0);}


Q_INVOKABLE void otputPulse(int index, bool out,quint32 time) {getOutput(index)->setOutPulse(out,time);}
Q_INVOKABLE bool output(int index)   {return getOutput(index)->getNow();}

public slots:

    void outputSetTo(int index, bool out) {getOutput(index)->setOut(out);}
    void outputSet(int index)   {outputSetTo(index,1);}
    void outputReset(int index) {outputSetTo(index,0);}
    void outputTog(int index)   {getOutput(index)->setTog();}

    void setBasicOutputsInv();

public:
    void callInputData(quint8 m_index);
    void callOutputData(quint8 m_index);

private:
	void sendGetIOSize();	

private slots:
    void updateAllInputData();
    void updateAllOutputData();

	void sendSetOData(bool all=true);

    void updateIOPut();

public slots:
virtual void update();


signals:

  void changedInput(int);
  void changedOutput(int);

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 

};

#endif //WLModuleIOPut_H
