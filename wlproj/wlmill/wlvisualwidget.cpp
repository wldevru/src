#include "wlvisualwidget.h"

#include <QtGui>
#include <QMessageBox>
#include <QTextStream>
#include <QFont>
#include <QMenu>
#include <QStringList>
#include <QTextStream>

#define _USE_MATH_DEFINES
#include <math.h>



#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif


WLVisualWidget::WLVisualWidget(WLGProgram *_Program,WLMillMachine *_MillMachine):WLOpenGL()
  ,vGLBufProgram(QOpenGLBuffer::VertexBuffer)
  ,vGLBufMill(QOpenGLBuffer::VertexBuffer)
  ,vGLBufHome(QOpenGLBuffer::VertexBuffer)
  ,iGLBufHome(QOpenGLBuffer::IndexBuffer)  
  ,vGLBufTool(QOpenGLBuffer::VertexBuffer)
  ,iGLBufTool(QOpenGLBuffer::IndexBuffer)
  ,vGLBufSC(QOpenGLBuffer::VertexBuffer)  
  ,vGLBufBox(QOpenGLBuffer::VertexBuffer)
  ,iGLBufBox(QOpenGLBuffer::IndexBuffer)  

{
m_typeView=XYZ;
m_typeOffset=Model;

//GLProgramElemntsList.clear();
m_Program=_Program;
lastIndexProgram=0;
m_viewLimits=true;

m_MillMachine=_MillMachine;


connect(m_Program,SIGNAL(ChangedShowTraj()),this,SLOT(updateTrajProgram()),Qt::QueuedConnection);
connect(m_Program,SIGNAL(changedActivElement(int)),this,SLOT(setEditElement(int)),Qt::QueuedConnection);

connect(m_Program,SIGNAL(startedBuildShow()),this,SLOT(resetProgramBuffer()),Qt::DirectConnection);

connect(m_MillMachine,SIGNAL(changedReadyRunList(bool)),this,SLOT(setEnRotTool(bool)));


GLMillElemnts=0;
GLlastMillElemnts=0;

m_viewProgramF=true;
m_viewMillF=true;
m_viewBacklash=false;
m_viewRotPointF=false;
m_zoomDir=false;

lastSizeSPsize=0;
//GLTool=0;
GLArrow=0;

m_toolHeight=25;
m_toolDiametr=8;

setFocusPolicy(Qt::ClickFocus);

EditElement=0;

m_rotTool=0;

m_tbViewRot = new QToolButton(this);
m_tbViewRot -> setIcon(QPixmap(":/data/icons/viewMov.png"));
m_tbViewRot -> setIconSize(QSize(32,32));
m_tbViewRot -> setToolTip(tr("Rot or move view"));
connect(m_tbViewRot,&QToolButton::clicked,this,&WLVisualWidget::on_TButtonRot);

m_tbViewCenter = new QToolButton(this);
m_tbViewCenter -> setIcon(QPixmap(":/data/icons/viewCenter.png"));
m_tbViewCenter -> setIconSize(QSize(32,32));
m_tbViewCenter -> setToolTip(tr("view to window"));
connect(m_tbViewCenter,&QToolButton::clicked,this,&WLVisualWidget::setViewCenter);

///----View Button
m_tbView = new QToolButton(this);
m_tbView -> setIcon(QPixmap(":/data/icons/viewModel.png"));
m_tbView -> setIconSize(QSize(32,32));
m_tbView -> setToolTip(tr("view orientation"));
//m_tbToolView->setVisible(false);

QMenu *menuView = new QMenu;

menuView->addAction(tr("Top"),   this,SLOT(setViewUp()));
menuView->addAction(tr("Bottom"),this,SLOT(setViewDown()));
menuView->addAction(tr("Left")  ,this,SLOT(setViewLeft()));
menuView->addAction(tr("Right") ,this,SLOT(setViewRight()));
menuView->addAction(tr("Front"), this,SLOT(setViewFront()));
menuView->addAction(tr("Rear")  ,this,SLOT(setViewRear()));

m_tbView->setMenu(menuView);
m_tbView->setPopupMode(QToolButton::InstantPopup);

///----ViewShow Button
m_tbViewShow = new QToolButton(this);
m_tbViewShow -> setIcon(QPixmap(":/data/icons/viewShow.png"));
m_tbViewShow -> setIconSize(QSize(32,32));
m_tbViewShow -> setToolTip(tr("list show"));

QMenu *menuViewShow = new QMenu;
QAction *Action;

Action=menuViewShow->addAction(tr("Program"),   this,SLOT(setViewProgram()));
Action->setCheckable(true);
Action->setChecked(true);

Action=menuViewShow->addAction(tr("Trajectory"),this,SLOT(setViewMill()));
Action->setCheckable(true);
Action->setChecked(true);

Action=menuViewShow->addAction(tr("Limits"),    this,SLOT(setViewLimits()));
Action->setCheckable(true);
Action->setChecked(true);

Action=menuViewShow->addAction(tr("Rot"),this,SLOT(setViewRotPoint()));
Action->setCheckable(true);

m_tbViewShow->setMenu(menuViewShow);
m_tbViewShow->setPopupMode(QToolButton::InstantPopup);

///----ViewType Button

m_tbViewType = new QToolButton(this);
m_tbViewType -> setIcon(QPixmap(":/data/icons/viewType.png"));
m_tbViewType -> setIconSize(QSize(32,32));
m_tbViewType -> setToolTip(tr("type show"));
QMenu *menuViewType = new QMenu;
QActionGroup *actionGroup = new QActionGroup(this);

Action=menuViewType->addAction(tr("XYZ"),this,SLOT(setViewXYZ()));
Action->setCheckable(true);
Action->setChecked(true);
actionGroup->addAction(Action);

Action=menuViewType->addAction(tr("GModel"),this,SLOT(setViewGModel()));
Action->setCheckable(true);
Action->setChecked(false);
actionGroup->addAction(Action);

actionGroup = new QActionGroup(this);

menuViewType->addSeparator();

Action=menuViewType->addAction(tr("Model"),this,SLOT(setViewOffsetModel()));
Action->setCheckable(true);
Action->setChecked(true);
actionGroup->addAction(Action);

Action=menuViewType->addAction(tr("Tool"),this,SLOT(setViewOffsetTool()));
Action->setCheckable(true);
Action->setChecked(false);
actionGroup->addAction(Action);

m_tbViewType->setMenu(menuViewType);
m_tbViewType->setPopupMode(QToolButton::InstantPopup);

m_tbZoomIn = new QToolButton(this);
m_tbZoomIn -> setIcon(QPixmap(":/data/icons/zoomIn.png"));
m_tbZoomIn -> setIconSize(QSize(32,32));
m_tbZoomIn -> setToolTip(tr("zoom in"));
m_tbZoomIn -> setAutoRepeat(true);
connect(m_tbZoomIn,&QToolButton::clicked,this,&WLVisualWidget::on_tbZoomIn);

m_tbZoomOut = new QToolButton(this);
m_tbZoomOut -> setIcon(QPixmap(":/data/icons/zoomOut.png"));
m_tbZoomOut -> setIconSize(QSize(32,32));
m_tbZoomOut -> setToolTip(tr("zoom out"));
m_tbZoomOut -> setAutoRepeat(true);
connect(m_tbZoomOut,&QToolButton::clicked,this,&WLVisualWidget::on_tbZoomOut);



m_timerView=new QTimer;
m_timerView->setSingleShot(true);



connect(m_timerView,SIGNAL(timeout()),this,SLOT(updateRotTool()));
connect(m_timerView,SIGNAL(timeout()),this,SLOT(update()));

QTimer::singleShot(300,this,SLOT(update()));

QTimer *timer = new QTimer;
timer->start(300);
}


