#ifndef WLModuleMPG_H
#define WLModuleMPG_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "wlmpg.h"



//MPG
class WLModuleMPG : public WLModule
{
	Q_OBJECT

public:
    WLModuleMPG(QObject *parent=0);
    ~WLModuleMPG();

    bool Init(int _sizeMPG);

    void setConfigMPG(int m_index,double mainDim);

private:
   QList <WLMPG*> MPG;

public:

int getSize()  {return MPG.size();}
WLMPG *getMPG(int m_index);

public slots:
virtual void update();
virtual void backup();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModuleWhell_H

