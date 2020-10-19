#include "wlpositionwidget.h"

WLPositionWidget::WLPositionWidget(WLMillMachine *_MillMachine,WLGProgram *_Program,QWidget *parent)
	: QWidget(parent)
{
	MillMachine=_MillMachine;
    Program=_Program;

	disButton=false;

	ui.setupUi(this);


	QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePosition()));
    timer->start(100);

    ui.gALabelX->setDrive(MillMachine->getDrive("X"));
    ui.gALabelY->setDrive(MillMachine->getDrive("Y"));
    ui.gALabelZ->setDrive(MillMachine->getDrive("Z"));
    ui.gALabelA->setDrive(MillMachine->getDrive("A"));
    ui.gALabelB->setDrive(MillMachine->getDrive("B"));

    ui.gALabelX->setGCode(MillMachine->GCode());
    ui.gALabelY->setGCode(MillMachine->GCode());
    ui.gALabelZ->setGCode(MillMachine->GCode());
    ui.gALabelA->setGCode(MillMachine->GCode());
    ui.gALabelB->setGCode(MillMachine->GCode());

    connect(ui.gALabelX,SIGNAL(changedPress(QString,int)),this,SLOT(onSetDrive(QString,int)));
    connect(ui.gALabelY,SIGNAL(changedPress(QString,int)),this,SLOT(onSetDrive(QString,int)));
    connect(ui.gALabelZ,SIGNAL(changedPress(QString,int)),this,SLOT(onSetDrive(QString,int)));
    connect(ui.gALabelA,SIGNAL(changedPress(QString,int)),this,SLOT(onSetDrive(QString,int)));
    connect(ui.gALabelB,SIGNAL(changedPress(QString,int)),this,SLOT(onSetDrive(QString,int)));
/*
    ui.qwAxisLabelPosX->rootObject()->setProperty("p_name","X:");
    ui.qwAxisLabelPosY->rootObject()->setProperty("p_name","Y:");
    ui.qwAxisLabelPosZ->rootObject()->setProperty("p_name","Z:");
    ui.qwAxisLabelPosA->rootObject()->setProperty("p_name","A:");
    ui.qwAxisLabelPosB->rootObject()->setProperty("p_name","B:");
    */
	connect(ui.pbOnMachine,SIGNAL(toggled(bool)),MillMachine,SLOT(setOn(bool)));

    ui.pbG28->setPopupMode(QToolButton::DelayedPopup);
    connect(ui.pbG28,SIGNAL(clicked()),SLOT(onGoHome()));
	
    QMenu *menuPBG28 = new QMenu();
    menuPBG28->addAction((tr("set G28 position")),this,SLOT(onPBsetG28()));
    menuPBG28->addAction((tr("get G28 position")),this,SLOT(onPBgetG28()));
    ui.pbG28->setMenu(menuPBG28);
		
	ui.pbRotSC->setPopupMode(QToolButton::DelayedPopup);
    connect(ui.pbRotSC,SIGNAL(clicked()),SLOT(onPBRotSC()));

	QMenu *menuPBRot = new QMenu();
	menuPBRot->addAction((tr("set base postion")),this,SLOT(onPBsetP0()));
	menuPBRot->addAction((tr("set verify postion")),this,SLOT(onPBsetP1()));
	menuPBRot->addAction((tr("rotation correction")),this,SLOT(onPBRotSK()));
    ui.pbRotSC->setMenu(menuPBRot);	
/*
    connect(ui.qwAxisLabelPosX->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetX(int)));
    connect(ui.qwAxisLabelPosY->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetY(int)));
*/
    connect(ui.cbExGCode->lineEdit(),SIGNAL(returnPressed()),this,SLOT(onExGCode()));

    connect(ui.pbFindDrivePos,SIGNAL(clicked()),this,SLOT(oPBFindDrivePos()));

    connect(ui.pbReset,SIGNAL(clicked()),MillMachine,SLOT(reset()),Qt::DirectConnection);

    connect(MillMachine,SIGNAL(changedReadyRunList(bool)),SLOT(updateEnableMoved(bool)));

/*
    if(!MillMachine->getDrive("Z"))
        {
        ui.qwAxisLabelPosZ->setVisible(false);
        }
    else {
          connect(ui.qwAxisLabelPosZ->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetZ(int)));
         }

    if(!MillMachine->getDrive("A"))
        {
        ui.qwAxisLabelPosA->setVisible(false);
        }
    else {
         connect(ui.qwAxisLabelPosA->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetA(int)));
         }

    if(!MillMachine->getDrive("B"))
        {
        ui.qwAxisLabelPosB->setVisible(false);
        }
    else {
         connect(ui.qwAxisLabelPosB->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetB(int)));
         }
*/
    ui.cbExGCode->setToolTip(
                 tr(
                "<b>GCode:</font></b>"
                "<ol>"
                  "<li>G0,G1</li>"
                  "<li>G2,G3 (I,J,K,R) </li>"
                  "<li>G17,G18,G19</li>"
                  "<li>G28(home)</li>"
                  "<li>G51(XYZ scale)</li>"
                  "<li>G53(no modal)</li>"
                  "<li>G54-G59</li>"
                  "<li>G80,G81,G83(Z,R,Q)</li>"
                  "<li>G90,G91</li>"
                "</ol>"
                  )
                );
}

