#ifndef WLModuleWhell_H
#define WLModuleWhell_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "wlmpg.h"



//Whell
class WLModuleMPG : public WLModule
{
	Q_OBJECT

public:
    WLModuleMPG(QObject *parent=0);
    ~WLModuleMPG();

	bool Init(int _sizeWhell);

    void setConfigMPG(int m_index,double mainDim);

private:
   QList <WLMPG*> MPG;

public:

int getSize()  {return MPG.size();}
WLMPG *getMPG(int m_index);

public slots:
virtual void update();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModuleWhell_H