WLVisualWidget::~WLVisualWidget()
{

}

void WLVisualWidget::WLDrawArrow1(WL3DPoint Ar,WL3DPoint O,float s)
{
 /*
makeCurrent();
int n=20;
float da,R,A;
R=1.5;
n=10;

WL3DPoint   End(0,0,5);
WL3DPoint  Point(R,0,0);
WL3DPoint SPoint(R,0,0);
da=2*M_PI/n;

Ar=Ar.normalize();

WL3DPoint I;
WL3DPoint J;
WL3DPoint K(0,0,1);

I=Ar;

J=K*I;

QMatrix4x4 M;

M.setColumn(0,QVector4D(I.x,I.y,I.z,0));
M.setColumn(1,QVector4D(J.x,J.y,J.z,0));
M.setColumn(2,QVector4D(K.x,K.y,K.z,0));
M.setColumn(3,QVector4D(0,0,0,1));

QMatrix4x4 MR(1,0,0,0
	         ,0,1,0,0
			 ,0,0,1,0
			 ,0,0,0,1);


M.rotate(-15,1,0,0);

I.set(M(0,0),M(1,0),M(2,0));
J.set(M(0,1),M(1,1),M(2,1));
K.set(M(0,2),M(1,2),M(2,2));

M.setColumn(3,QVector4D(O.x,O.y,O.z,1));

K=K.normalize();

//qDebug()<<"K1("<<K.x<<","<<K.y<<","<<K.z<<")";

double rA=0,rB=0,rC=0;
WL3DPoint P1,P0;

P0=P1=K;
P0.y=0;

rC=acos(P0.r()/P1.r())*180/M_PI;
if(P1.y>0) rC=-rC;


rB=asin(P0.x/P0.r())*180/M_PI;

glColor3f(0,0.6,0);
WLDrawArrow(I,O+I*5);
WLDrawArrow(J,O+J*5);
glColor3f(0,0.9,0);
WLDrawArrow(K,O+K*10);


M.setColumn(3,QVector4D(O.x,O.y,O.z,1));

I.set(M(0,0),M(1,0),M(2,0));
J.set(M(0,1),M(1,1),M(2,1));
K.set(M(0,2),M(1,2),M(2,2));

glColor3f(0.6,0,0);
WLDrawArrow(I,O+I*7);
WLDrawArrow(J,O+J*7);
glColor3f(0.9,0,0);
WLDrawArrow(K,O+K*14);


glPushMatrix();


#if QT_VERSION >= 0x050000
  glMultMatrixf(M.data());
#else
  glMultMatrixd(M.data());
#endif

glScalef(s,s,s);

glPopMatrix();
*/
}

void WLVisualWidget::WLDrawArrow(WL3DPoint Ar,WL3DPoint O,float s)
{
/*
makeCurrent();
Ar=Ar.normalize();
WL3DPoint I;
WL3DPoint J;

if(Ar.x!=0||Ar.y!=0)
	 {I.x=Ar.y;I.y=-Ar.x;I.z=Ar.z;}
   else
	 {I.x=1;I.y=0;I.z=0;}

I=I.normalize();
J=Ar*I;
J=J.normalize();
I=J*Ar;

QMatrix4x4 M;

M.setColumn(0,QVector4D(I.x,I.y,I.z,0));
M.setColumn(1,QVector4D(J.x,J.y,J.z,0));
M.setColumn(2,QVector4D(Ar.x,Ar.y,Ar.z,0));
M.setColumn(3,QVector4D(O.x,O.y,O.z,1));

if(GLArrow==0) calcPointsArrow();

glPushMatrix();

#if QT_VERSION >= 0x050000
  glMultMatrixf(M.data());
#else
  glMultMatrixd(M.data());
#endif

glScalef(s,s,s);

glCallList(GLArrow);

glPopMatrix();
*/
}

void WLVisualWidget::updateRotTool()
{
//#ifdef MILL3D 
QMutexLocker locker(&Mutex); 

if(m_enRotToolF)
	{
    m_rotTool-=4;
    if(m_rotTool>0) m_rotTool-=360;
    }

//#endif

}


void WLVisualWidget::paintGL()
{
    // Clear color and depth buffer
    setGLClearColor();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int activSC=m_MillMachine->GCode()->getActivSC();

    WL6DPoint  SC=m_MillMachine->GCode()->getOffsetSC(activSC).to6D();

    SC.a=m_MillMachine->GCode()->getRefPoint0SC(activSC).a;

    showSC("G"+QString::number(activSC+53),SC.toM());
    showSC("G53",WL6DPoint().toM(),1.5);

    if(m_viewProgramF)  showProgramTraj();
    if(m_viewMillF)     showMillTraj();

    showTrackTraj();

    if(m_typeView==XYZ)
     {
     showHome(m_MillMachine->GCode()->getG28Position().to3D());
     showTool(m_MillMachine->getCurrentPosition().to3D(),true,10,QVector3D(0,1,0));

     if(m_viewRotPointF) showRotPoint();

     if(m_viewLimits){

      showBox(WL3DPointf((m_MillMachine->getDrive("X")? m_MillMachine->getDrive("X")->minPosition():0)
                        ,(m_MillMachine->getDrive("Y")? m_MillMachine->getDrive("Y")->minPosition():0)
                        ,(m_MillMachine->getDrive("Z")? m_MillMachine->getDrive("z")->minPosition():0))
             ,WL3DPointf((m_MillMachine->getDrive("X")? m_MillMachine->getDrive("X")->maxPosition():0)
                        ,(m_MillMachine->getDrive("Y")? m_MillMachine->getDrive("Y")->maxPosition():0)
                        ,(m_MillMachine->getDrive("Z")? m_MillMachine->getDrive("Z")->maxPosition():0))
                        ,QVector3D(1,1,1));
      }

     showBox(m_MillMachine->getAxisPosition().to3D()
                      ,m_MillMachine->getDrive("X")? m_MillMachine->getDrive("X")->getBacklash():0
                      ,m_MillMachine->getDrive("Y")? m_MillMachine->getDrive("Y")->getBacklash():0
                      ,m_MillMachine->getDrive("Z")? m_MillMachine->getDrive("Z")->getBacklash():0
                      ,QVector3D(.75,0,0));
     }
    else {
         showHome(m_MillMachine->getGModel()->getFrame(m_MillMachine->GCode()->getG28Position()));
         showTool(m_MillMachine->getGModel()->getFrame(m_MillMachine->getCurrentPosition()).to6D(),true,10,QVector3D(0,1,0));
    }


    m_timerView->start(25);

}

