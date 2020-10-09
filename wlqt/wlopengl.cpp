#include "wlopengl.h"


WLOpenGL::WLOpenGL()
{
showMatrix.setToIdentity();

showOffset=QVector4D(0,0,0,0);

Zoom=1;

TimerMovie = new QTimer;
connect(TimerMovie,SIGNAL(timeout()),SLOT(updateView()));
TimerMovie->setInterval(30);

setClearColor(QColor(150,150,150));
}

WLOpenGL::~WLOpenGL()
{

}
void WLOpenGL::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(clearColor.redF(),clearColor.greenF(),clearColor.blueF(),1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initGLBuffers();
}

void WLOpenGL::movView(float Xd,float Yd,float Zd)
{
showOffset.setX(showOffset.x()+Xd);
showOffset.setY(showOffset.y()+Yd);
showOffset.setZ(showOffset.y()+Zd);
}

void WLOpenGL::setPointRot(QVector4D pR)
{    
pR.setW(0); //устанавливаем в ноль 

QVector4D P=showMatrix*pR;//находим наши коорд на экран

showOffset+=(showMatrix.column(3)+P)*Zoom;//двигаем экран на разницу

showMatrix.setColumn(3,QVector4D(-P.x(),-P.y(),-P.z(),1));//устанавливаем 

qDebug()<<"setRotPoint";
}

void WLOpenGL::setRotView()
{
}


void WLOpenGL::resizeGL(int w, int h)
{
vport[0]=0;
vport[1]=0;
vport[2]=w;
vport[3]=h;

float wf=w;
float hf=h;

projection.setToIdentity();
projection.ortho(-wf/2,wf/2,-hf/2,hf/2,-50000,50000);
}

void WLOpenGL::zoomView(QPoint MousePos,int delta)
{
if(MousePos.x()<=0||MousePos.x()>=vport[2]
 ||MousePos.y()<=0||MousePos.y()>=vport[3])
  {
  MousePos.setX(vport[2]/2);
  MousePos.setY(vport[3]/2);
  }

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

void WLOpenGL::resetView()
{
showMatrix.setToIdentity();
Zoom=1; 
}; 

void WLOpenGL::resetRotView()
{
showMatrix.setColumn(0,QVector4D(1,0,0,0)); 
showMatrix.setColumn(1,QVector4D(0,1,0,0)); 
showMatrix.setColumn(2,QVector4D(0,0,1,0)); 
}; 


void WLOpenGL::startMovie()
{
t=0;
TimerMovie->start();
}

void WLOpenGL::updateView()
{
t+=0.1;

if(t>=1)   {TimerMovie->stop(); t=1;}

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


update();
}

void WLOpenGL::setView(WLFrame Fr)
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
