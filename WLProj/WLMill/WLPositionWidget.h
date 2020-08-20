#ifndef WLPOSITIONWIDGET_H
#define WLPOSITIONWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QtQuick>

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

	 void onExGCode();

     void updateEnableMoved(bool);
	 void onPBSetXY0();
	 
     void onPBRotSK();
	 void onPBsetHome();
     void onPBgetHome();
	 void onPBsetP0();
	 void onPBsetP1();

     void setPosition(QString nameDrive,float pos,int type);

     void onPBsetX(int type) {onSetDrive("X",type);}
     void onPBsetY(int type) {onSetDrive("Y",type);}
     void onPBsetZ(int type) {onSetDrive("Z",type);}
     void onPBsetA(int type) {onSetDrive("A",type);}
     void onPBsetB(int type) {onSetDrive("B",type);}

	 void onPBGoTo();

     void onSetDrive(QString nameDrive,int type);

public slots:

	void onGoHome();

   // void onFindX() {MillMachine->goDriveFind("X");}
   // void onFindY() {MillMachine->goDriveFind("Y");}
   // void onFindZ() {MillMachine->goDriveFind("Z");}
   // void onFindA() {MillMachine->goDriveFind("A");}
   // void onFindB() {MillMachine->goDriveFind("B");}
	 
    void onPBRotSC();

	void setEditDisabled(bool dis) 
	                             
	                            {
								 disButton=dis;
                                // setViewSC(iSC);
								// PBsetHome->setDisabled(dis);
                                // PBgetHome->setDisabled(dis);
                                 }

	 void updatePosition();
     void setViewSC(int index)  {
                                Q_UNUSED(index)
                               // MillMachine->GCode.setGCode("G"+QString::number(53+index));
                                /*
		                        iSC=index;
	                            updatePosition(); 
	                            //qDebug()<<"iSC"<<iSC;
								ui.pbRotSK->setDisabled(iSC<2||disButton);
								ui.pbSetP0->setDisabled(iSC<2||disButton);
								ui.pbSetP1->setDisabled(iSC<2||disButton);
								 

	                            //PBsetX->setDisabled(iSC<=1||disButton); 
								//PBsetY->setDisabled(iSC<=1||disButton); 
								//PBsetZ->setDisabled(iSC<=1||disButton); 

                                if(iSC>0) emit ChangedViewSC(iSC-1);
                                */
	                            }

};

#endif // WLPOSITIONWIDGET_H