void WLVisualWidget::paintGLold()
{  
//if(Mutex.locked()) return;
//if(ListTraj.size()==0) return;
/*
int w=vport[2];
int h=vport[3];

//glDisable(GL_LIGHTING);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glOrtho((GLdouble)-w/2,(GLdouble)w/2,(GLdouble)-h/2,(GLdouble)h/2,(GLdouble)-50000,(GLdouble)50000);

glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);

int iSC=1;
WL3DPoint P(0,0,0);

P=MillMachine->GCode.getHomePosition().to3D();

glLoadIdentity();
setRotView();
glColor3f(1,1,0);

WL6DPoint SCPoint=MillMachine->GCode.getOffsetSC(viewSC).to3D();
SCPoint.a=MillMachine->GCode.getRefPoint0SC(viewSC).a;

#if QT_VERSION >= 0x050000
  glMultMatrixf(SCPoint.toM().data());
#else
  glMultMatrixd(SCPoint.toM().data());
#endif


glScalef(1/Zoom,1/Zoom,1/Zoom); 
showSC("G"+QString::number(viewSC+53));

if(viewRotPointF)
{
glLoadIdentity();
setRotView();
glColor3f(1,1,1);

WLFrame frRefP0,frRefP1;

SCPoint=MillMachine->GCode.getOffsetSC(viewSC).to3D();
frRefP0.fromM(SCPoint.toM()*MillMachine->GCode.getRefPoint0SC(viewSC).to3D().toM());
showTool(frRefP0.to6D(),false,2);

SCPoint.a=MillMachine->GCode.getRefPoint0SC(viewSC).a;

frRefP0=MillMachine->GCode.getRefPoint0SC(viewSC).to3D();

frRefP1.fromM(frRefP0.toM()*SCPoint.toM()*frRefP0.toM().inverted()*MillMachine->GCode.getRefPoint1SC(viewSC).to3D().toM());
showTool(frRefP1.to6D(),false,1);
}

//PointRot.set(P.x,P.y,P.z);

P=MillMachine->GCode.getHomePosition().to3D();
glLoadIdentity();
setRotView();
glColor3f(1,1,0);
glTranslatef(P.x,P.y,P.z);
glScalef(1/Zoom,1/Zoom,1/Zoom); 
showHome();

glColor3f(1,0,1);
//showHome(Program->getBackPosition());

glLoadIdentity();
glColor3f(0,1,1);

glLoadIdentity();
setRotView();
glColor3f(0,1,0);
showTool(MillMachine->getCurrentPosition().to6D(),true);

if(true)//viewBacklash)
{
glLoadIdentity();
setRotView();
glColor3f(0.65,0,0);

WLGPoint pos=MillMachine->getAxisPosition();
showBox(WL6DPoint(pos.x
                 ,pos.y
                 ,pos.z)
                 ,MillMachine->getDrive("X")? MillMachine->getDrive("X")->getBacklash():0
                 ,MillMachine->getDrive("Y")? MillMachine->getDrive("Y")->getBacklash():0
                 ,MillMachine->getDrive("Z")? MillMachine->getDrive("Z")->getBacklash():0);
//showTool(MillMachine->getAxisPosition(),true); 
}

glLoadIdentity();
setRotView();
glColor3f(0.9,0.9,0.9);
if(viewLimits)
showBox(WL3DPointf((MillMachine->getDrive("X")? MillMachine->getDrive("X")->getMinPosition():0)
                  ,(MillMachine->getDrive("Y")? MillMachine->getDrive("Y")->getMinPosition():0)
                  ,(MillMachine->getDrive("Z")? MillMachine->getDrive("z")->getMinPosition():0))
       ,WL3DPointf((MillMachine->getDrive("X")? MillMachine->getDrive("X")->getMaxPosition():0)
                  ,(MillMachine->getDrive("Y")? MillMachine->getDrive("Y")->getMaxPosition():0)
                  ,(MillMachine->getDrive("Z")? MillMachine->getDrive("Z")->getMaxPosition():0)));


glLoadIdentity();
setRotView();
showTrackTraj(); 


if(viewProgramF)
 {
 glLoadIdentity();
 setRotView();
 showProgramTraj(false);
 }

if(viewMillF)
 {
 glLoadIdentity();
 setRotView();
 showMillTraj(false);
 
 }
*/

} 

void WLVisualWidget::showBox(WL3DPointf P0,WL3DPointf P1,QVector3D color)
{
showBox(((P0+P1)/2).to3D()
        ,P1.x-P0.x
        ,P1.y-P0.y
        ,P1.z-P0.z
        ,color);
}


void WLVisualWidget::showBox(WL6DPoint showPoint,float dx,float dy,float dz,QVector3D color)
{
WL3DPointf Points[8];

dx/=2;
dy/=2;
dz/=2;

Points[0].x=-dx; Points[0].y=-dy; Points[0].z=-dz;
Points[1].x= dx; Points[1].y=-dy; Points[1].z=-dz;
Points[2].x= dx; Points[2].y= dy; Points[2].z=-dz;
Points[3].x=-dx; Points[3].y= dy; Points[3].z=-dz;

Points[4].x=-dx; Points[4].y=-dy; Points[4].z= dz;
Points[5].x= dx; Points[5].y=-dy; Points[5].z= dz;
Points[6].x= dx; Points[6].y= dy; Points[6].z= dz;
Points[7].x=-dx; Points[7].y= dy; Points[7].z= dz;

int vertexLocation;

QMatrix4x4 matrix;

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);

vGLBufBox.bind();
vGLBufBox.allocate(Points,8*sizeof(WL3DPointf));

iGLBufBox.bind();

progOneColor.bind();
progOneColor.setUniformValue("mpv_matrix",projection
                                         *matrix
                                         *getShowMatrix()
                                         *showPoint.toM());

progOneColor.setUniformValue("u_scale",1.0f);
progOneColor.setUniformValue("u_color",color);

vertexLocation = progOneColor.attributeLocation("a_position");
progOneColor.enableAttributeArray(vertexLocation);
progOneColor.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3);

