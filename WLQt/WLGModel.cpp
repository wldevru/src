#include "WLGModel.h"

WLGModel::WLGModel(QObject *parent) : QObject(parent)
{
axisX.name='X';
axisY.name='Y';
axisZ.name='Z';
axisA.name='A';
axisB.name='B';
axisC.name='C';

axisX.valueFrame.x=1;
axisY.valueFrame.y=1;
axisZ.valueFrame.z=1;


listAxis<<&axisX<<&axisY<<&axisZ;
}

WLFrame WLGModel::getFrame(WLGPoint GPoint)
{
QMutexLocker locker(&Mutex);

WLFrame ret;

QMatrix4x4 posM;
posM.setToIdentity();

axisX.value=GPoint.x;
axisY.value=GPoint.y;
axisZ.value=GPoint.z;
axisA.value=GPoint.a;
axisB.value=GPoint.b;
axisC.value=GPoint.c;

posM=offsetFrame.toM().inverted()*posM;

foreach(SAxisGModel *Axis,listAxis)
 {
 posM=Axis->getPosM(posM);
 }

ret.fromM(offsetFrame.toM()*posM);

return ret;
}

void WLGModel::writeXMLData(QXmlStreamWriter &stream)
{
QString str;

foreach(SAxisGModel *Axis,listAxis)
 {
 if(!str.isEmpty()) str+=",";
 str+=Axis->name;
 }

stream.writeAttribute("list",str);

stream.writeAttribute("axisX",axisX.toString());
stream.writeAttribute("axisY",axisY.toString());
stream.writeAttribute("axisZ",axisZ.toString());
stream.writeAttribute("axisA",axisA.toString());
stream.writeAttribute("axisB",axisB.toString());
stream.writeAttribute("axisC",axisC.toString());
}

void WLGModel::readXMLData(QXmlStreamReader &stream)
{
if(!stream.attributes().value("axisX").isEmpty()) axisX.fromString(stream.attributes().value("axisX").toString());
if(!stream.attributes().value("axisY").isEmpty()) axisY.fromString(stream.attributes().value("axisY").toString());
if(!stream.attributes().value("axisZ").isEmpty()) axisZ.fromString(stream.attributes().value("axisZ").toString());
if(!stream.attributes().value("axisA").isEmpty()) axisA.fromString(stream.attributes().value("axisA").toString());
if(!stream.attributes().value("axisB").isEmpty()) axisB.fromString(stream.attributes().value("axisB").toString());
if(!stream.attributes().value("axisC").isEmpty()) axisC.fromString(stream.attributes().value("axisC").toString());

if(!stream.attributes().value("list").isEmpty())
 {
 QStringList List=stream.attributes().value("list").toString().split(",");

 listAxis.clear();

 foreach(QString str,List)
  {
  str=str.toUpper();

  if(str[0]=='X') listAxis<<&axisX;
  else
      if(str[0]=='Y') listAxis<<&axisY;
      else
          if(str[0]=='Z') listAxis<<&axisZ;
          else
              if(str[0]=='A') listAxis<<&axisA;
              else
                  if(str[0]=='B') listAxis<<&axisB;
                  else
                      if(str[0]=='C') listAxis<<&axisC;

   }

  }


}

