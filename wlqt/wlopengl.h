#ifndef WLOPENGL_H
#define WLOPENGL_H

#include <QMatrix4x4>
#include <QVector4D>
#include <QTimer>
#include <QQuaternion>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "wlframe.h"
#include "wlcalc.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


class WLOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
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

    QColor clearColor;

private slots:
	void updateView();

public:
     WLOpenGL();
    ~WLOpenGL();

    float getZoom() {return Zoom;}
	void  resetRotView();
	void  resetView();


    QColor getClearColor() {return clearColor;}
    void   setGLClearColor() { glClearColor(clearColor.redF()
                                           ,clearColor.greenF()
                                           ,clearColor.blueF()
                                           ,1);}

public:
    virtual QMatrix4x4 getShowMatrix() {return showMatrix;}

protected:
    void initializeGL();
	void resizeGL(int w, int h);

//public:	
	

	void movView(float Xd,float Yd,float Zd=0);
    void rotView(float Xa,float Ya,float Za=0) {showMatrix=getRotMatrix(Xa,Ya,Za)*showMatrix;}

    void zoomView(QPoint MousePos,int delta);

	void setPointRot(QVector4D pR);

    void setRotView();

	
    virtual void initShaders() {}
    virtual void initGLBuffers(){}

private:
	void setView(WLFrame Fr);

private:

public:
   QMatrix4x4 showMatrix;
   QMatrix4x4 projection;
   QVector4D  showOffset;

   float      Zoom;

   GLint vport[4];

   QMatrix4x4 startShowMatrix;

public slots: 

    void setClearColor(QColor _color) {clearColor=_color;}

    void setViewUp(void)     {setView(WLFrame(0,0,0,0,0,0));}
    void setViewDown(void)   {setView(WLFrame(0,0,0,0,0,180));}
    void setViewLeft(void)   {setView(WLFrame(0,0,0,180,0,90));}
    void setViewRight(void)  {setView(WLFrame(0,0,0,0,0,-90));}
    void setViewFront(void)  {setView(WLFrame(0,0,0,-90,-90,0));}
    void setViewRear(void)   {setView(WLFrame(0,0,0,90,90,0));}    

virtual void setViewCenter(void) {
                                 showOffset.setX(0);
                                 showOffset.setY(0);
                                 update();
                                 }


};

#endif // WLOPENGL_H
