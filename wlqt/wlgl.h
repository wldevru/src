#ifndef WLGL_H
#define WLGL_H

#include <QMatrix4x4>
#include <QVector4D>
#include <QTimer>
#include <QQuaternion>
#include <QDebug>
#include <QGLWidget>

#include <GL/gl.h>
#include <GL/glu.h>

#include "WLFrame.h"
#include "WLCalc.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


class WLGL : public QGLWidget
{
	Q_OBJECT

private:
	QTimer *TimerMovie;
	QQuaternion startQuant;
	QQuaternion   endQuant;
	QVector4D  startOffset;
	QVector4D    endOffset;
	
	float t;
	
	void startMovie();

private slots:
	void updateView();

public:
	WLGL();
	~WLGL();

    float getZoom() {return Zoom;}
	void  resetRotView();
	void  resetView();
	
protected:
    void initializeGL();
	void resizeGL(int w, int h);

//public:	
	

	void movView(float Xd,float Yd,float Zd=0);
    void rotView(float Xa,float Ya,float Za=0) {showMatrix=getRotMatrix(Xa,Ya,Za)*showMatrix;}

    void zoomView(QPoint MousePos,int delta);

	void setPointRot(QVector4D pR);

    void setRotView();

private:
	

	void setView(WLFrame Fr);
public:
   QMatrix4x4 showMatrix;
   QVector4D  showOffset;
   float      Zoom;

   GLint vport[4];

   QMatrix4x4 startShowMatrix;

public slots: 

    void setViewUp(void)     {setView(WLFrame(0,0,0,0,0,0));}
    void setViewDown(void)   {setView(WLFrame(0,0,0,0,0,180));}
    void setViewLeft(void)   {setView(WLFrame(0,0,0,180,0,90));}
    void setViewRight(void)  {setView(WLFrame(0,0,0,0,0,-90));}
    void setViewFront(void)  {setView(WLFrame(0,0,0,-90,-90,0));}
    void setViewRear(void)   {setView(WLFrame(0,0,0,90,90,0));}

virtual void setViewCenter(void) {
                                 showOffset.setX(0);
                                 showOffset.setY(0);
                                 updateGL();
                                 }


};

#endif // WLGL_H
