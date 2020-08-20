#ifndef WLMILLDRIVE_H
#define WLMILLDRIVE_H

#include "wldrive.h"

class WLMillDrive : public WLDrive
{
	Q_OBJECT

private:
 enum autoMDrive 
          {
	      autoNo,
		  autoTouchSD,
		  autoTouchEMG
          };
public:
    WLMillDrive(QString name="");
	~WLMillDrive();

double getViewPosition();

double getRealPosition();
  int setRealPosition(double pos);

  int setAxisPosition(double pos);
inline double getAxisPosition() {return position();}

  void setBacklash(double bl);

inline double getBacklash()      {return m_halfBacklash*2;}
inline double getHalfBacklash()  {return m_halfBacklash;}

virtual int setMov(double d);//движение на заданное расстояние в размере
virtual int setMot(double p);//движение в заданное положение в размере

virtual void writeXMLData(QXmlStreamWriter &stream);
virtual void  readXMLData(QXmlStreamReader &stream);

void setInputs(WLIOPut *PEL,WLIOPut *MEL,WLIOPut *ORG);

public:
  void setMovTouch(int dir,float F,bool sd=false);


protected:
 virtual int waitAfterMotion();
 virtual int updateAuto();

private:
 int updateTouch();

private slots:
 void updateMillDriveAuto();

private:


 float m_Ftouch;

 int autoTypeMDrive;
 //int autoOperation;

 double m_backPosition;
 /*
WLIOPut *inLATCH;
WLIOPut *inPEL;
WLIOPut *inMEL;
WLIOPut *inRDY;
*/
private:

 double m_viewPosition;
 double m_halfBacklash;
};

#endif // WLMILLDRIVE_H
