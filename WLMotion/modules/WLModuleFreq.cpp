#include "wlmodulefreq.h"

WLModuleFreq::WLModuleFreq(QObject *parent)
	: WLModule(parent)
{
setType(typeMFreq);
Init(1);
}

WLModuleFreq::~WLModuleFreq()
{
while(outFreq.isEmpty())
       delete outFreq.takeLast();
}

bool WLModuleFreq::Init(int sizeOutFreq)
{
if(sizeOutFreq<1||outFreq.size()== sizeOutFreq) return false;

WLFreq *freq;

if(sizeOutFreq>outFreq.size())
 for(int i=outFreq.size();i<sizeOutFreq;i++ )
  {
  freq = new WLFreq;
  freq->setIndex(i);
  freq->setParent(this);
  connect(freq,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  outFreq+=freq;
  }
else
	while(outFreq.size()!= sizeOutFreq) 
	  {	  
	  freq=outFreq.takeLast();
	  disconnect(freq,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
	  delete freq;  
      }

return true;
}

WLFreq *WLModuleFreq::getOutFreq(int index)
{
Q_ASSERT((index<getSizeOutFreq())&&(index<255));

return index<getSizeOutFreq() ? outFreq[index]:nullptr;
}

void WLModuleFreq::update()
{
    foreach(WLFreq *freq,outFreq)
        freq->sendGetData();
}

void  WLModuleFreq::readCommand(QByteArray Data)
{
quint8 index,ui1;
float f1;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
{
case sendFreq_dataOut: Stream>>index;//index8
   	                   Stream>>f1;
					   if(index<getSizeOutFreq()) outFreq[index]->setData(f1);
					  // qDebug()<<"ChangedDataOutFreq"<<index<<f1;
   				       //emit ChangedDataOutFreq(index,f1);				      
   			           break;

case  sendModule_prop: Stream>>ui1;
					                      
					   Init(ui1);
                       break;

case  sendModule_error:Stream>>ui1;
                       Stream>>index;  

					   if(ui1>200)
					    {
						emit sendMessage("WLModuleFreq "+getErrorStr(errorModule,ui1),QString::number(index),(int)(ui1));	
					    }
					    else
				        if(index<getSizeOutFreq())   
							{
							outFreq[index]->setError(ui1);       									  
							emit sendMessage("WLFreq "+getErrorStr(errorFreq,ui1),QString::number(index),(int)(ui1));	
						    }
                       break;
}

}
/*
bool WLModulePWM::setOutPWM(int index,float perpower)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)typeMPWM<<(quint8)_setOutPWM<<(quint8)index<<perpower;

qDebug()<<"send setOutPWM"<<data.size();

emit sendCommand(data);
return true;
}

bool WLModulePWM::setInvOutPWM(int index,bool inv)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)typeMPWM<<(quint8)_setInvOutPWM<<(quint8)index<<(quint8)inv;

qDebug()<<"send setInvOutPWM"<<data.size();

emit sendCommand(data);
return true;
}

bool WLModulePWM::setEnableOutPWM(int index,bool enable)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)typeMPWM<<(quint8)_setEnableOutPWM<<(quint8)index<<enable;

qDebug()<<"send setOutPWMEn"<<enable<<data.size();

emit sendCommand(data);
return true;
}

bool WLModulePWM::setPmaxOutPWM(quint8 index,float Pmax)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<"setFmaxOutPWM"<<index<<Pmax;

Stream<<(quint8)typeMPWM<<(quint8)_setPmaxOutPWM<<(quint8)index<<Pmax;

emit sendCommand(data);
return true;
}

bool WLModulePWM::sendGetDataOutPWM(int i)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream<<(quint8)typeMPWM<<(quint8)_getDataOutPWM<<(quint8)i;

//qDebug()<<"sendGetPWMData"<< i;
emit sendCommand(data);
return true;
}	

bool WLModulePWM::setKOutPWM(int index,float k)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)typeMPWM<<(quint8)_setKOutPWM<<(quint8)index<<k;

qDebug()<<"setKOutPWM"<<index<<data.size();

emit sendCommand(data);
return true;
}

bool WLModulePWM::setFOutPWM(int index,float f)
{
QByteArray data;
QDataStream Stream(&data,QIODevice::WriteOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

qDebug()<<data.size();

Stream<<(quint8)typeMPWM<<(quint8)_setFOutPWM<<(quint8)index<<f;

qDebug()<<"setFOutPWM"<<index<<data.size();

emit sendCommand(data);
return true;
}*/
/*
void WLModulePWM::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeStartElement("outpwm");
for(int i=0;i<sizeOutPWM;i++)
 {
 stream.writeStartElement(QString::number(i));
   stream.writeAttribute("Freq",QString::number(outPWM[i].getFreq()));   
 stream.writeEndElement();
 }
stream.writeEndElement();
}

void WLModulePWM::readXMLData(QXmlStreamReader &stream)
{
int index;
QStringList list;

 stream.readNextStartElement();

 if(stream.name()=="outpwm"
  &&stream.tokenType()==QXmlStreamReader::StartElement)
	   {
	   while(!stream.atEnd())
	    {
        stream.readNextStartElement();
		
		if(stream.name()=="outpwm") break;
		if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

		index=stream.name().toString().toInt();
		if(index<sizeOutPWM)
		    {
			if(!stream.attributes().value("Freq").isEmpty()) 	
				{				
				outPWM[index].setFOutPWM(stream.attributes().value("Freq").toString().toFloat());				
			    }
		    }
	    }
	   }
}
*/
