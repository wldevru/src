#ifndef WLGMODEL_H
#define WLGMODEL_H

#include <QObject>
#include <QList>
#include <QMutexLocker>
#include <QMutex>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "wl3dpoint.h"
#include "wlframe.h"
#include "wlgcode.h"


struct SAxisGModel  //linear mov x, rotary rot a
{
WLFrame  offsetFrame;
WLFrame   valueFrame;
 double        value;
          QChar name;

SAxisGModel() {}

QString toString()
{
return offsetFrame.toString()+";"+valueFrame.toString();
}

bool fromString(QString str)
{
bool ret = false;
QStringList List=str.split(";");

if(List.size()==2)
 {
 if(offsetFrame.fromString(List[0])
   &&valueFrame.fromString(List[1])) ret=true;
 }

return ret;
}

inline QMatrix4x4 getPosM(QMatrix4x4 posM)
{
return ((valueFrame*value).toM()*offsetFrame.toM()*posM);
}

};

class  WLGModel : public QObject
{
    Q_OBJECT

public:
    explicit WLGModel(QObject *parent = nullptr);

    WLFrame getFrame(WLGPoint GPoint);


 void writeXMLData(QXmlStreamWriter &stream);
 void  readXMLData(QXmlStreamReader &stream);

private:
  QMutex Mutex;
public:

  QList <SAxisGModel*> listAxis;

  WLFrame offsetFrame;

  SAxisGModel axisX;
  SAxisGModel axisY;
  SAxisGModel axisZ;
  SAxisGModel axisA;
  SAxisGModel axisB;
  SAxisGModel axisC;

signals:

public slots:
};

#endif // WLGMODEL_H
