#ifndef WLModulePWM_H
#define WLModulePWM_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include "wldcan.h"
#include "wlmodule.h"
#include "wlpwm.h"


class WLModulePWM : public WLModule
{
	Q_OBJECT

public:
    WLModulePWM(QObject *parent=nullptr);
   ~WLModulePWM();

    bool Init(int _sizeOutPWM);
	bool InitOut(int _sizeOutPWM);	

private:
   QList <WLPWM*> outPWM;	
   QList <int> outputInvList;
public:
	int getSizeOutPWM() {return outPWM.size();}
    WLPWM* getOutPWM(int m_index);
public:

public slots:
virtual void update();

private slots:
void updatePWM();

signals:
void changedOutPWM(int n);

public:

 virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModulePWM_H