WLPositionWidget::~WLPositionWidget()
{

}

void WLPositionWidget::oPBFindDrivePos()
{
MillMachine->goFindDrivePos();
}

void WLPositionWidget::onExGCode()
{
MillMachine->runGCode(ui.cbExGCode->currentText());
}

void WLPositionWidget::onGoHome()
{
MillMachine->runGCode("G28 Z0");
MillMachine->runGCode("G28 X0 Y0");
MillMachine->runGCode("G28 A0 B0 C0");
}


void WLPositionWidget::onPBSetXY0()
{
setPosition("X",0,0);
setPosition("Y",0,0);
}

void WLPositionWidget::onPBRotSK()
{
WL3DPoint refP0(MillMachine->m_GCode.getRefPoint0SC(MillMachine->m_GCode.getActivSC()).to3D());
WL3DPoint curPos(MillMachine->getCurrentPositionActivSC().to3D());
WL3DPoint refP1(MillMachine->m_GCode.getRefPoint1SC(MillMachine->m_GCode.getActivSC()).to3D());

curPos.z=0;

double a=(curPos.getAxy(refP0)-refP1.getAxy(refP0))*180.0/M_PI;

qDebug()<<"calc A"<<a;

MillMachine->rotAboutRotPointSC(MillMachine->m_GCode.getActivSC()
                               ,MillMachine->m_GCode.getRefPoint0SC(MillMachine->m_GCode.getActivSC()).a+a);



}

void WLPositionWidget::updateEnableMoved(bool en)
{
disButton=en;

ui.pbG28->setDisabled(en);
ui.pbFindDrivePos->setDisabled(en);
ui.pbRotSC->setDisabled(en);

if(MillMachine->isRunProgram())
    ui.cbExGCode->setDisabled(en);
else
    ui.cbExGCode->setDisabled(false);

}

void WLPositionWidget::updatePosition()
{
WLGPoint GP;
WLGPoint GP53;


GP53=MillMachine->getAxisPosition();
GP=MillMachine->getCurrentPositionActivSC();

QPalette blckPalette,redPalette;

blckPalette.setColor(QPalette::WindowText, Qt::black);
 redPalette.setColor(QPalette::WindowText, Qt::red);
/*
ui.qwAxisLabelPosX->rootObject()->setProperty("p_data53",QString("%1").arg((GP53.x),0,'f',2));
ui.qwAxisLabelPosY->rootObject()->setProperty("p_data53",QString("%1").arg((GP53.y),0,'f',2));

ui.qwAxisLabelPosX->rootObject()->setProperty("p_data",QString("%1").arg((GP.x),0,'f',2));
ui.qwAxisLabelPosY->rootObject()->setProperty("p_data",QString("%1").arg((GP.y),0,'f',2));

ui.qwAxisLabelPosX->rootObject()->setProperty("p_feed",QString("%1").arg((MillMachine->getDrive("X")->Vnow()*60),0,'f',0));
ui.qwAxisLabelPosY->rootObject()->setProperty("p_feed",QString("%1").arg((MillMachine->getDrive("Y")->Vnow()*60),0,'f',0));

ui.qwAxisLabelPosX->rootObject()->setProperty("p_color",MillMachine->getDrive("X")->isTruPosition()?"black":"red");
ui.qwAxisLabelPosY->rootObject()->setProperty("p_color",MillMachine->getDrive("Y")->isTruPosition()?"black":"red");

if(ui.qwAxisLabelPosZ->isVisible())
{
ui.qwAxisLabelPosZ->rootObject()->setProperty("p_color",MillMachine->getDrive("Z")->isTruPosition()?"black":"red");
ui.qwAxisLabelPosZ->rootObject()->setProperty("p_data",QString("%1").arg((GP.z),0,'f',2));
ui.qwAxisLabelPosZ->rootObject()->setProperty("p_data53",QString("%1").arg((GP53.z),0,'f',2));
ui.qwAxisLabelPosZ->rootObject()->setProperty("p_feed",QString("%1").arg(MillMachine->getDrive("Z")->Vnow()*60,0,'f',0));

}

if(ui.qwAxisLabelPosA->isVisible())
{
ui.qwAxisLabelPosA->rootObject()->setProperty("p_color",MillMachine->getDrive("A")->isTruPosition()?"black":"red");
ui.qwAxisLabelPosA->rootObject()->setProperty("p_data",QString("%1").arg((GP.a),0,'f',2));
ui.qwAxisLabelPosA->rootObject()->setProperty("p_data53",QString("%1").arg((GP53.a),0,'f',2));
ui.qwAxisLabelPosA->rootObject()->setProperty("p_feed",QString("%1").arg(MillMachine->getDrive("A")->Vnow()*60,0,'f',0));

}

if(ui.qwAxisLabelPosB->isVisible())
{
ui.qwAxisLabelPosB->rootObject()->setProperty("p_color",MillMachine->getDrive("B")->isTruPosition()?"black":"red");
ui.qwAxisLabelPosB->rootObject()->setProperty("p_data",QString("%1").arg((GP.b),0,'f',2));
ui.qwAxisLabelPosB->rootObject()->setProperty("p_data53",QString("%1").arg((GP53.b),0,'f',2));
ui.qwAxisLabelPosB->rootObject()->setProperty("p_feed",QString("%1").arg(MillMachine->getDrive("B")->Vnow()*60,0,'f',0));

}*/

ui.gALabelX->update();
ui.gALabelY->update();
ui.gALabelZ->update();
ui.gALabelA->update();
ui.gALabelB->update();

ui.rotSK->setData(MillMachine->m_GCode.getRefPoint0SC(MillMachine->m_GCode.getActivSC()).a);


ui.labelActivGCode->setText(MillMachine->m_GCode.getActivGCodeString());


if(MillMachine->m_motDevice->getModuleConnect())
 ui.labelConnect->setEnabled(MillMachine->m_motDevice->getModuleConnect()->isConnect());
else
 ui.labelConnect->setEnabled(false);

#ifdef DEF_5D
P=MillMachine->getCurrentPosition();
AG5X->setData(P.a,3 );
BG5X->setData(P.b,3 );
CG5X->setData(P.c,3 );
#endif
#ifdef MILLKUKA
WL6EPos EPos =MillMachine->Kuka->getPosition6EPos();
E1->setData(EPos.e1.pos,5);
#endif
}

