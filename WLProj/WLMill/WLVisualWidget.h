#ifndef WLVISUALWIDGET_H
#define WLVISUALWIDGET_H

#include <QPoint>
#include <QMouseEvent>
#include <QString>
#include <QStringList>
#include <QList>
#include <QMutex>
#include <QThread>
#include <QToolButton>
#include <QQuickWidget>

#include "WLGProgram.h"
#include "WLMillMachine.h"
#include "WL3DPoint.h"
#include "WL6DPoint.h"
#include "WLOpenGL.h"

#define BUFSIZE 128

#define defTrackSize 128
#define toolPointsSize 12

 enum TypeViewModel  {XYZ,GModel};
 enum TypeViewOffest {Model,Tool};


class WLVisualWidget : public WLOpenGL
{
	Q_OBJECT

public:

private:
    TypeViewModel  m_typeView;
    TypeViewOffest m_typeOffset;


//	int manualAxis;

    QToolButton *m_tbCenterView;
    QToolButton *m_tbToolView;
    QToolButton *m_tbGModelView;


    QQuickWidget *qw;

    WLGProgram *m_Program;
	int lastIndexProgram;
    WLMillMachine *m_MillMachine;

    bool m_viewProgramF;
    bool m_viewMillF;
    bool m_viewLimits;
    bool m_viewRotPointF;
    bool m_viewBacklash;
    bool m_zoomDir;

    QTimer *m_timerView;

    int lastSizeSPsize=0;

	QVector<WL3DPoint> ToolPoints;
	QVector<GLubyte>   ToolIndices;

	QVector<WL3DPoint> ArrowPoints;
	
	//GLuint GLTool;
	GLuint GLArrow;

    float m_toolDiametr;
    float m_toolHeight;

     QList<GLuint>  GLProgramElemntsList;

	 GLuint  GLMillElemnts;
	 GLuint  GLlastMillElemnts;
      
	 WL3DPoint rotPointProgram;

     int EditElement;

     QMutex Mutex;

	 int viewSC;

     QList <WL3DPointf> trackTraj;

     QOpenGLShaderProgram progOneColor;
     QOpenGLShaderProgram progTraj;
     QOpenGLShaderProgram progSelect;

     QOpenGLBuffer vGLBufProgram;
     QOpenGLBuffer vGLBufMill;
     QOpenGLBuffer vGLBufTrack;

     QOpenGLBuffer vGLBufHome;
     QOpenGLBuffer iGLBufHome;

     QOpenGLBuffer vGLBufTool;
     QOpenGLBuffer iGLBufTool;

     QOpenGLBuffer vGLBufSC;

     QOpenGLBuffer vGLBufBox;
     QOpenGLBuffer iGLBufBox;
public:
    WLVisualWidget(WLGProgram *_Program,WLMillMachine *m_MillMachine);
	~WLVisualWidget();  
		
    long getEditElement() {return EditElement;}

     void paintGLold();

     void setZoomDir(bool _dir) {m_zoomDir=_dir;}
     bool zoomDir() {return m_zoomDir;}
protected:
  
    void paintGL();
  
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

	void wheelEvent( QWheelEvent * event );
	void keyPressEvent (QKeyEvent * event );

    void initShaders();
    void initGLBuffers();
private:

	void calcPointsTool();
	void calcPointsArrow();

	void showProgramTraj(bool select=false);
    void showMillTraj();
	void showTrackTraj();
    void showRotPoint();

   	void showSC(QString,int f=0);
    void showHome(WLFrame);
	void showLimit();
    void showTool(WL6DPoint showPoint,bool rot=false,float scale=1,QVector3D color=QVector3D(1,1,1));

    void showBox(WL3DPointf P0,WL3DPointf P1,QVector3D color);
    void showBox(WL6DPoint showPoint,float dx,float dy,float dz,QVector3D color);

	void NormalizeRot(int *angel);
	void NormalizeZoom(float *zoom);
     
	bool translate(QString data,long last_kadr=0);

    void createGLListTraj();

    int selectElement(int x,int y);
   //индекс элемента и производить ли переход 
     void WLDrawArrow(WL3DPoint Vec,WL3DPoint O,float s=1); 
	 void WLDrawArrow1(WL3DPoint Vec,WL3DPoint O,float s=1);

   void updatePointRot();
   void updatePointRotAll(float *X,float *Y,float *Z);
public:  
   //bool isCorrect() {/*if(nowTypeWork==Correct) return true; else */return false;};
   ///bool isEdit()    {/*if(nowTypeWork==Edit)    return true; else */return false;};
 //  bool isMovie()   {/*if(nowTypeWork==Movie)   return true; else */return false;};
private:

   bool ShowCorF;

   float rotTool;  
   bool  enRotTool;
   
   QPoint LastMousePos;

   QMatrix4x4 getShowMatrix();

signals:
  // void ChangedEditElement(int i);
   //void ChangediEditElement(int i);
   //void ChangedEditElementLine(int l);
   
   void changedDataElement(int ik,WL3DPoint st,WL3DPoint en,bool g0,float F);

   void changedLength(float);
   void changedEditElement(int);

private slots :
	void  setEnRotTool(bool en) {enRotTool=en;}
    void  resetProgramBuffer() {lastSizeSPsize=0;}
    void  placeVisualElements();
public slots:
		
    void setTypeView(int type)   {m_typeView=(TypeViewModel)type; updateTrajProgram();}
    void setViewCenter();

    void updateTrajProgram();
    //void updateTrajMill(int index=-1);

    void updateRotTool();

	void setViewSC(int _viewSC) {viewSC=_viewSC;}
  //  void buildTraj();


    void setEditElement(int);

    void setToolDiametr(float d);	
	void setToolHeight(float h);	
//	void setManualAxis(int a) {manualAxis=a;}

    void setViewProgram() {m_viewProgramF=!m_viewProgramF;  update();}
    void setViewMill()    {m_viewMillF=!m_viewMillF;        update();}
    void setViewRotPoint(){m_viewRotPointF=!m_viewRotPointF;update();}
    void setViewLimits()  {m_viewLimits=!m_viewLimits;      update();}

    void setViewXYZ()     {m_typeView=XYZ;   trackTraj.clear(); m_Program->setGModel(nullptr);                 setViewCenter();}
    void setViewGModel()  {m_typeView=GModel;trackTraj.clear(); m_Program->setGModel(m_MillMachine->getGModel());setViewCenter();}

    void setViewOffsetModel()     {m_typeOffset=Model;setViewCenter();}
    void setViewOffsetTool()      {m_typeOffset=Tool; setViewCenter();}

    

    // QWidget interface
protected:
   void showEvent(QShowEvent *event);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // WLVISUALWIDGET_H
