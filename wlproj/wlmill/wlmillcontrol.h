#ifndef WLMILLCONTROL_H
#define WLMILLCONTROL_H

#include <QWidget>
#include "ui_wlmillcontrol.h"

#include "wlmillmachine.h"
#include "wlgprogram.h"
#include "wledittext.h"
#include "wlenternum.h"
#include "wlmcodesh.h"


class WLMillControl : public QWidget
{
	Q_OBJECT

public:
    WLMillControl(WLMillMachine *_MillMachine,WLGProgram *_Program,QWidget *parent = 0);
   ~WLMillControl();

private:
    Ui::WLMillControl ui;

 WLMillMachine *MillMachine;
 WLGProgram  *Program;

 bool flashOnMachine;

 float m_stepSper;
 float m_stepFper;

protected:
  void keyPressEvent ( QKeyEvent * event );
  void keyReleaseEvent ( QKeyEvent * event );
  void focusInEvent ( QFocusEvent * event );
  void focusOutEvent ( QFocusEvent * event );

private:
	float calcStepMov();
	float calcWhellTurn();
	float calcFtouch();
	
    void  updateChangedPBAxis(QToolButton *tb,QString nameDrive,int rot);

    //void setPercentS(float per);
    //void setPercentF(float per);

	float stepSize[5];
	float turnSize[5];

    QList <float> ListFper;
private slots:


    void onSetSCor();
    void onClearSCorList();

	void onEditOffsetTool();

	void updateTableTools();
    void updateWhellXButton(quint8);

	void updateLabelBaseOffsetTool();
	// void updateLabelS(double data);
    void onTeachAxis();
    void onFindAxis()  {MillMachine->goDriveFind(ui.cbServiceAxis->currentText());}
    void onRFindAxis() {if(MillMachine->getDrive(ui.cbServiceAxis->currentText()))
                               MillMachine->getDrive(ui.cbServiceAxis->currentText())->setTruPosition(false);
                       }

     void updateWhellAxis();

     void onSetF100Per() {ui.sbFper->setValue(100.0);}
     void onSetS100Per() {ui.sbSper->setValue(100.0);}

     //void updateScrollBarF(int);
     //void updateScrollBarS(int);

	 void setSValue();
	 void updateStackedWidget(bool);
	 void updateLabelOnMachine(bool on);

	 void updateLabelBuffer();
     void updateLabelTime();

	 void onSendProgramTraj();

     void onEditScript();
	 void updateRunSrcipt();

	 void updateFSLabel();
     void updateTab();
     //void updateStepMov();
     //void updateSizeWhellTurn();

	 void updateButtonClicked();
	 void updateFeedTouch();

	 void updateLabelInProbe();
	 void updateProbeButtons();

     void onChangedPBPlusX()  {updateChangedPBAxis(ui.pbPlusX,"X",1);}
     void onChangedPBMinusX() {updateChangedPBAxis(ui.pbMinusX,"X",-1);}
     void onChangedPBPlusY()  {updateChangedPBAxis(ui.pbPlusY,"Y",1);}
     void onChangedPBMinusY() {updateChangedPBAxis(ui.pbMinusY,"Y",-1);}
     void onChangedPBPlusZ()  {updateChangedPBAxis(ui.pbPlusZ,"Z",1);}
     void onChangedPBMinusZ() {updateChangedPBAxis(ui.pbMinusZ,"Z",-1);}
     void onChangedPBPlusA()  {updateChangedPBAxis(ui.pbPlusA,"A",1);}
     void onChangedPBMinusA() {updateChangedPBAxis(ui.pbMinusA,"A",-1);}

     void onSetChangedTable();
     void onAcceptTableTools();


     void on_pbGetMSLimit_clicked();
     void on_pbGetPSLimit_clicked();

    void on_pbStopTouch_pressed();

     void on_pbMinusFman_pressed();
     void on_pbPlusFman_pressed();

     void on_pbMinusF_clicked();

     void on_pbPlusF_clicked();

     void on_pbMinusS_clicked();

     void on_pbPlusS_clicked();

     void on_sbFman_valueChanged(double arg1);

     void on_pbFast_pressed();

     void on_pbFast_released();

public slots:
		 

	 //void onPBY();
	 //void onPBZ();

	// void calcKF(int);
	 //void calcKS(int);
};

#endif // WLMILLCONTROL_H
