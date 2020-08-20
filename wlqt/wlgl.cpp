#include "WLGL.h"


WLGL::WLGL()
{
showMatrix.setToIdentity();

showOffset=QVector4D(0,0,0,0);

Zoom=1;

TimerMovie = new QTimer;
connect(TimerMovie,SIGNAL(timeout()),SLOT(updateView()));
TimerMovie->setInterval(30);
}

WLGL::~WLGL()
{

}
void WLGL::initializeGL()
{
	 qglClearColor(Qt::black);

     glShadeModel(GL_SMOOTH);

	 glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glEnable(GL_NORMALIZE); 

     glEnable(GL_POLYGON_SMOOTH_HINT);
     glEnable(GL_POLYGON_SMOOTH);
     //glEnable(GL_LINE_SMOOTH);

     glClearColor(0.65,0.7,0.7,1);

     glCullFace(GL_BACK);

     GLfloat lightPosition0[4] = {0.0, 0.0, 10000, 1.0 };
     GLfloat lightPosition1[4] = {0.0, 0.0, 0, 1.0 };
	
     glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
     glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);

     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
	
     glEnable(GL_MULTISAMPLE);
}

void WLGL::movView(float Xd,float Yd,float Zd)
{
showOffset.setX(showOffset.x()+Xd);
showOffset.setY(showOffset.y()+Yd);
showOffset.setZ(showOffset.y()+Zd);
}

void WLGL::setPointRot(QVector4D pR)
{
pR.setW(0); //устанавливаем в ноль 

QVector4D P=showMatrix*pR;//находим наши коорд на экран

showOffset+=(showMatrix.column(3)+P)*Zoom;//двигаем экран на разницу

showMatrix.setColumn(3,QVector4D(-P.x(),-P.y(),-P.z(),1));//устанавливаем 

qDebug()<<"setRotPoint";
}

void WLGL::setRotView()
{
glTranslated(showOffset.x(),showOffset.y(),0);
glScalef(Zoom,Zoom,Zoom);

#if QT_VERSION >= 0x050000
  glMultMatrixf(showMatrix.data());
#else
  glMultMatrixd(showMatrix.data());
#endif
}

void WLGL::resizeGL(int w, int h)
{
vport[0]=0;
vport[1]=0;
vport[2]=w;
vport[3]=h;

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glOrtho((GLdouble)-w/2,(GLdouble)w/2,(GLdouble)-h/2,(GLdouble)h/2,(GLdouble)-5000,(GLdouble)5000);

glViewport(vport[0],vport[1],vport[2],vport[3]);
}

void WLGL::zoomView(QPoint MousePos,int delta)
{
QVector4D P0(MousePos.x()-vport[2]/2-showOffset.x()
	       ,-MousePos.y()+vport[3]/2-showOffset.y()
		   ,0
		   ,1); //Текущая позиция на экране

QVector4D P1=P0;  

QMatrix4x4 M=showMatrix;
M.scale(Zoom);
M.setColumn(3,QVector4D(0,0,0,1));//убераем смещение нам нужен только поворот

P0=M.inverted()*P0;   //узнаём позицию в ск отображения

//уменьшаем увеличение
Zoom-=(delta*Zoom/1000);
//P0 координата мыши в СК плоского окна новые
M=showMatrix;
M.scale(Zoom);
M.setColumn(3,QVector4D(0,0,0,1));//убераем смещение нам нужен только поворот

P0=M*P0; //Узнаём новую точку на экране после увелиечния

//смещаем
P1-=P0;

//qDebug()<<P1.x()<<P1.y()<<Zoom;

movView(P1.x(),P1.y());
}

void WLGL::resetView()
{
showMatrix.setToIdentity();
Zoom=1; 
}; 

void WLGL::resetRotView()
{
showMatrix.setColumn(0,QVector4D(1,0,0,0)); 
showMatrix.setColumn(1,QVector4D(0,1,0,0)); 
showMatrix.setColumn(2,QVector4D(0,0,1,0)); 
}; 


void WLGL::startMovie()
{
t=0;
TimerMovie->start();
}

void WLGL::updateView()
{
t+=0.1;

if(t>=1)
{
TimerMovie->stop(); t=1;
}
else
{
QQuaternion curQuant=QQuaternion::nlerp(startQuant,endQuant,t);

QMatrix4x4 M=startShowMatrix;

M.setColumn(3,QVector4D(0,0,0,1));

showMatrix=M.inverted()*startShowMatrix;//узнаём координаты смещения отн. базовой ск

M=getRotMatrix(0,0);
M.rotate(curQuant);

showMatrix=M*showMatrix;//поварачиваем на квантерион


if(t==3)
 {
 showMatrix=startShowMatrix;
 resetRotView();
 showMatrix.rotate(endQuant);
 }
}

updateGL();
}

void WLGL::setView(WLFrame Fr)
{
startQuant=MatrixToQuaternion(showMatrix);
startQuant.setScalar(-startQuant.scalar());

QMatrix4x4 M;

M=startShowMatrix=showMatrix;

M.setColumn(3,QVector4D(0,0,0,1));

endQuant=MatrixToQuaternion(Fr.toM()*M.inverted()*showMatrix);
endQuant.setScalar(-endQuant.scalar());


startMovie();

}
