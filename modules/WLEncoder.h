#ifndef WLENCODER_H
#define WLENCODER_H

#include <QObject>
#include <QDataStream>
#include <QTimer>
#include <QDebug>

#include "WLModule.h"


//Encoder
#define comEnc_setSendChgData 1 //set autosend data
#define comEnc_setEnable      2 //set enable encoder
#define comEnc_setScale       3 //set scale count
#define comEnc_setPos         4 //set cur position

#define comEnc_getData  100 //call data encoder

#define sendEnc_data 200 //send data encoder

#define ENCF_enable  1<<0
#define ENCF_sendChg 1<<1

const QString errorEncoder("0,no error\
,1,-");

class WLEncoder : public WLElement
{
	Q_OBJECT

public:
	
 WLEncoder(QObject *parent=0);
~WLEncoder();

private:

    long posNow;
 quint16 scale;

 quint8 error;
 quint8 flag;

public:
   void setData(long pos) {posNow=pos;};  

   void setError(quint8 err)  {emit changedError(error=err);}

signals:
 
 void changedError(quint8);
 void changedCnt(long);

public:

	bool setPos(long cnt);	
    bool setEnable(bool enable);
	bool setScale(quint16 _scale);	

	bool sendGetData();

public:

//virtual void writeXMLData(QXmlStreamWriter &stream);
//virtual void  readXMLData(QXmlStreamReader &stream);
};



#endif // WLENCODER_H
