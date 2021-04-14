#include "wlmilldrive.h"

WLMillDrive::WLMillDrive(QString _name,WLModuleAxis *_MAxis)
    : WLDrive(_name,_MAxis)
{
m_halfBacklash=0;
m_viewPosition=0;

setRealPosition(0);

autoTypeMDrive=autoNo;
//inicial();
}

WLMillDrive::~WLMillDrive()
{

}

double WLMillDrive::getRealPosition()
{
if(m_halfBacklash==0.0) return position();

if(rot())
	return position()-getHalfBacklash();
else
	return position()+getHalfBacklash();
}

double WLMillDrive::getViewPosition()
{
if(m_halfBacklash==0.0) return position();

double pos=position();

if(pos>m_viewPosition)
   if(m_viewPosition<(pos-m_halfBacklash)) m_viewPosition=pos-m_halfBacklash;
	
if(pos<m_viewPosition)
   if(m_viewPosition>(m_halfBacklash+pos)) m_viewPosition=pos+m_halfBacklash;

return m_viewPosition+getOffset();
}
  
int WLMillDrive::setRealPosition(double pos)
{
qDebug()<<getName()<<"setRealPosition "<<pos<<getAxisPosition()+getHalfBacklash()<<getAxisPosition()-getHalfBacklash();
//qDebug()<<(pos>(getAxisPosition()+getHalfBacklash()))<<((getAxisPosition()-getHalfBacklash())>pos);

if((pos-0.001f)>(getAxisPosition()+getHalfBacklash())
	 ||(getAxisPosition()-getHalfBacklash())>(pos+0.001f))	
  {
  sendMessage(getName(),("error real position"),-1);
  return 0;
  }
else
  {
  m_viewPosition=pos;
  return 1;
  }
}

int WLMillDrive::setAxisPosition(double pos)
{
return setPosition(pos);
}

int WLMillDrive::setMov(double d)//движение на заданное расстояние в размере
{
return setMot(getRealPosition()+d);
}

int WLMillDrive::setMot(double p)//движение в заданное положение в размере
{
double pos=getRealPosition();

qDebug()<<getName()<<"setMot MillDrive"<<p;

if(pos!=p)
{
if(pos<p)
    return WLDrive::setMot(p+getHalfBacklash());
  else
    return WLDrive::setMot(p-getHalfBacklash());
}

return 0;
}

	
void WLMillDrive::setBacklash(double bl)
{
if(bl>=0) 
 {
 m_halfBacklash=bl/2;
 }

};


int WLMillDrive::waitAfterMotion()         
{
getViewPosition();

return WLDrive::waitAfterMotion();
};



void WLMillDrive::writeXMLData(QXmlStreamWriter &stream)
{
stream.writeAttribute("Backlash",QString::number(getBacklash()));
WLDrive::writeXMLData(stream);
}

void WLMillDrive::readXMLData(QXmlStreamReader &stream)
{
WLDrive::readXMLData(stream);

setBacklash(stream.attributes().value("Backlash").toString().toFloat());
setRealPosition(getAxisPosition());
}

void WLMillDrive::updateAuto()
{
if(isAuto()&&(autoTypeMDrive !=autoNo))
 {
 updateMillDriveAuto();
 }
else
 {
 WLDrive::updateAuto();
 }
}


void WLMillDrive::updateMillDriveAuto()
{
qDebug()<<getName()<<"updateMillDriveAuto()"<<isPause();
if(isAutoDrive()&&!isPause())
switch(autoTypeMDrive)
 {
 case autoTouchSD:   
 case autoTouchEMG:  updateTouch();  break; 
}
}



int WLMillDrive::updateTouch()
{
qDebug()<<getName()<<"update touch"<<autoOperation;

if(autoTypeMDrive==autoTouchSD
 ||autoTypeMDrive==autoTouchEMG) 
{

switch(autoOperation)
               {
			   case 0:
               case 1: m_backPosition=position();
                       m_Pad.Load("main");
                       m_Pad.setSpeed(m_Ftouch/60);

					   if(autoTypeMDrive==autoTouchSD)
                         getAxis()->setActIn(AXIS_inORG,AXIS_actSdStop);
					   else
                         getAxis()->setActIn(AXIS_inORG,AXIS_actEmgStop);

                       setMot(autoOperation==1 ? maxPosition():minPosition());

					   autoOperation=3;
                       startMotion();
					   break;

               case 3: if(isLatch2()||isLatch3()) 
						  {
						  autoOperation=4;
						  //emgStop();  
                          qDebug()<<getName()<<"ch2/ch3"<<isLatch2()<<isLatch3();
					      }
					     else
						 if(!isMotion())
						     {
                             qDebug()<<getName()<<"no ch2/ch3";
                             reset();
                             emit sendMessage(getName(),tr("no sensor signal (inORG)"),-212);
							 }
  	            	   break; 
			   
               case 4: reset();
					   break; 
               }

}
return 1;
}



void  WLMillDrive::setMovTouch(int dir,float _Ftouch,bool sd)
{
QMutexLocker locker(&MutexDrive);
qDebug()<<getName()<<"setMovTouch";
if(setAuto())
   {
   autoOperation=dir; 
   m_Ftouch=_Ftouch;
   if(sd)
     autoTypeMDrive=autoTouchSD;
   else
	 autoTypeMDrive=autoTouchEMG;
   }
   else
    sendMessage(getName(),tr("movement setup error"),-10);
}


