#include "wlpositionwidget.h"

WLPositionWidget::WLPositionWidget(WLMillMachine *_MillMachine,WLGProgram *_Program,QWidget *parent)
	: QWidget(parent)
{
	MillMachine=_MillMachine;
    Program=_Program;
	//iSC=0;
	disButton=false;

	ui.setupUi(this);

//	ui.cbSK->addItems(QString(tr("Axis,Base")).split(","));

	QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(updatePosition()));
    timer->start(100);

//	connect(ui.pbFindX,SIGNAL(clicked()),SLOT(onFindX()));
//	connect(ui.pbFindY,SIGNAL(clicked()),SLOT(onFindY()));
    /*
	connect(ui.pbFindZ,SIGNAL(clicked()),SLOT(onFindZ()));	
    connect(ui.pbFindA,SIGNAL(clicked()),SLOT(onFindA()));
    connect(ui.pbFindB,SIGNAL(clicked()),SLOT(onFindB()));
*/
    //ui.XG5X->setPrefix("X:");
    //ui.YG5X->setPrefix("Y:");
    //ui.ZG5X->setPrefix("Z:");
    //ui.AG5X->setPrefix("A:");
    //ui.BG5X->setPrefix("B:");

    ui.qwAxisLabelPosX->rootObject()->setProperty("p_name","X:");
    ui.qwAxisLabelPosY->rootObject()->setProperty("p_name","Y:");
    ui.qwAxisLabelPosZ->rootObject()->setProperty("p_name","Z:");
    ui.qwAxisLabelPosA->rootObject()->setProperty("p_name","A:");
    ui.qwAxisLabelPosB->rootObject()->setProperty("p_name","B:");

//	connect(ui.cbSK,SIGNAL(currentIndexChanged(int)),this,SLOT(setViewSC(int)));
//	ui.cbSK->setCurrentIndex(1);
	//setViewSC(2);
	connect(ui.pbOnMachine,SIGNAL(toggled(bool)),MillMachine,SLOT(setOn(bool)));
    ui.pbOnMachine->setIcon(QIcon(":/data/icons/power_on.png"));

    ui.pbHome->setIcon(QIcon(":/data/icons/home.png"));
    ui.pbHome->setPopupMode(QToolButton::DelayedPopup);
	connect(ui.pbHome,SIGNAL(clicked()),SLOT(onGoHome()));
	
	QMenu *menuPBHome = new QMenu();
    menuPBHome->addAction((tr("set home")),this,SLOT(onPBsetHome()));
    menuPBHome->addAction((tr("get home")),this,SLOT(onPBgetHome()));
    ui.pbHome->setMenu(menuPBHome);	
		
    ui.pbRotSC->setIcon(QIcon(":/data/icons/rot.png"));
	ui.pbRotSC->setPopupMode(QToolButton::DelayedPopup);
    connect(ui.pbRotSC,SIGNAL(clicked()),SLOT(onPBRotSC()));

	QMenu *menuPBRot = new QMenu();
	menuPBRot->addAction((tr("set base postion")),this,SLOT(onPBsetP0()));
	menuPBRot->addAction((tr("set verify postion")),this,SLOT(onPBsetP1()));
	menuPBRot->addAction((tr("rotation correction")),this,SLOT(onPBRotSK()));
    ui.pbRotSC->setMenu(menuPBRot);	

    connect(ui.qwAxisLabelPosX->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetX(int)));
    connect(ui.qwAxisLabelPosY->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetY(int)));
    //connect(ui.qwAxisLabelPosZ->rootObject(),SIGNAL(qmlSignalClick()),this,SLOT(onPBsetZ()));
   // connect(ui.qwAxisLabelPosA->rootObject(),SIGNAL(qmlSignalClick()),this,SLOT(onPBsetA()));
   // connect(ui.qwAxisLabelPosB->rootObject(),SIGNAL(qmlSignalClick()),this,SLOT(onPBsetB()));
