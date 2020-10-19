#ifndef WLPOSITIONWIDGET_H
#define WLPOSITIONWIDGET_H

#include <QWidget>
#include <QMenu>

#include "ui_wlpositionwidget.h"

#include "wllabel.h"
#include "wl3dpoint.h"
#include "wleditpoint.h"
#include "wlmillmachine.h"
#include "wlgprogram.h"

class WLPositionWidget : public QWidget
{
	Q_OBJECT

public:
    WLPositionWidget(WLMillMachine *_MillMachine,WLGProgram *_Program,QWidget *parent=0);
	~WLPositionWidget();

	// WLFrame getViewSC() {return MillMachine->GCode.getSC(iSC-1);};

private:
	Ui::WLPositionWidget ui;

	//int iSC;	
    bool disButton;
	
 WLMillMachine *MillMachine;
 WLGProgram  *Program;

signals:
     void changedViewSC(int);
     void changedHomePosition(WLFrame);

private slots:

     void oPBFindDrivePos();
	 void onExGCode();

     void updateEnableMoved(bool);
	 void onPBSetXY0();
	 
     void onPBRotSK();
     void onPBsetG28();
     void onPBgetG28();
	 void onPBsetP0();
	 void onPBsetP1();

     void setPosition(QString nameDrive,float pos,int type);

     void onPBsetX(int type) {onSetDrive("X",type);}
     void onPBsetY(int type) {onSetDrive("Y",type);}
     void onPBsetZ(int type) {onSetDrive("Z",type);}
     void onPBsetA(int type) {onSetDrive("A",type);}
     void onPBsetB(int type) {onSetDrive("B",type);}

     void onSetDrive(QString nameDrive,int type);

public slots:

	void onGoHome();
	 
    void onPBRotSC();

    void setEditDisabled(bool dis)  {disButton=dis;}

    void updatePosition();


};

#endif // WLPOSITIONWIDGET_H