glDrawElements(GL_LINES,24,GL_UNSIGNED_BYTE,0);
}



void WLVisualWidget::showTool(WL6DPoint showPoint,bool rot,float scale,QVector3D color)
{
int vertexLocation;
QMatrix4x4 matrix,rotM;

rotM.setToIdentity();

if(rot)
 rotM.rotate(m_rotTool,0,0,1.);

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);

vGLBufTool.bind();
iGLBufTool.bind();

progOneColor.bind();
progOneColor.setUniformValue("mpv_matrix",projection
                                         *matrix
                                         *getShowMatrix()
                                         *showPoint.toM()
                                         *rotM);

progOneColor.setUniformValue("u_scale",scale);
progOneColor.setUniformValue("u_color",color);

vertexLocation = progOneColor.attributeLocation("a_position");
progOneColor.enableAttributeArray(vertexLocation);
progOneColor.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,sizeof(WL3DPointf));

glDrawElements(GL_LINES,toolPointsSize*2,GL_UNSIGNED_BYTE,0);
glDrawArrays(GL_LINE_LOOP, 1,toolPointsSize);
}


void WLVisualWidget::showHome(WLFrame Fr)
{
int vertexLocation;
QMatrix4x4 matrix;

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);

vGLBufHome.bind();
iGLBufHome.bind();

progOneColor.bind();
progOneColor.setUniformValue("mpv_matrix",projection*matrix*getShowMatrix()*Fr.toM());
progOneColor.setUniformValue("u_scale",5.0f);
progOneColor.setUniformValue("u_color",QVector3D(1,1,0));

vertexLocation = progOneColor.attributeLocation("a_position");
progOneColor.enableAttributeArray(vertexLocation);
progOneColor.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3);

glDrawElements(GL_LINE_LOOP,8,GL_UNSIGNED_BYTE,0);
}

void WLVisualWidget::showSC(QString nameSC,WLFrame pos,float scale)
{
int vertexLocation;

QMatrix4x4 matrix;

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);

glLineWidth(3);


vGLBufSC.bind();
progOneColor.bind();
progOneColor.setUniformValue("mpv_matrix",projection
                                         *matrix
                                         *getShowMatrix()
                                         *pos.toM());

progOneColor.setUniformValue("u_scale",(scale*50.0f/Zoom));

vertexLocation = progOneColor.attributeLocation("a_position");
progOneColor.enableAttributeArray(vertexLocation);
progOneColor.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,sizeof(QVector3D));

progOneColor.setUniformValue("u_color",QVector3D(1,0,0));
glDrawArrays(GL_LINES, 1,2);
progOneColor.setUniformValue("u_color",QVector3D(0,1,0));
glDrawArrays(GL_LINES, 2,2);
progOneColor.setUniformValue("u_color",QVector3D(0,0,1));
glDrawArrays(GL_LINES, 4,2);
}

void WLVisualWidget::showMillTraj()
{
QMutexLocker locker1(&m_MillMachine->MutexShowTraj);

if(!m_MillMachine->isReady()) return;

//#ifdef MILL3D
bool ok;

qint32 curId=m_MillMachine->getMotionDevice()->getModulePlanner()->getCurIdElement();
qint32 indexMPlanner=curId+m_MillMachine->getMotionDevice()->getModulePlanner()->getCountBuf();

int pointsCountBuf=0;

QVector <WL3DPointf> showPoints;

if(!m_MillMachine->showMillTraj.isEmpty())
{
QList <WL6DPoint> Points;

for(int i=0;i<m_MillMachine->showMillTraj.size();i++)
  {
   if(m_MillMachine->showMillTraj[i].index<curId)
	   {       
       m_MillMachine->showMillTraj.removeAt(i--);
       }
   else
      {
      break;
      }
  }


for(int i=0;i<m_MillMachine->showMillTraj.size();i++)
  {
  if(m_MillMachine->showMillTraj[i].index==indexMPlanner)
   {
   //qDebug()<<"pointsCountBuf="<<Points.size();
   pointsCountBuf=Points.size();
   }

  if(m_typeView==XYZ)
    {
    WLGModel GModel;
    Points+=m_MillMachine->showMillTraj[i].calcPoints(&ok,&GModel);
    }
  else
    Points+=m_MillMachine->showMillTraj[i].calcPoints(&ok,m_MillMachine->getGModel(),2);
 
  if(m_MillMachine->showMillTraj[i].index<=indexMPlanner)
   {
   //qDebug()<<"pointsCountBuf="<<Points.size();
   pointsCountBuf=Points.size();
   }
  }
//glEnd();

if(!Points.isEmpty())
{
showPoints.reserve(Points.size());

for(int j=0;j<Points.size();j++)
   {
   showPoints+=Points[j].to3Df();

//  glVertex3f(Points[j].x,Points[j].y,Points[j].z);
   }

//qDebug()<<"lastPoint"<<showPoints.last().to3D().toString();
 }

if(!showPoints.isEmpty())
{
int vertexLocation;
QMatrix4x4 matrix;

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);

vGLBufMill.bind();
vGLBufMill.allocate(showPoints.data(),showPoints.size()*sizeof(WL3DPointf));

progOneColor.bind();
progOneColor.setUniformValue("mpv_matrix",projection*matrix*getShowMatrix());
progOneColor.setUniformValue("u_scale",1.0f);
progOneColor.setUniformValue("u_color",QVector3D(0,1,1));

vertexLocation = progOneColor.attributeLocation("a_position");
progOneColor.enableAttributeArray(vertexLocation);
progOneColor.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3);

glLineWidth(3);
glDrawArrays(GL_LINE_STRIP, pointsCountBuf,showPoints.size()-pointsCountBuf);

glLineWidth(4);
progOneColor.setUniformValue("u_color",QVector3D(1,1,0));
glDrawArrays(GL_LINE_STRIP, 0,pointsCountBuf);
}
//glNormalPointer(GL_DOUBLE,   sizeof(WL3DPoint),&Triangles.data()+1);
//qDebug()<<"ToolIndices.size()"<<ToolIndices.size();


}
//vGLBufMill.release();

//MillMachine->MutexShowTraj.unlock();
//#endif

}

void WLVisualWidget::showTrackTraj()
{
if(trackTraj.size()==defTrackSize) trackTraj.removeFirst();

if(m_typeView==XYZ)
  trackTraj+=m_MillMachine->getCurrentPosition().to6D().to3Df();
else
  trackTraj+=m_MillMachine->getGModel()->getFrame(m_MillMachine->getCurrentPosition()).to6D().to3Df();

int vertexLocation;
QMatrix4x4 matrix;

QVector <WL3DPointf> track=trackTraj.toVector();

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);


vGLBufTrack.bind();
vGLBufTrack.write(0,track.data(),track.size()*sizeof(WL3DPointf));