/*
    connect(ui.XG5X,SIGNAL(Clicked()),this,SLOT(onPBsetX()));
    connect(ui.YG5X,SIGNAL(Clicked()),this,SLOT(onPBsetY()));
    connect(ui.ZG5X,SIGNAL(Clicked()),this,SLOT(onPBsetZ()));
    connect(ui.AG5X,SIGNAL(Clicked()),this,SLOT(onPBsetA()));
    connect(ui.BG5X,SIGNAL(Clicked()),this,SLOT(onPBsetB()));
*/
	//connect(ui.pbSetHome,SIGNAL(clicked()),this,SLOT(onPBsetHome()));
    //connect(ui.pbSetP0,SIGNAL(clicked()),this,SLOT(onPBsetP0()));
    //connect(ui.pbSetP1,SIGNAL(clicked()),this,SLOT(onPBsetP1()));
    //connect(ui.pbRotSK,SIGNAL(clicked()),this,SLOT(onPBRotSK()));
//	connect(ui.pbSetXY0,SIGNAL(clicked()),this,SLOT(onPBSetXY0()));

//	connect(ui.pbGoTo,SIGNAL(clicked()),this,SLOT(onPBGoTo()));	

//  connect(ui.pbGExec,SIGNAL(clicked()),this,SLOT(onExGCode()));
//	connect(ui.pbGoHome,SIGNAL(clicked()),this,SLOT(onGoHome()));
    connect(ui.cbExGCode->lineEdit(),SIGNAL(returnPressed()),this,SLOT(onExGCode()));

    //connect(ui.pbReset,SIGNAL(clicked()),MillMachine->EVMScript,SLOT(reset()),Qt::DirectConnection);
    connect(ui.pbReset,SIGNAL(clicked()),MillMachine,SLOT(reset()),Qt::DirectConnection);

    //connect(MillMachine->EVMScript,SIGNAL(changedBusy(bool)),ui.pbResetScript,SLOT(setEnabled(bool)));

    connect(MillMachine,SIGNAL(changedReadyRunList(bool)),SLOT(updateEnableMoved(bool)));

    ui.labelConnect->setPixmap(QPixmap(":/data/icons/iong.png"));

    if(!MillMachine->getDrive("Z"))
        {
        ui.qwAxisLabelPosZ->setVisible(false);
   //     ui.pbFindZ->setVisible(false);
        //ui.ZG5X->deleteLater();     ui.ZG5X=nullptr;
       // ui.qwAxisLabelPosZ->deleteLater();     ui.qwAxisLabelPosZ=nullptr;
       // ui.pbFindZ->deleteLater();  ui.pbFindZ=nullptr;

        }
    else {
        //connect(ui.pbFindZ,SIGNAL(clicked()),SLOT(onFindZ()));
        //connect(ui.ZG5X,SIGNAL(Clicked()),this,SLOT(onPBsetZ()));
        connect(ui.qwAxisLabelPosZ->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetZ(int)));
        }

    if(!MillMachine->getDrive("A"))
        {
     //   ui.AG5X->deleteLater();     ui.AG5X=nullptr;
      //   ui.qwAxisLabelPosA->deleteLater();     ui.qwAxisLabelPosA=nullptr;
      //  ui.pbFindA->deleteLater();  ui.pbFindA=nullptr;
        ui.qwAxisLabelPosA->setVisible(false);
   //     ui.pbFindA->setVisible(false);
        }
    else{
   //     connect(ui.pbFindA,SIGNAL(clicked()),SLOT(onFindA()));
   //     connect(ui.AG5X,SIGNAL(Clicked()),this,SLOT(onPBsetA()));
         connect(ui.qwAxisLabelPosA->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetA(int)));
    }

    if(!MillMachine->getDrive("B"))
        {
        //ui.BG5X->deleteLater();     ui.BG5X=nullptr;
        //ui.qwAxisLabelPosB->deleteLater();     ui.qwAxisLabelPosB=nullptr;
        //ui.pbFindB->deleteLater();  ui.pbFindB=nullptr;
        ui.qwAxisLabelPosB->setVisible(false);
    //    ui.pbFindB->setVisible(false);
        }
    else {
    //     connect(ui.pbFindB,SIGNAL(clicked()),SLOT(onFindB()));
        // connect(ui.BG5X,SIGNAL(Clicked()),this,SLOT(onPBsetB()));
         connect(ui.qwAxisLabelPosB->rootObject(),SIGNAL(qmlSignalClick(int)),this,SLOT(onPBsetB(int)));
    }

    ui.cbExGCode->setToolTip(
                 tr(
                "<b>GCode:</font></b>"
                "<ol>"
                  "<li>G0,G1</li>"
                  "<li>G2,G3 (I,J,K,R) </li>"
                  "<li>G17,G18,G19</li>"
                  "<li>G28(home)</li>"
                  "<li>G51(XYZ)</li>"
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

void WLPositionWidget::onExGCode()
{
//ui.cbExGCode->insertItem(0,ui.cbExGCode->currentText());
MillMachine->runGCode(ui.cbExGCode->currentText());
}

void WLPositionWidget::onGoHome()
{
//MillMachine->runScript("goHome()");

MillMachine->runGCode("G28 Z0");
MillMachine->runGCode("G28 X0 Y0");
MillMachine->runGCode("G28 A0 B0 C0");
}

void WLPositionWidget::onPBGoTo()
{
	/*
WLDialogToPoint Dial(this);
#ifdef DEF_5D
Dial.setNowPoint(MillMachine->getCurrentPosition().to3D());
#else
WLFrame Cp=MillMachine->getCurrentPosition();
Cp.fromM(MillMachine->GCode.getSC(iSC-1).toM().inverted()*Cp.toM());

Dial.setNowPoint(Cp.to3D());
#endif

Dial.setNowF(200);
Dial.setModal(true);
Dial.show();

if(Dial.exec())
 {
 qDebug()<<"Ok";

 WLElementTraj ME;
 WLFrame Fr;
 WL3DPoint P;
 QList <WLElementTraj> LME;
 bool ok=false;
 if(!Dial.isGoHome())
	 {
	 Fr=MillMachine->GCode.getSC(iSC-1);
	 WLFrame P(Dial.getPoint());

     if(Dial.isRelative())
		Fr.fromM(Fr.toM()*P.toM()*Cp.toM());
	 else		   
	   Fr.fromM(Fr.toM()*P.toM());	   

	 ME.setLineXYZ(MillMachine->getCurrentPosition(),Fr.to6D());

     if(ok)
	  {
      if(Dial.isFast())	 ME.setFast();    else 	   ME.setF(Dial.getF());

      LME+=ME;

      MillMachine->setElementTraj(LME);
	  }
	 else
	  qDebug()<<"err";
     }
 else
   {

   QList<WLElementTraj> Traj;
   WLElementTraj ME;

   #ifdef MILLKUKA
   WL3DPoint CP=MillMachine->getCurrentPosition().to3D();
   #else
   WL6DPoint CP=MillMachine->getCurrentPosition();
   #endif

   bool ok;
   WL6DPoint bP=CP;
   bP.z=MillMachine->GCode.getHomePosition().z;

   ME.setLineXYZ(bP,MillMachine->GCode.getHomePosition().to6D());
   ME.setFast();
   Traj.prepend(ME);

   ME.setLineXYZ(CP,Traj.first().startPoint.to3D());
   ME.setFast();
   Traj.prepend(ME);
   
   qDebug()<<"Traj size="<<Traj.size();

   MillMachine->setElementTraj(Traj);
   }
 
 }*/
}

void WLPositionWidget::onPBSetXY0()
{
setPosition("X",0,0);
setPosition("Y",0,0);
}

void WLPositionWidget::onPBRotSK()
{
//if(ui.cbSK->currentIndex()==1)
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
}

void WLPositionWidget::updateEnableMoved(bool en)
{
disButton=en;

//ui.pbFindX->setDisabled(en);
//ui.pbFindY->setDisabled(en);

//if(ui.pbFindZ) ui.pbFindZ->setDisabled(en);
//if(ui.pbFindA) ui.pbFindA->setDisabled(en);
//if(ui.pbFindB) ui.pbFindB->setDisabled(en);


ui.pbHome->setDisabled(en);
ui.pbRotSC->setDisabled(en);
//ui.pbSetP0->setDisabled(en);
//ui.pbSetP1->setDisabled(en);
if(MillMachine->isRunProgram())
    ui.cbExGCode->setDisabled(en);
else
    ui.cbExGCode->setDisabled(false);
//ui.pbGExec->setDisabled(en);
//ui.pbSetXY0->setDisabled(en);
//ui.pbGoTo->setDisabled(en);
}

void WLPositionWidget::updatePosition()
{
WLGPoint GP;
WLGPoint GP53;
//WLGPoint GP54;

GP53=MillMachine->getAxisPosition();
GP=MillMachine->getCurrentPositionActivSC();
/*
switch(ui.cbSK->currentIndex())
{
case 0:  GP=MillMachine->getAxisPosition();break;
//case 1:P=MillMachine->getCurrentPosition();break;

default: GP=MillMachine->getCurrentPositionActivSC();break;
		// qDebug()<<"SC"<<Program->GCode.getOffsetSC(iSC-1).toString();
}

*/
/*
ui.XG5X->setFrameShadow(MillMachine->getDrive("X")->isTruPosition()?QFrame::Plain:QFrame::Sunken);
ui.YG5X->setFrameShadow(MillMachine->getDrive("Y")->isTruPosition()?QFrame::Plain:QFrame::Sunken);

if(ui.ZG5X)
    ui.ZG5X->setFrameShadow(MillMachine->getDrive("Z")->isTruPosition()?QFrame::Plain:QFrame::Sunken);
if(ui.AG5X)
    ui.AG5X->setFrameShadow(MillMachine->getDrive("A")->isTruPosition()?QFrame::Plain:QFrame::Sunken);
if(ui.BG5X)
    ui.BG5X->setFrameShadow(MillMachine->getDrive("B")->isTruPosition()?QFrame::Plain:QFrame::Sunken);
*/


QPalette blckPalette,redPalette;

blckPalette.setColor(QPalette::WindowText, Qt::black);
 redPalette.setColor(QPalette::WindowText, Qt::red);

ui.qwAxisLabelPosX->rootObject()->setProperty("p_data53",QString("%1").arg((GP53.x),0,'f',2));
ui.qwAxisLabelPosY->rootObject()->setProperty("p_data53",QString("%1").arg((GP53.y),0,'f',2));

ui.qwAxisLabelPosX->rootObject()->setProperty("p_data",QString("%1").arg((GP.x),0,'f',2));
ui.qwAxisLabelPosY->rootObject()->setProperty("p_data",QString("%1").arg((GP.y),0,'f',2));

ui.qwAxisLabelPosX->rootObject()->setProperty("p_feed",QString("%1").arg((MillMachine->getDrive("X")->Vnow()*60),0,'f',0));
ui.qwAxisLabelPosY->rootObject()->setProperty("p_feed",QString("%1").arg((MillMachine->getDrive("Y")->Vnow()*60),0,'f',0));

//ui.XG5X->setPalette(MillMachine->getDrive("X")->isTruPosition()? blckPalette:redPalette);
//ui.YG5X->setPalette(MillMachine->getDrive("Y")->isTruPosition()? blckPalette:redPalette);
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

}

 /*
if(ui.ZG5X)
   ui.ZG5X->setPalette(MillMachine->getDrive("Z")->isTruPosition()? blckPalette:redPalette);
if(ui.AG5X)
   ui.AG5X->setPalette(MillMachine->getDrive("A")->isTruPosition()? blckPalette:redPalette);
if(ui.BG5X)
   ui.BG5X->setPalette(MillMachine->getDrive("B")->isTruPosition()? blckPalette:redPalette);
*/
//ui.XG5X->setStyleSheet(QStringLiteral(MillMachine->Xd->isTruPosition()? "QLabel{color: rgb(0, 0, 0);}":"QLabel{color: rgb(170, 0, 0);}"));

/*
QPalette palR,palB;
palR=palB=XG5X->palette();
palR.setColor(QPalette::WindowText, Qt::red);
palB.setColor(QPalette::WindowText, Qt::blue);
*/
//ui.XG5X->setData(GP.x,2);
//XG5X->setPalette(MillMachine->getRotAxis(0)?palR:palB);

//ui.YG5X->setData(GP.y,2);
//YG5X->setPalette(MillMachine->getRotAxis(1)?palR:palB);

//if(ui.ZG5X) ui.ZG5X->setData(GP.z,2);
//if(ui.AG5X) ui.AG5X->setData(GP.a,2);
//if(ui.BG5X) ui.BG5X->setData(GP.b,2);

//ZG5X->setPalette(MillMachine->getRotAxis(2)?palR:palB);

//if(ui.cbSK->currentIndex()!=0)
 {
 ui.rotSK->setData(MillMachine->m_GCode.getRefPoint0SC(MillMachine->m_GCode.getActivSC()).a);
 //refPoint0->setData(Program->GCode.getRefPoint0SC(iSC-1).to3D().toString());
 //refPoint1->setData(Program->GCode.getRefPoint1SC(iSC-1).to3D().toString());
 }
/*
else
 {
 ui.rotSK->setData(0,4);
// refPoint0->setText("");
 //refPoint1->setText("");
 }
*/

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

/*
void WLPositionWidget::onPBsetX()
{
//if(MillMachine->isManual())
//QMessageBox::information(this, tr("Невозможно изменить"),tr("Необходимо выйти из ручного режима."),QMessageBox::Ok);
//  else
if(disButton) return;
WLEnterNum  EnterNum (this);
EnterNum.setLabel("X=");
EnterNum.setSuffix(tr("mm"));

if(EnterNum.exec())  setPosition("X",EnterNum.getNow());
}

void WLPositionWidget::onPBsetY()
{
if(disButton) return;
WLEnterNum  EnterNum (this);
EnterNum.setLabel("Y=");
//EnterNum.setSuffix(tr("mm"));

if(EnterNum.exec())  setPosition("Y",EnterNum.getNow());
}

void WLPositionWidget::onPBsetZ()
{
//if(MillMachine->isManual())
//QMessageBox::information(this, tr("Невозможно изменить"),tr("Необходимо выйти из ручного режима."),QMessageBox::Ok);
//  else
if(disButton) return;
WLEnterNum  EnterNum (this);
EnterNum.setLabel("Z=");
EnterNum.setSuffix(tr("mm"));

if(EnterNum.exec())  setPosition("Z",EnterNum.getNow());
}


void WLPositionWidget::onPBsetA()
{
//if(MillMachine->isManual())
//QMessageBox::information(this, tr("Невозможно изменить"),tr("Необходимо выйти из ручного режима."),QMessageBox::Ok);
//  else
if(disButton) return;
WLEnterNum  EnterNum (this);
EnterNum.setLabel("A=");
EnterNum.setSuffix(tr("gr"));

if(EnterNum.exec())  setPosition("A",EnterNum.getNow());
}
*/
void WLPositionWidget::onSetDrive(QString nameDrive,int type)
{
if(disButton) return;

if(type==3)
 {
 MillMachine->goDriveFind(nameDrive);
 return;
 }

WLEnterNum  EnterNum (this);

EnterNum.setLabel(nameDrive+"=");
//EnterNum.setSuffix(tr("gr"));

if(EnterNum.exec())  setPosition(nameDrive,EnterNum.getNow(),type);
}


void WLPositionWidget::setPosition(QString nameDrive,float pos,int type)
{
switch(type)
{
case 0:   MillMachine->setCurPositionSC(nameDrive,pos);
          break;
case 1:   MillMachine->getDrive(nameDrive)->setPosition(pos);
          break;
}
/*
if(type==0)//ui.cbSK->currentIndex()==1)
  {
  MillMachine->setCurPositionSC(nameDrive,pos);
  }  
  else
  if(ui.cbSK->currentIndex()==0)  MillMachine->getDrive(nameDrive)->setPosition(pos);
*/
  
}

void WLPositionWidget::onPBRotSC()
{
if(disButton) return;

//if(ui.cbSK->currentIndex()==1)
{
WLEnterNum  EnterNum (this);
EnterNum.setLabel("A=");
EnterNum.setSuffix(tr("gr"));

if(EnterNum.exec())  
 {
 MillMachine->rotAboutRotPointSC(MillMachine->m_GCode.getActivSC(),EnterNum.getNow());
 }
}


  /*
if(EnterNum.exec())  setPosition(ADrive,EnterNum.getNow());

  if(!disButton)
  {
  WLEnterNum *EnterNum =new WLEnterNum(this);
  EnterNum->setWindowTitle(tr("Enter the value of turning around P0:"));
  EnterNum->setLabel("A=");
  EnterNum->setSuffix(tr("gr"));
    
  WLFrame curPos=MillMachine->getCurrentPosition();
  
  curPos.fromM(MillMachine->GCode.getSC(MillMachine->GCode.getActivSC()).toM().inverted()*curPos.toM());
  WL3DPoint O,C,R;
  O=MillMachine->GCode.getRefPoint0SC(MillMachine->GCode.getActivSC()).to3D();
  C=curPos.to3D();
  R=MillMachine->GCode.getRefPoint1SC(MillMachine->GCode.getActivSC()).to3D();
  
  qDebug()<<"O"<<O.toString();
  qDebug()<<"C"<<C.toString();
  qDebug()<<"R"<<R.toString();
  qDebug()<<"Aco"<<C.getAxy(O);
  qDebug()<<"Aro"<<R.getAxy(O);

  EnterNum->setNow((C.getAxy(O)-R.getAxy(O))*180/M_PI);

  if(EnterNum->exec())  
    {
	MillMachine->GCode.rotAboutRotPointSK(MillMachine->GCode.getActivSC(),EnterNum->getNow());
    }
  
  delete EnterNum;
  }*/
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

WLGPoint  GP=MillMachine->m_GCode.getRefPoint1SC(MillMachine->m_GCode.getActivSC(),0);

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

void WLPositionWidget::onPBsetHome()
{
WLGPoint GP;
WLEditPoint EP;
QString nameDrive;

EP.setNameData("X,Y,Z,A,B,C");

QList <double> List;

GP=MillMachine->m_GCode.getHomePosition();

//if(ui.cbSK->currentIndex()==1) GP=MillMachine->m_GCode.getPointActivSC(GP,true);

EP.setLabel(tr("enter Home position"));

EP.setValueStr(GP.toString());

EP.show();

if(EP.exec())
    {
    GP.fromString(EP.getValueStr());

    //if(ui.cbSK->currentIndex()==1) GP=MillMachine->m_GCode.getPointActivSC(GP);

    MillMachine->m_GCode.setHomePosition(GP);
    }
	///emit ChangedHomePosition(Program->GCode.getSC(iSC-1).toM()*EP.getFrame().toM());

}

void WLPositionWidget::onPBgetHome()
{
if(QMessageBox::question(this, tr("Question:"),tr("are you sure?"),QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
                   MillMachine->m_GCode.setHomePosition(MillMachine->getCurrentPosition(1));
}
