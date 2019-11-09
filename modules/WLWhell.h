#ifndef WLFREQ_H
#define WLFREQ_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include <QDebug>

#include "WLModule.h"
#include "WLEncoder.h"
#include "WLFlags.h"

#define comWhell_setEnable     1 
#define comWhell_setKTrack     2 
#define comWhell_setTypeTrack  3
#define comWhell_setAxis       4 

#define comWhell_setIInAxisTrack 5 
#define comWhell_setIInKTrack    6
#define comWhell_setIInTypeTrack 7
#define comWhell_setKTrackData   8
#define comWhell_setUseInput     9

#define comWhell_setEncoder     10

#define comWhell_getData 11

#define sendWhell_data 1

#define WHF_enable    1<<0
#define WHF_vtype     1<<1
#define WHF_useinput  1<<2

const QString errorWhell("0,no error\
,1,set data\
,2,wrong enable");

#define errorWhell_setdata 1
#define errorWhell_enable  2

class WLWhell : public WLElement
{
	Q_OBJECT

public:
	
 WLWhell(QObject *parent=0);
~WLWhell(); 

private:

 quint8 error;
 WLFlags Flags;

 quint8 iEncoder;

public:

   void setError(quint8 err)  {emit ChangedError(error=err);}

   
    quint8 getEncoder() {return iEncoder;};

    quint8 getFlag() {return Flags.m_Data;}

signals:
 
 void ChangedError(quint8);

public:

	bool setEncoder(quint8 _iEncoder);

	bool setAxis(int iAxis);
    bool setKTrack(float k);
    bool setEnable(bool enable);
    bool setTypeTrack(quint8 type);    
    bool setUseInput(bool enable);
    bool setKTrackData(float K8[],double mainDim);

	bool sendGetData();

public:

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);
};



#endif // WLFREQ_H
