#include "wldelayscript.h"

WLDelay::WLDelay(QObject *parent)
	: QThread(parent)
{
//reset();
	
for(int i=0;i<sizeTimers;i++)
  {
  m_count[i]=0;
  m_activ[i]=0;
  }

setTerminationEnabled();
/*
Timer=new QTimer;
connect(Timer,SIGNAL(timeout()),SLOT(timeEnd()));
Timer->start(50);*/

}

WLDelay::~WLDelay()
{

}

void WLDelay::run()
{
while(1)
{
msleep(50);
for(int i=0;i<sizeTimers;i++)
  {
  if(m_activ[i])  m_count[i]+=50;
  }
}
}
