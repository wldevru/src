#include "wlmodulepwm.h"

WLModulePWM::WLModulePWM(QObject *parent)
	: WLModule(parent)
{
setType(typeMPWM);

Init(1);

QTimer *updateTimer = new QTimer;
connect(updateTimer,SIGNAL(timeout()),SLOT(update()));
updateTimer->start(100);


}

WLModulePWM::~WLModulePWM()
{
while(outPWM.isEmpty())
          delete outPWM.takeLast();
}

bool WLModulePWM::Init(int _sizeOutPWM)
{
if(InitOut(_sizeOutPWM))
{
update();
return true;
}
else
 return false;
}

bool WLModulePWM::InitOut(int sizeOutPWM)
{
if(sizeOutPWM<1||outPWM.size()== sizeOutPWM) return false;

WLPWM *pwm;

if(sizeOutPWM>outPWM.size())
 for(int i=outPWM.size();i<sizeOutPWM;i++ )
  {
  pwm = new WLPWM;
  pwm->setIndex(i);
  pwm->setParent(this);
  connect(pwm,SIGNAL(sendCommand(QByteArray)),SLOT(setCommand(QByteArray)));
  connect(pwm,SIGNAL(changed()),SLOT(updatePWM()));
  outPWM+=pwm;
  }
else
	while(outPWM.size()!= sizeOutPWM) 
	  {	  
	  pwm=outPWM.takeLast();
	  disconnect(pwm,SIGNAL(sendCommand(QByteArray)),this,SLOT(setCommand(QByteArray)));
      disconnect(pwm,SIGNAL(changed()),this,SLOT(updatePWM()));
	  delete pwm;  
      }


return true;
}

WLPWM *WLModulePWM::getOutPWM(int index)
{
Q_ASSERT(((index<getSizeOutPWM()))&&(index<255));

return index<getSizeOutPWM() ? outPWM[index]: nullptr;
}

void WLModulePWM::update()
{
foreach(WLPWM *pwm,outPWM)
  {
  pwm->sendGetData();
}
}

void WLModulePWM::updatePWM()
{
WLPWM *PWM=static_cast<WLPWM*>(sender());

emit changedOutPWM(PWM->getIndex());
}

void  WLModulePWM::readCommand(QByteArray Data)
{
quint8 index,ui1;

float f1,f2;

QDataStream Stream(&Data,QIODevice::ReadOnly);

Stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
Stream.setByteOrder(QDataStream::LittleEndian);

Stream>>ui1;

switch(ui1)
{

case comPWM_setValue:Stream>>index;//index8
                     if(index<getSizeOutPWM())
                      {
                      outPWM[index]->setData(Stream);
                      }

                     break;

case sendPWM_dataOut:Stream>>index;//index8
   	                 Stream>>ui1;//flag
					 Stream>>f1;
					 Stream>>f2;
                      //   qDebug()<<"ChangedDataOutPWM"<<index<<f1;
					 if(index<getSizeOutPWM()) outPWM[index]->setData(ui1,f1,f2);	
					 break;

case  sendModule_prop: Stream>>ui1;
					                      
					   Init(ui1);
                       break;

case  sendModule_error:
	                Stream>>ui1;//index8
                    Stream>>index;  //Error

                    if(ui1>startIndexErrorModule)
					 {
                     emit sendMessage("WLModulePWM "+getErrorStr(errorModule,ui1),QString::number(index),(int)(ui1));	
					 }
					else
					   if(index<getSizeOutPWM())   
						   {
						   outPWM[index]->setError(ui1);       									  
						   emit sendMessage("WLPWM "+getErrorStr(errorPWM,ui1),QString::number(index),(int)(ui1));	
					       }
                    break;
}

}

void WLModulePWM::readXMLData(QXmlStreamReader &stream)
{	
quint8 index;

int size=2;

while(!stream.atEnd())
{
stream.readNextStartElement();

if(stream.name()==metaObject()->className()) break;
if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

if(stream.name()=="outputs")
  {
  size=2;
  if(!stream.attributes().value("size").isEmpty()) size=stream.attributes().value("size").toString().toInt();    

  InitOut(size);

  while(!stream.atEnd())
   {
   stream.readNextStartElement();
   
   if(stream.name()=="outputs") break;
   if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

   if(stream.name()=="PWM")
	   {
	   index=stream.attributes().value("index").toString().toInt();
	   if(index<getSizeOutPWM())	
		   outPWM[index]->readXMLData(stream);		    	    	   
      }

   }
  }
}

}
void WLModulePWM::writeXMLData(QXmlStreamWriter &stream)
{

stream.writeStartElement("outputs");
stream.writeAttribute("size",QString::number(getSizeOutPWM()));

for(int i=0;i<getSizeOutPWM();i++)
 {
 stream.writeStartElement("PWM");
 stream.writeAttribute("index",QString::number(i));
   outPWM[i]->writeXMLData(stream);
 stream.writeEndElement();
 }

stream.writeEndElement();

}