void WLPositionWidget::onSetDrive(QString nameDrive,int type)
{
if(disButton) return;

if(type==WLGAxisLabel::typeName)
 {
 return;
 }

WLEnterNum  EnterNum (this);

EnterNum.setLabel(nameDrive+"=");


if(EnterNum.exec())  setPosition(nameDrive,EnterNum.getNow(),type);
}


void WLPositionWidget::setPosition(QString nameDrive,float pos,int type)
{
switch(type)
{
case WLGAxisLabel::typeOfst:  MillMachine->setCurPositionSC(nameDrive,pos);
                              break;
case WLGAxisLabel::typePos:   MillMachine->getDrive(nameDrive)->setPosition(pos);
                              break;
}

}

void WLPositionWidget::onPBRotSC()
{
if(disButton) return;

WLEnterNum  EnterNum (this);
EnterNum.setLabel("A=");
EnterNum.setSuffix(tr("gr"));

if(EnterNum.exec())  
 {
 MillMachine->rotAboutRotPointSC(MillMachine->m_GCode.getActivSC(),EnterNum.getNow());
 }

}







void WLPositionWidget::onPBsetP0()
{
WLEditPoint EP;

WLGPoint  GP=MillMachine->m_GCode.getRefPoint0SC(MillMachine->m_GCode.getActivSC(),0);

EP.setNameData("X,Y,Z");
EP.setValueStr(GP.toString());

EP.show();

if(EP.exec())
    {
    qDebug("update rotPoint");
    GP.fromString(EP.getValueStr());
    MillMachine->m_GCode.setRefPoint0SC(MillMachine->m_GCode.getActivSC(),GP);
    }
};

void WLPositionWidget::onPBsetP1()
{
WLEditPoint EP;

WLGPoint  GP=MillMachine->m_GCode.getRefPoint1SC(MillMachine->m_GCode.getActivSC());

EP.setNameData("X,Y,Z");
EP.setValueStr(GP.toString());

EP.show();

if(EP.exec())
    {
    qDebug("update rotPoint");
    GP.fromString(EP.getValueStr());
    MillMachine->m_GCode.setRefPoint1SC(MillMachine->m_GCode.getActivSC(),GP);
    }
};

void WLPositionWidget::onPBsetG28()
{
WLGPoint GP;
WLEditPoint EP;
QString nameDrive;

EP.setNameData("X,Y,Z,A,B,C");

QList <double> List;

GP=MillMachine->m_GCode.getG28Position();


EP.setLabel(tr("enter G28 position"));

EP.setValueStr(GP.toString());

EP.show();

if(EP.exec())
    {
    GP.fromString(EP.getValueStr());
    MillMachine->m_GCode.setG28Position(GP);
    }
	///emit ChangedHomePosition(Program->GCode.getSC(iSC-1).toM()*EP.getFrame().toM());

}

void WLPositionWidget::onPBgetG28()
{
if(QMessageBox::question(this, tr("Question:"),tr("are you sure?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
                   MillMachine->m_GCode.setG28Position(MillMachine->getCurrentPosition(1));
}
