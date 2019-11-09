#ifndef WLModuleWhell_H
#define WLModuleWhell_H

#include <QObject>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include "WLWhell.h"


//Whell
#define comWhell_setEnable     1 //enable whell
#define comWhell_setKTrack     2 //set K track axis
#define comWhell_setTypeTrack  3 //set type track axis (vel/pos)
#define comWhell_setAxis       4 //set track axis

#define comWhell_setEncoder     10 //set encoder

#define errorWhell_setdata 1
#define errorWhell_enable  2

#define WHF_enable    1<<0
#define WHF_vtype     1<<1
#define WHF_useinput  1<<2
#define WHF_opinaxis  1<<3
#define WHF_opink     1<<4

class WLModuleWhell : public WLModule
{
	Q_OBJECT

public:
	WLModuleWhell(QObject *parent=0);
	~WLModuleWhell();

	bool Init(int _sizeWhell);

	void setConfigWhell(int index,double mainDim);

private:
   QList <WLWhell*> Whell;	

public:

int getSizeWhell()  {return Whell.size();}
WLWhell *getWhell(int index) {if(index>=getSizeWhell()) index=0; return  Whell[index]; }

public slots:
virtual void update();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
virtual void readCommand(QByteArray data); 
};

#endif // WLModuleWhell_H

