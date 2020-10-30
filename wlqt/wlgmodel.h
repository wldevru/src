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
WLFrame  ofstFrame;
WLFrame   dirFrame;
  double       value;
          QChar name;

SAxisGModel() {value=0;name='?';}

QString toString()
{
return ofstFrame.toString()+";"+dirFrame.toString();
}

bool fromString(QString str)
{
bool ret = false;
QStringList List=str.split(";");

if(List.size()==2)
 {
 if(ofstFrame.fromString(List[0])
   &&dirFrame.fromString(List[1])) ret=true;
 }
return ret;
}

inline QMatrix4x4 getPosM(QMatrix4x4 posM)
{
return ((dirFrame*value).toM()*ofstFrame.toM()*posM);
}

};

struct WLGModelData
{
QString strAxis;

WLFrame offsetFrame;

SAxisGModel axisX;
SAxisGModel axisY;
SAxisGModel axisZ;
SAxisGModel axisA;
SAxisGModel axisB;
SAxisGModel axisC;

WLGModelData()
  {
  axisX.name='X';
  axisY.name='Y';
  axisZ.name='Z';
  axisA.name='A';
  axisB.name='B';
  axisC.name='C';

  axisX.dirFrame.x=1;
  axisY.dirFrame.y=1;
  axisZ.dirFrame.z=1;

  strAxis="X,Y,Z";
  }
};

class  WLGModel : public QObject
{
    Q_OBJECT

public:
    explicit WLGModel(QObject *parent = nullptr);

    WLFrame getFrame(WLGPoint GPoint);
   WLGPoint getGPoint(WLFrame Frame);

 void writeXMLData(QXmlStreamWriter &stream);
 void  readXMLData(QXmlStreamReader &stream);

 WLGModelData getData();

private:
  QMutex Mutex;
  WLGModelData m_data;

public:
     void setStrAxis(QString str);
  QString getStrAxis();

  void setOffsetFrame(WLFrame ofst) {m_data.offsetFrame=ofst;}

  SAxisGModel getX() {return m_data.axisX;}
  SAxisGModel getY() {return m_data.axisY;}
  SAxisGModel getZ() {return m_data.axisZ;}
  SAxisGModel getA() {return m_data.axisA;}
  SAxisGModel getB() {return m_data.axisB;}
  SAxisGModel getC() {return m_data.axisC;}

  void setX(SAxisGModel sd) {m_data.axisX=sd;}
  void setY(SAxisGModel sd) {m_data.axisY=sd;}
  void setZ(SAxisGModel sd) {m_data.axisZ=sd;}
  void setA(SAxisGModel sd) {m_data.axisA=sd;}
  void setB(SAxisGModel sd) {m_data.axisB=sd;}
  void setC(SAxisGModel sd) {m_data.axisC=sd;}

signals:

public slots:  
   void setData(WLGModelData data);
};

#endif // WLGMODEL_H
