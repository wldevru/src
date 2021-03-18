#ifndef WLPOSITIONWIDGET_H
#define WLPOSITIONWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QLayout>
#include <QButtonGroup>
#include <QTime>
#include <QSplitter>

#include "ui_wlpositionwidget.h"

#include "wllabel.h"
#include "wl3dpoint.h"
#include "wleditpoint.h"
#include "wlmillmachine.h"
#include "wlgprogram.h"
#include "wlelementcontrol.h"
#include "wlgaxislabel.h"

class WLPositionWidget : public QWidget
{
	Q_OBJECT

public:
    WLPositionWidget(WLMillMachine *_MillMachine,WLGProgram *_Program,QWidget *parent=0);
	~WLPositionWidget();

	// WLFrame getViewSC() {return MillMachine->GCode.getSC(iSC-1);};
 void setJogDistStr(QString);
 void setFperStr(QString);

private:
	Ui::WLPositionWidget ui;

	//int iSC;	
    bool disButton;
	
 WLMillMachine *MillMachine;
 WLGProgram  *Program;

 char focusElement='F';


signals:
     void changedViewSC(int);
     void changedHomePosition(WLFrame);
     void chnagedGPos(QString name,double pos);

private:
   WLGAxisLabel  *gALabelX=nullptr;
   WLGAxisLabel  *gALabelY=nullptr;
   WLGAxisLabel  *gALabelZ=nullptr;
   WLGAxisLabel  *gALabelA=nullptr;
   WLGAxisLabel  *gALabelB=nullptr;
   WLGAxisLabel  *gALabelC=nullptr;

   QToolButton *pbMinusX;
   QToolButton *pbMinusY;
   QToolButton *pbMinusZ;

   QToolButton *pbPlusX;
   QToolButton *pbPlusY;
   QToolButton *pbPlusZ;

   QList <QToolButton*> TBPDriveList;
   QList <QToolButton*> TBMDriveList;

   WLLabel *labelS;
   WLLabel *labelF;
   QLabel  *labelActivGCode;

   QDoubleSpinBox *sbFper;
   QDoubleSpinBox *sbFman;
   QDoubleSpinBox *sbSper;

   QToolButton *pbFast;
   QToolButton *pbPause;

   QLabel *labelTypeManual;

   float m_stepSper=2.5;
   float m_stepFper=2.5;

   QList <float> m_listFper;
   QStringList m_listManDist;
   int m_curIndexListMan=0;

   QSize m_buttonSize;

private:

    void initElementControls();
    float calcStepMov();

    void setFocusElement(char f);

    void onTeachAxis(QString name);

    // QWidget interface
protected:

  void keyPressEvent ( QKeyEvent * event );
  void keyReleaseEvent ( QKeyEvent * event );
  void focusOutEvent ( QFocusEvent * event );
  void mousePressEvent(QMouseEvent *event);

private slots: 

     void updateProgress();
     void updateOnButton();

     void onSetSCor();
     void onClearSCorList();

     void on_pbFast_pressed();
     void on_pbFast_released();

     void on_pbPlusSper_pressed()  {sbSper->setValue(sbSper->value()+m_stepSper);}
     void on_pbMinusSper_pressed() {sbSper->setValue(sbSper->value()-m_stepSper);}

     void on_pbPlusFper_pressed()  {sbFper->setValue(sbFper->value()+m_stepFper);}
     void on_pbMinusFper_pressed() {sbFper->setValue(sbFper->value()-m_stepFper);}


     void on_pbPlusFman_pressed();
     void on_pbMinusFman_pressed();

     void on_pbPlus_pressed();
     void on_pbMinus_pressed();

     void onPBAxis(QString name,int rot,bool press);

     void updateFSLabel();

     void onExGCode();

     void updateEnableMoved(bool);
	 void onPBSetXY0();
	 
     void onPBRotSK();
     void onPBsetG28();
     void onPBgetG28();
	 void onPBsetP0();
	 void onPBsetP1();

     void setPosition(QString nameDrive,float pos,int type);

     void onPBsetX(int type) {onPushDrive("X",type);}
     void onPBsetY(int type) {onPushDrive("Y",type);}
     void onPBsetZ(int type) {onPushDrive("Z",type);}
     void onPBsetA(int type) {onPushDrive("A",type);}
     void onPBsetB(int type) {onPushDrive("B",type);}

     void onPushDrive(QString nameDrive,int type);

public slots:

	void onGoHome();
	 
    void onPBRotSC();

    void setEditDisabled(bool dis)  {disButton=dis;}

    void updatePosition();


};


#endif // WLPOSITIONWIDGET_H
