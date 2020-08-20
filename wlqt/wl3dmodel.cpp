#include "wl3dmodel.h"

WL3DModel::WL3DModel()
{
setNameModel("noname");
}

WL3DModel::~WL3DModel()
{

}




bool loadSTL(QString fileName,QVector<STriangle> &Triangles)
{
QFile ProgFile(fileName);
STriangle Tr;
quint32 total_triangles=0;
quint16 atr=0;
bool ret;

Triangles.clear();

if(ProgFile.open(QIODevice::ReadOnly))
  {
  QDataStream DataStream(&ProgFile);
  DataStream.setFloatingPointPrecision(QDataStream::SinglePrecision);
  DataStream.setByteOrder(QDataStream::LittleEndian);
  //n=DataStream.readRawData(buf,80);
  //qDebug()<<"n="<<n;
  DataStream.skipRawData(80);

  DataStream>>total_triangles;
  qDebug()<<fileName<<"total triangles"<<total_triangles;
  while(total_triangles--&&!DataStream.atEnd())
   {
   DataStream>>Tr.Points[0];//normal
   Tr.Points[2]=Tr.Points[4]=Tr.Points[0];

   for(int i=1;i<6;i+=2)
    {
    DataStream>>Tr.Points[i];
    }

   DataStream>>atr;

   Triangles+=Tr;
   }
  ret=true;
  }
else
{
qDebug()<<"error openFile"<<fileName<<ProgFile.errorString();
ret=false;
}
qDebug()<<"Triangles load STL"<<Triangles.size();
return ret;
}