progOneColor.bind();
progOneColor.setUniformValue("mpv_matrix",projection*matrix*getShowMatrix());
progOneColor.setUniformValue("u_scale",1.0f);
progOneColor.setUniformValue("u_color",QVector3D(0,1,0));

vertexLocation = progOneColor.attributeLocation("a_position");
progOneColor.enableAttributeArray(vertexLocation);
progOneColor.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3);

glLineWidth(3);
glDrawArrays(GL_LINE_STRIP, 0,trackTraj.size());
vGLBufTrack.release();
}

void WLVisualWidget::showRotPoint()
{
WLFrame frRefP0,frRefP1;
WL6DPoint SCPoint;
int activSC=m_MillMachine->GCode()->getActivSC();

SCPoint=m_MillMachine->GCode()->getOffsetSC(activSC).to3D();
frRefP0.fromM(SCPoint.toM()*m_MillMachine->GCode()->getRefPoint0SC(activSC).to3D().toM());
showTool(frRefP0.to6D(),false,5,QVector3D(0.8f,0.8f,0.0f));

SCPoint.a=m_MillMachine->GCode()->getRefPoint0SC(activSC).a;

frRefP0=m_MillMachine->GCode()->getRefPoint0SC(activSC).to3D();

frRefP1.fromM(frRefP0.toM()*SCPoint.toM()*frRefP0.toM().inverted()*m_MillMachine->GCode()->getRefPoint1SC(activSC).to3D().toM());
showTool(frRefP1.to6D(),false,2,QVector3D(0.8f,0.8f,0.0f));
}



void WLVisualWidget::showProgramTraj(bool select)
{
QMutexLocker locker1(&Mutex);

if(!m_Program->showPoints.isEmpty()
  &&m_Program->MutexShowPoint.tryLock(5))
{
int vertexLocation;

QMatrix4x4 Mrot;
QVector4D P;

vGLBufProgram.bind();

int curSize=(m_Program->showPoints.size()*sizeof(WLShowPointProgram));

if(lastSizeSPsize!=curSize)
{
if((vGLBufProgram.size()/sizeof(WLShowPointProgram))!=m_Program->maxShowPoints())
     vGLBufProgram.allocate(m_Program->maxShowPoints()*sizeof(WLShowPointProgram));

QVector <WLShowPointProgram> data=m_Program->showPoints.mid(lastSizeSPsize/sizeof(WLShowPointProgram)).toVector();

vGLBufProgram.write(lastSizeSPsize,data.data(),data.size()*sizeof(WLShowPointProgram));

lastSizeSPsize=curSize;
}

if(select)
{
qDebug()<<"selectWire"<<m_Program->indexData.size();

QMatrix4x4 matrix;

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);

progSelect.bind();
progSelect.setUniformValue("mpv_matrix",projection*matrix*getShowMatrix());

vertexLocation = progSelect.attributeLocation("a_position");
progSelect.enableAttributeArray(vertexLocation);
progSelect.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,sizeof(WLShowPointProgram));

vertexLocation = progSelect.attributeLocation("a_scolor");
progSelect.enableAttributeArray(vertexLocation);
progSelect.setAttributeBuffer(vertexLocation,GL_FLOAT,sizeof(WL3DPointf)*2,1,sizeof(WLShowPointProgram));

glLineWidth(4);
glDrawArrays(GL_LINE_STRIP, 0,m_Program->showPoints.size());
}
else
{

if(!m_Program->showPoints.isEmpty())
{

QMatrix4x4 matrix;

matrix.setToIdentity();
matrix.translate(showOffset.x(),showOffset.y(),.0);
matrix.scale(Zoom);


progTraj.bind();
progTraj.setUniformValue("mpv_matrix",projection*matrix*getShowMatrix());


vertexLocation = progTraj.attributeLocation("a_position");
progTraj.enableAttributeArray(vertexLocation);
progTraj.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,sizeof(WLShowPointProgram));

vertexLocation = progTraj.attributeLocation("a_color");
progTraj.enableAttributeArray(vertexLocation);
progTraj.setAttributeBuffer(vertexLocation,GL_FLOAT,sizeof(WL3DPointf),3,sizeof(WLShowPointProgram));

glLineWidth(1);
glDrawArrays(GL_LINE_STRIP, 0,m_Program->showPoints.size());

progTraj.release();

}	


if((0<=EditElement)&&((EditElement+1)<m_Program->getElementCount())
 &&(m_Program->indexData[EditElement+1].offsetPoint<m_Program->showPoints.size()))
{ 
  QMatrix4x4 matrix;

  matrix.setToIdentity();
  matrix.translate(showOffset.x(),showOffset.y(),.0);
  matrix.scale(Zoom);

  progOneColor.bind();
  progOneColor.setUniformValue("mpv_matrix",projection*matrix*getShowMatrix());

  int vertexLocation = progOneColor.attributeLocation("a_position");
  progOneColor.enableAttributeArray(vertexLocation);
  progOneColor.setAttributeBuffer(vertexLocation,GL_FLOAT,0,3,sizeof(WLShowPointProgram));
  progOneColor.setUniformValue("u_scale",1.0f);
  progOneColor.setUniformValue("u_color",QVector3D(1,1,1));

  glLineWidth(3);

  if(EditElement!=(m_Program->indexData.size()-1))
   glDrawArrays(GL_LINE_STRIP, m_Program->indexData[EditElement].offsetPoint, m_Program->indexData[EditElement+1].offsetPoint
                                                                           -m_Program->indexData[EditElement].offsetPoint);
  else
   glDrawArrays(GL_LINE_STRIP, m_Program->indexData[EditElement].offsetPoint, m_Program->showPoints.size()
                                                                           -m_Program->indexData[EditElement].offsetPoint);


  progOneColor.release();

} 

}

m_Program->MutexShowPoint.unlock();
}

}



void WLVisualWidget::mousePressEvent(QMouseEvent *event)
{
event->accept();
//qDebug()<<"press";
m_lastMousePos=event->pos();

//QList<WLElementTraj>  ListTraj=Program->getTraj();

if (event->buttons() & Qt::LeftButton) 
 {
 int x=event->x();
 int y=event->y();
 long n;

 n=selectElement(x,y);
 setEditElement(n);  

 m_timePress.start();

 updatePointRot();
 } 
 else
 if (event->buttons() & Qt::MidButton )  updatePointRot();

}


