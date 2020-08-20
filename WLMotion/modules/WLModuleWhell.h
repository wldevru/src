#ifndef WLModuleWhell_H
#define WLModuleWhell_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "wlwhell.h"


//Whell


class WLModuleWhell : public WLModule
{
	Q_OBJECT

public:
	WLModuleWhell(QObject *parent=0);
	~WLModuleWhell();

	bool Init(int _sizeWhell);

	void setConfigWhell(int m_index,double mainDim);

private:
   QList <WLWhell*> Whell;	

public:

int getSizeWhell()  {return Whell.size();}
WLWhell *getWhell(int m_index);

public slots:
virtual void update();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModuleWhell_H