int WLVisualWidget::selectElement(int x,int y)
{
 makeCurrent();

 static  GLuint fbo=0;
 static GLuint rbrgba=0;
 static GLuint rbdepth=0;

 if(rbrgba==0)   glGenRenderbuffers(1, &rbrgba);

    glBindRenderbuffer(GL_RENDERBUFFER, rbrgba);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width(),height());

 if(rbdepth==0)   glGenRenderbuffers(1, &rbdepth);

    glBindRenderbuffer(GL_RENDERBUFFER, rbdepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width(),height());


 if(fbo==0) glGenFramebuffers(1, &fbo);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_RENDERBUFFER, rbrgba);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, rbdepth);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
     {
     qDebug()<<"False Frame Buffer Status"<<glCheckFramebufferStatus(GL_FRAMEBUFFER);
     }

    glEnable(GL_DEPTH_TEST);

    glViewport(0,0,width(),height());

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    showProgramTraj(true);

    GLubyte res[4];
    GLint viewPort[4];
    int ret;

    glGetIntegerv(GL_VIEWPORT,viewPort);
    glReadPixels(x,viewPort[3]-y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,res);

    ret=res[0]*255*255+res[1]*255+res[2];

    qDebug()<<"select Color"<<res[0]<<res[1]<<res[2]<<ret;
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebufferObject());

    doneCurrent();

    return static_cast<int>(ret);
}

 

 void WLVisualWidget::mouseMoveEvent(QMouseEvent *event)
 {
 event->accept();

     int dx = event->x() - m_lastMousePos.x();
     int dy = event->y() - m_lastMousePos.y();

     if (event->buttons() & Qt::MidButton)
     {
	 if(QApplication::keyboardModifiers()&Qt::ControlModifier)
	    movView(dx,-dy);
      else
        rotView(dy/3,dx/3);
     }
     else if (event->buttons() & Qt::LeftButton)
         {
         if(m_rotViewF)
             rotView(dy/3,dx/3);
         else
             movView(dx,-dy);
         }

     m_lastMousePos = event->pos();
 }

void WLVisualWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
Q_UNUSED(event);
setViewCenter();
}

void WLVisualWidget::keyPressEvent ( QKeyEvent * event )
{

}

void WLVisualWidget::initShaders()
{
// Compile vertex shader
if(!progOneColor.addShaderFromSourceFile(QOpenGLShader::Vertex,  ":/onecolor.vsh")
 ||!progOneColor.addShaderFromSourceFile(QOpenGLShader::Fragment,":/onecolor.fsh"))
    close();

if (!progOneColor.link()
  ||!progOneColor.bind())
    close();


if(!progTraj.addShaderFromSourceFile(QOpenGLShader::Vertex,  ":/traj.vsh")
 ||!progTraj.addShaderFromSourceFile(QOpenGLShader::Fragment,":/traj.fsh"))
    close();

if (!progTraj.link()
  ||!progTraj.bind())
    close();


if(!progSelect.addShaderFromSourceFile(QOpenGLShader::Vertex,  ":/select.vsh")
 ||!progSelect.addShaderFromSourceFile(QOpenGLShader::Fragment,":/select.fsh"))
    close();

if (!progSelect.link()
  ||!progSelect.bind())
    close();

}

void WLVisualWidget::initGLBuffers()
{
WL3DPointf vHome[4];

vHome[0].set(-1, 1,0);
vHome[1].set( 1, 1,0);
vHome[2].set( 1,-1,0);
vHome[3].set(-1,-1,0);

GLubyte iHome[]={0,1,2,3,0,2,1,3};

vGLBufHome.create();
vGLBufHome.bind();
vGLBufHome.allocate(vHome,4*sizeof(WL3DPointf));

iGLBufHome.create();
iGLBufHome.bind();
iGLBufHome.allocate(iHome,8*sizeof(GLubyte));

QVector <WL3DPointf>vTool;
QVector <GLubyte>   iTool;
WL3DPointf P;
float dA,A;
float R=1.0;
float H=5.0;

dA=360/toolPointsSize;
A=0;

vTool+=P;

P.z=H;

for(quint8 i=0;i<toolPointsSize;i++)
 {
 iTool+=0;
 iTool+=(i+1);

 A+=dA;

 P.x=R*cosf(A*2*M_PI/360);
 P.y=R*sinf(A*2*M_PI/360);

 vTool+=P;
 }

vGLBufTool.create();
vGLBufTool.bind();
vGLBufTool.allocate(vTool.data(),sizeof(WL3DPointf)*vTool.size());

iGLBufTool.create();
iGLBufTool.bind();
iGLBufTool.allocate(iTool.data(),sizeof(GLubyte)*iTool.size());


vGLBufProgram.create();

QVector3D vSC[]={QVector3D(0.0f, 0.0f,  0.0f)
                ,QVector3D(1.0f, 0.0f,  0.0f)
                ,QVector3D(0.0f, 0.0f,  0.0f)
                ,QVector3D(0.0f, 1.0f,  0.0f)
                ,QVector3D(0.0f, 0.0f,  0.0f)
                ,QVector3D(0.0f, 0.0f,  1.0f)};

vGLBufSC.create();
vGLBufSC.bind();
vGLBufSC.allocate(vSC,6*sizeof(QVector3D));

vGLBufBox.create();
iGLBufBox.create();
iGLBufBox.bind();

GLubyte iBox[]={0,1,2,3,4,5,6,7,0,4,1,5,2,6,3,7,0,3,1,2,4,7,5,6};

iGLBufBox.allocate(iBox,sizeof(iBox)*sizeof(GLubyte));

vGLBufMill.create();

vGLBufTrack.create();
vGLBufTrack.bind();
vGLBufTrack.allocate(defTrackSize*sizeof(WL3DPointf));
}


void WLVisualWidget::wheelEvent( QWheelEvent * event )
{
zoomView(event->pos(),zoomDir()? -event->delta():event->delta());
}

void WLVisualWidget::createGLListTraj()
{

}

void WLVisualWidget::updatePointRot()
{
qDebug()<<"updateRotPoint";
//return;
QMutexLocker locker(&m_Program->Mutex);
//if(Program->ListTraj.size()==0) return; //если пуст
WL3DPointf Psum;

if(m_typeOffset==Tool)
{}
else {
 if(m_Program->MutexShowPoint.tryLock())
 {
 if(EditElement>0
 &&(EditElement<m_Program->indexData.size())
 &&((m_Program->indexData[EditElement].offsetPoint)<m_Program->showPoints.size()))
  {
  Psum=m_Program->showPoints[m_Program->indexData[EditElement].offsetPoint+1].pos;
  }
 else
  {
  Psum=(m_Program->getMinShowPoint()+m_Program->getMaxShowPoint())/2.0;
  }

 m_Program->MutexShowPoint.unlock();
 }
}

qDebug()<<"Psum"<<Psum.to3D().toString();

setPointRot(QVector4D(Psum.x,Psum.y,Psum.z,0));
}

QMatrix4x4 WLVisualWidget::getShowMatrix()
{
QMatrix4x4 ret;
if(m_typeOffset==Tool)
 {
 if(m_typeView==XYZ)
   {
   ret=showMatrix*m_MillMachine->getCurrentPosition().to3D().toM().inverted();
   }
 else
   {
   WLFrame Fr=m_MillMachine->getGModel()->getFrame(m_MillMachine->getCurrentPosition());

   ret=showMatrix*Fr.toM().inverted();
   }

 }
else
 ret=WLOpenGL::getShowMatrix();

return ret;
}

void WLVisualWidget::placeVisualElements()
{
m_tbViewRot-> move(this->width()/2-m_tbViewRot->width()/2,5);

m_tbZoomIn -> move(m_tbViewRot->geometry().x()-m_tbZoomIn->width()-10,5);
m_tbZoomOut-> move(m_tbViewRot->geometry().x()+m_tbViewRot->width()+10,5);

m_tbView  -> move(5,m_tbZoomOut->geometry().bottom()+3);
m_tbViewShow -> move(5,m_tbView->geometry().bottom()+3);
m_tbViewType -> move(5,m_tbViewShow->geometry().bottom()+3);
m_tbViewCenter->move(5,m_tbViewType->geometry().bottom()+10);
}

void WLVisualWidget::on_TButtonRot()
{
m_rotViewF=!m_rotViewF;

m_tbViewRot->setIcon(m_rotViewF ?
                     QPixmap(":/data/icons/viewRot.png")
                    :QPixmap(":/data/icons/viewMov.png"));

}

void WLVisualWidget::setViewCenter()
{
WL3DPointf minP,maxP;
QVector4D P;

QMatrix4x4 M=getShowMatrix();

 bool first=true;

 m_Program->MutexShowPoint.lock();

 foreach(WLShowPointProgram point,m_Program->showPoints)
 {
 P.setX(point.pos.x);
 P.setY(point.pos.y);
 P.setZ(point.pos.z);
 P.setW(1);

 P=M*P;

 if(first)
  {
  minP.x=maxP.x=P.x();
  minP.y=maxP.y=P.y();
  first=false;
  }
 else
   {
   if(minP.x>P.x()) minP.x=P.x();
     else if(maxP.x<P.x()) maxP.x=P.x();

   if(minP.y>P.y()) minP.y=P.y();
     else if(maxP.y<P.y()) maxP.y=P.y();
   }
 }

 m_Program->MutexShowPoint.unlock();

 if(m_Program->showPoints.isEmpty())
  {
  Zoom=1;

  showOffset.setX(0);
  showOffset.setY(0);
  }
 else
  {
  Zoom=qMin(qAbs(vport[2]/(maxP.x-minP.x)),qAbs(vport[3]/(maxP.y-minP.y)));


  if(m_typeOffset==Model)   {
  showOffset.setX(-(minP.x+maxP.x)/2*Zoom);
  showOffset.setY(-(minP.y+maxP.y)/2*Zoom);
  }
  else if(m_typeOffset==Tool) {
    showOffset.setX(0);
    showOffset.setY(0);
    }
  }

}




void WLVisualWidget::setToolDiametr(float d)
{
if(d<0.5||d>100) return; 

m_toolDiametr=d;

calcPointsTool();
} 

void WLVisualWidget::calcPointsTool()
{
int n=10;

ToolPoints.clear();
ToolIndices.clear();

float da,a,R;

da=360/n;

R=m_toolDiametr/2;

WL3DPoint P(0,0,0);

ToolPoints+=P;

P.z=m_toolHeight;

a=0;

for(int i=0;i<10;i++)
 {
 ToolIndices+=0;
 ToolIndices+=(i+1);

 a+=da;

 P.x=R*cos(a*2*M_PI/360);
 P.y=R*sin(a*2*M_PI/360);

 ToolPoints+=P;
 }


//if(GLTool==0) GLTool=glGenLists(1);
//qDebug()<<"setGLTool"<<GLTool;
/*
glNewList(GLTool,GL_COMPILE);

glBegin(GL_LINE_LOOP);
    for(int i=0;i<ToolPoints.size();i++)
	  {
      P=ToolPoints[i];
	  glVertex3f(P.x,P.y,P.z+toolHeight);
	  }
glEnd();

glBegin(GL_LINE_LOOP);
    for(int i=0;i<ToolPoints.size();i++)
	  {
	  P=ToolPoints[i];
	  glVertex3f(0,0,0);
	  glVertex3f(P.x,P.y,P.z+toolHeight);
	  }
glEnd();
glEndList();
qDebug()<<"setGLTool2"<<GLTool;*/
}

void WLVisualWidget::calcPointsArrow()
{
/*
int n;
float da,R,a;
R=1.5;
n=10;

qDebug()<<"calcPointsArrow";

ArrowPoints.clear();

da=360/n;

WL3DPoint P;

for(a=0;a<360;a+=da)
 {
 P.x=R*cos(a*2*M_PI/360);
 P.y=R*sin(a*2*M_PI/360);
 P.z=0;

 ArrowPoints+=P;
 }

if(GLArrow==0) GLArrow=glGenLists(1);

qDebug()<<"setGLArrow"<<GLArrow;

glNewList(GLArrow,GL_COMPILE);

for(int i=0;i<ArrowPoints.size();i++)
{
glBegin(GL_LINE_LOOP);
 glVertex3f(0,0,0);
 glVertex3f(ArrowPoints[i].x
	       ,ArrowPoints[i].y
		   ,ArrowPoints[i].z-5);
 if(i==0)
	 glVertex3f(ArrowPoints[ArrowPoints.size()-1].x
	           ,ArrowPoints[ArrowPoints.size()-1].y
		       ,ArrowPoints[ArrowPoints.size()-1].z-5);
   else
	 glVertex3f(ArrowPoints[i-1].x
	           ,ArrowPoints[i-1].y
		       ,ArrowPoints[i-1].z-5); 
glEnd();
}

glEndList();
*/
}


void WLVisualWidget::setToolHeight(float h)
{
if(h<0.5f||h>200.5f) return;
m_toolHeight=h;

calcPointsTool();
}

void WLVisualWidget::showEvent(QShowEvent *event)
{
Q_UNUSED(event)
    placeVisualElements();

QOpenGLWidget::showEvent(event);
}

void WLVisualWidget::resizeEvent(QResizeEvent *event)
{
Q_UNUSED(event)
    placeVisualElements();

QOpenGLWidget::resizeEvent(event);
}

/*

void WLVisualWidget::setEditLine(int il) 
{
//qDebug()<<"setEditLine="<<il;
//if(k<totalKadr) 
//QList<WLElementTraj>  ListTraj=Program->getListTraj();

QMutexLocker locker(&Program->Mutex);

for(int i=0;i<Program->ListTraj.size();i++)
  if(Program->ListTraj[i].iline==il) 
	  {
	  EditElement=Program->ListTraj[i].iline; //а есть лт такой элемент?
	  break;
      }
	
//qDebug("setEditElement=%d",EditElement);

}
*/


void WLVisualWidget::setEditElement(int id)
{
//QList<WLElementTraj>  ListTraj=Program->getListTraj();
qDebug()<<"setEditElement"<<id;

if(EditElement==id) return;

m_Program->Mutex.lock();

if(0<id&&id<m_Program->getElementCount())
  {
  EditElement=id;
  m_Program->setActivElement(EditElement);
  m_Program->Mutex.unlock();

  emit changedEditElement(EditElement);
  }
else
  m_Program->Mutex.unlock();
//for(int i=0;i<EditElements.size();i++)
 // qDebug()<<"EditElement+ "<<EditElements[i];
//QTimer::singleShot(0,this,SLOT(updateGL()));
}



void WLVisualWidget::updateTrajProgram()
{
QMutexLocker locker1(&Mutex);
QMutexLocker locker(&m_Program->Mutex);


//QMutexLocker locker(&Mutex);
/*
if(GLProgramElemnts!=NULL) delete [] GLProgramElemnts;

GLProgramElemnts = new GLuint[Program->ListTraj.size()];

for(int i=0;i<Program->ListTraj.size();i++)
 {
 GLProgramElemnts[i]=Program->ListTraj[i].GLElemnt;
 }
 */
	/*
qDebug()<<"updateTrajProgram()"<<index<<Program->ListTraj.size()<<Program->ListTraj.isEmpty();



QMutexLocker locker1(&Mutex);
QMutexLocker locker(&Program->Mutex);

makeCurrent();

if(index<0) index=Program->ListTraj.size();
if(index>Program->ListTraj.size()) index=0;


if(index==0)
{
qDebug()<<"delete GL Elements";
lastIndexProgram=0;

while(!GLProgramElemntsList.isEmpty())
	glDeleteLists(GLProgramElemntsList.takeFirst(),1);
}
else
if(lastIndexProgram<index)
{
GLProgramElemntsList+=glGenLists(1);

int i;
WL3DPoint Psum(0,0,0);

/*
for(i=0;i<Program->ListTraj.size();i++)
  if(Program->ListTraj[i].GLElemnt==0) 	Program->ListTraj[i].calcGLElement();
*/  
	/*
qDebug()<<"Sizes"<<index<<Program->ListTraj.size();

for(i=0;i<index;i++) //ищем максимальные и минимальные значения точек
	    Psum+=Program->ListTraj[i].midPoint;	 

rotPointProgram=Psum/Program->ListTraj.size();

glNewList(GLProgramElemntsList.last(),GL_COMPILE);

QMatrix4x4 Mrot;
QVector4D P;
bool ok;
float delta=.5;
bool ch_delta=true;



for(i=lastIndexProgram;i<index;i++)
{
if(Program->ListTraj[i].Type==WLElementTraj::nomov) continue;
glLoadName(Program->ListTraj[i].index);
//glLoadName(i);

if(Program->ListTraj[i].isFast())	 glColor3f(1-ch_delta*delta,0,0); else  glColor3f(0,0,1-ch_delta*delta);

ch_delta=!ch_delta;

//qDebug()<<"color="<<(1-ch_delta*delta);

//glLineWidth(1);
glBegin(GL_LINE_STRIP);
glLineWidth(.1); 

QList <WL6DPoint> Points=Program->ListTraj[i].calcPoints();
//if(typeView == HEADHEAD) 
 for(int j=0;j<Points.size();j++)
   {
   glVertex3f(Points[j].x
	         ,Points[j].y
			 ,Points[j].z);
   }
 /*
else
 for(int j=0;j<Points.size();j++)
   {
   Mrot.setColumn(0,QVector4D(1,0,0,0));
   Mrot.setColumn(1,QVector4D(0,1,0,0));
   Mrot.setColumn(2,QVector4D(0,0,1,0));
   Mrot.setColumn(3,QVector4D(0,0,0,1));  

   Mrot.rotate(Points[j].c,0,0,1);
   P=Mrot*(Points[j].to.toV());

   glVertex3f(P.x(),P.y(),P.z());
   }*/
/*
glEnd();

}

glEndList();

lastIndexProgram=index;
}
qDebug()<<"end UpdateTrajProgram";*/
}


/*
if(GLMillElemnts==0) GLMillElemnts=glGenLists(1);

glNewList(GLMillElemnts,GL_COMPILE);
glLineWidth(2);

bool ch_delta=true;
float delta=0.5;

for(i=MillMachine->MillTraj.size()-1;i>=0;i--)
{
//glLoadName(i);
	/*
if(i==0) 
 glColor3f(1,1,1);
 else*//*
if(MillMachine->MillTraj[i].isFast())	
  glColor3f(1-ch_delta*delta,0,0);	 
  else       
  if(MillMachine->MillTraj[i].blsh)	  
	glColor3f(0,1,0);
    else
	  glColor3f(0,0,1-ch_delta*delta);

ch_delta=!ch_delta;
glCallList(MillMachine->MillTraj[i].GLElemnt);
/*
glBegin(GL_LINE_STRIP);
for(int j=0;j<MillMachine->MillTraj[i].Points.size();j++)
   {
   glVertex3f(MillMachine->MillTraj[i].Points[j].x
	         ,MillMachine->MillTraj[i].Points[j].y
			 ,MillMachine->MillTraj[i].Points[j].z);
   }
glEnd();
*//*

glColor3f(0,0.5,0);

/*	
WLDrawArrow(MillMachine->MillTraj[i].endV
           ,MillMachine->MillTraj[i].Points.last().to3D(),0.2);
*//*
}
glEndList();

if(GLlastMillElemnts==0) GLlastMillElemnts=glGenLists(1);

glNewList(GLlastMillElemnts,GL_COMPILE);
glLineWidth(4);

for(i=0;i<MillMachine->lastMillTraj.size();i++)
{
//glLoadName(i);
glColor3f(1,1,1);

//glLineStipple(1,0xAAAA);
//glEnable(GL_LINE_STIPPLE);

 if(MillMachine->lastMillTraj[i].isFast())	
  glColor3f(1,0.6,0.6);	 
  else       
  if(MillMachine->lastMillTraj[i].blsh)	  
	glColor3f(0.6,1,0.6);
    else
	  glColor3f(0.6,0.6,1);


glCallList(MillMachine->lastMillTraj[i].GLElemnt);

/*
glBegin(GL_LINE_STRIP);
for(int j=0;j<MillMachine->lastMillTraj[i].Points.size();j++)
   {
   glVertex3f(MillMachine->lastMillTraj[i].Points[j].x
	         ,MillMachine->lastMillTraj[i].Points[j].y
			 ,MillMachine->lastMillTraj[i].Points[j].z);
   }
glEnd();
*/
//glDisable(GL_LINE_STIPPLE);
/*
glColor3f(0,0.5,0);
}

glEndList();

}*/
