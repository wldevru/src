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

    QTimer *timerProgres = new QTimer;
    connect(timerProgres,SIGNAL(timeout()),this,SLOT(updateProgress()));
    timerProgres->start(1000);

    QTimer *timerOnButton = new QTimer;
    connect(timerOnButton,SIGNAL(timeout()),this,SLOT(updateOnButton()));
    timerOnButton->start(500);

    setFperStr("0.1,0.25,1,5,10,25,50,75,100");
    setJogDistStr("JOG,5.00,1.00,0.10,0.01");

    m_buttonSize=QSize(32,32);

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

    connect(ui.cbExGCode->lineEdit(),SIGNAL(returnPressed()),this,SLOT(onExGCode()));

    connect(ui.pbFindDrivePos,SIGNAL(clicked()),this,SLOT(onPBFindDrivePos()));

    connect(ui.pbReset,SIGNAL(clicked()),MillMachine,SLOT(reset()),Qt::DirectConnection);

    connect(MillMachine,SIGNAL(changedReadyRunList(bool)),SLOT(updateEnableMoved(bool)));

    ui.cbExGCode->setToolTip(
                 tr(
                "<b>GCode:</font></b>"
                "<ol>"
                  "<li>G0,G1</li>"
                  "<li>G2,G3 (I,J,K,R) </li>"
                  "<li>G17,G18,G19</li>"
                  "<li>G28 </li>"
                  "<li>G43 G44 G49</li>"
                  "<li>G51(XYZ scale)</li>"
                  "<li>G53(no modal)</li>"
                  "<li>G54-G59</li>"
                  "<li>G64,G61.1,G64(P,Q)</li>"
                  "<li>G80,G81,G83(Z,R,Q)</li>"
                  "<li>G90,G91</li>"
                  "<li>G98,G99</li>"
                "</ol>"
                  )
                );

initElementControls();

QTimer *timerFS= new QTimer;

connect(timerFS,SIGNAL(timeout()),SLOT(updateFSLabel()));
timerFS->start(50);

WLMPG *Whell=MillMachine->getMPG();

if(Whell)
 {
 connect(Whell,&WLMPG::changedCurIndexAxis,this,[=](quint8 i){if(gALabelX) gALabelX->setChecked(i==1);
                                                                if(gALabelY) gALabelY->setChecked(i==2);
                                                                if(gALabelZ) gALabelZ->setChecked(i==3);
                                                                if(gALabelA) gALabelA->setChecked(i==4);
                                                                if(gALabelB) gALabelB->setChecked(i==5);});


 if(gALabelX) gALabelX->setChecked(Whell->getCurIndexAxis()==1);
 if(gALabelY) gALabelY->setChecked(Whell->getCurIndexAxis()==2);
 if(gALabelZ) gALabelZ->setChecked(Whell->getCurIndexAxis()==3);
 if(gALabelA) gALabelA->setChecked(Whell->getCurIndexAxis()==4);
 if(gALabelB) gALabelB->setChecked(Whell->getCurIndexAxis()==5);

 //connect(Whell,&WLWhell::changedCurIndexX,this,[=](quint8 i){cbTypeManual->setCurrentIndex(i);});
 //connect(Whell,&WLWhell::changedCurVmode,ui.rbWhellVMode,&QRadioButton::setChecked);
 }

setFocusElement('J');

ui.pbOnMachine->setBaseSize(m_buttonSize);

}

WLPositionWidget::~WLPositionWidget()
{

}

void WLPositionWidget::setJogDistStr(QString str)
{
m_listManDist=str.split(",");
}

void WLPositionWidget::setFperStr(QString str)
{
QStringList list=str.split(",");

m_listFper.clear();

foreach(QString vstr,list)
 {
 m_listFper+=vstr.toFloat();
 }
}

void WLPositionWidget::initElementControls()
{
QList <WLMillDrive*> list=MillMachine->getDrives();

QSizePolicy sizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
QHBoxLayout *horLayout;

QVBoxLayout *verLayoutEL = ui.verLayoutControl;

gALabelX=new WLGAxisLabel(this);
gALabelY=new WLGAxisLabel(this);
gALabelZ=new WLGAxisLabel(this);
gALabelA=new WLGAxisLabel(this);
gALabelB=new WLGAxisLabel(this);
gALabelC=new WLGAxisLabel(this);

QFont font;

font=this->font();
font.setPointSize(12);


foreach(WLMillDrive *mdrive,list)
 {
 WLGAxisLabel *AL=nullptr;

 if(mdrive->getName()=="X")       AL=gALabelX;
 else if(mdrive->getName()=="Y")  AL=gALabelY;
 else if(mdrive->getName()=="Z")  AL=gALabelZ;
 else if(mdrive->getName()=="A")  AL=gALabelA;
 else if(mdrive->getName()=="B")  AL=gALabelB;

 if(AL==nullptr) continue;

 horLayout=new QHBoxLayout(this);

 AL->setDrive(mdrive);
 AL->setGCode(MillMachine->getGCode());;

 connect(AL,SIGNAL(changedPress(QString,int)),this,SLOT(onPushDrive(QString,int)));

 horLayout->addWidget(AL);

 QToolButton *TBM = new QToolButton(this);
 TBM->setIcon(QPixmap(":/data/icons/minus1.png"));
 TBM->setIconSize(m_buttonSize);
 TBM->setAutoRepeat(false);
 TBM->setSizePolicy(sizePolicy);

 connect(TBM,&QToolButton::pressed,this,[=](){onPBAxis(mdrive->getName(),-1,1);});
 connect(TBM,&QToolButton::released,this,[=](){onPBAxis(mdrive->getName(),-1,0);});

 horLayout->addWidget(TBM);

 QToolButton *TBP = new QToolButton(this);
 TBP->setIcon(QPixmap(":/data/icons/plus2.png"));
 TBP->setIconSize(m_buttonSize);
 TBP->setAutoRepeat(false);
 TBP->setSizePolicy(sizePolicy);

 connect(TBP,&QToolButton::pressed,this,[=](){onPBAxis(mdrive->getName(),1,1);});
 connect(TBP,&QToolButton::released,this,[=](){onPBAxis(mdrive->getName(),1,0);});
 horLayout->addWidget(TBP);

 connect(MillMachine,&WLMillMachine::changedOn,TBP,&QToolButton::setEnabled);
 connect(MillMachine,&WLMillMachine::changedOn,TBM,&QToolButton::setEnabled);

 connect(MillMachine,&WLMillMachine::changedPossibleManual,TBP,&QToolButton::setEnabled);
 connect(MillMachine,&WLMillMachine::changedPossibleManual,TBM,&QToolButton::setEnabled);

 TBM->setEnabled(MillMachine->isOn());
 TBP->setEnabled(MillMachine->isOn());

 TBPDriveList+=TBP;
 TBMDriveList+=TBM;

 if(mdrive->getName()=="X") {pbPlusX=TBP;pbMinusX=TBM;}
 else if(mdrive->getName()=="Y") {pbPlusY=TBP;pbMinusY=TBM;}
 else if(mdrive->getName()=="Z") {pbPlusZ=TBP;pbMinusZ=TBM;}

 verLayoutEL->addLayout(horLayout);
 }

QSizePolicy sizePolicyE = sizePolicy;

sizePolicyE.setHorizontalPolicy(QSizePolicy::Expanding);
//F

horLayout=new QHBoxLayout(this);

labelF = new WLLabel(this);
labelF->setPrefix("F:");
labelF->setDataN(0);
labelF->setFont(font);
labelF->setSizePolicy(sizePolicyE);

horLayout->addWidget(labelF);

QToolButton *TB100 = new QToolButton(this);
TB100->setIcon(QPixmap(":/data/icons/100.png"));
TB100->setIconSize(m_buttonSize);
TB100->setSizePolicy(sizePolicy);
horLayout->addWidget(TB100);

sbFper = new QDoubleSpinBox(this);
sbFper->setAlignment(Qt::AlignLeft);
sbFper->setRange(0.1,300);
sbFper->setSingleStep(0.05);
sbFper->setValue(100);
sbFper->setPrefix("F:");
sbFper->setSuffix("%");
sbFper->setButtonSymbols(QAbstractSpinBox::NoButtons);
sbFper->setSizePolicy(sizePolicyE);
sbFper->setFont(font);

connect(sbFper,SIGNAL(valueChanged(double)),MillMachine,SLOT(setPercentSpeed(double)));
MillMachine->setPercentSpeed(100);

horLayout->addWidget(sbFper);

connect(TB100,&QToolButton::clicked,this,[=](){sbFper->setValue(100);});

verLayoutEL->addLayout(horLayout);

//horLayout=new QHBoxLayout(this);

QToolButton *TBM = new QToolButton(this);
TBM->setIcon(QPixmap(":/data/icons/minus1.png"));
TBM->setIconSize(m_buttonSize);
TBM->setAutoRepeat(true);
TBM->setSizePolicy(sizePolicy);
//TBM->setMinimumSize(m_sizeButton);
connect(TBM,&QToolButton::clicked,this,&WLPositionWidget::on_pbMinusFper_pressed);
horLayout->addWidget(TBM);

QToolButton *TBP = new QToolButton(this);
TBP->setIcon(QPixmap(":/data/icons/plus2.png"));
TBP->setIconSize(m_buttonSize);
TBP->setAutoRepeat(true);
TBP->setSizePolicy(sizePolicy);
//TBP->setMinimumSize(m_sizeButton);
connect(TBP,&QToolButton::clicked,this,&WLPositionWidget::on_pbPlusFper_pressed);
horLayout->addWidget(TBP);

verLayoutEL->addLayout(horLayout);

//S
horLayout=new QHBoxLayout(this);

labelS = new WLLabel(this);
labelS->setPrefix("S:");
labelS->setDataN(0);
labelS->setFont(font);
labelS->setToolTip(tr("press for edit"));
labelS->setSizePolicy(sizePolicyE);
horLayout->addWidget(labelS);

TB100 = new QToolButton(this);
TB100->setIcon(QPixmap(":/data/icons/100.png"));
TB100->setIconSize(m_buttonSize);
TB100->setSizePolicy(sizePolicy);
//TB100->setMinimumSize(m_sizeButton);
connect(TB100,&QToolButton::clicked,this,[=](){MillMachine->setPercentSOut(100);});
horLayout->addWidget(TB100);

sbSper = new QDoubleSpinBox(this);
sbSper->setAlignment(Qt::AlignLeft);
sbSper->setRange(0.1,300);
sbSper->setSingleStep(0.05);
sbSper->setValue(100);
sbSper->setPrefix("S:");
sbSper->setSuffix("%");
sbSper->setButtonSymbols(QAbstractSpinBox::NoButtons);
sbSper->setFont(font);
sbSper->setSizePolicy(sizePolicyE);

connect(sbSper,SIGNAL(valueChanged(double)),MillMachine,SLOT(setPercentSOut(double)));
MillMachine->setPercentSOut(100);
horLayout->addWidget(sbSper);

connect(TB100,&QToolButton::clicked,this,[=](){sbSper->setValue(100);});

verLayoutEL->addLayout(horLayout);
//ui.laElementControl->addLayout(horLayout);

//horLayout=new QHBoxLayout(this);

TBM = new QToolButton(this);
TBM->setIcon(QPixmap(":/data/icons/minus1.png"));
TBM->setIconSize(m_buttonSize);
TBM->setAutoRepeat(true);
TBM->setSizePolicy(sizePolicy);
//TBM->setMinimumSize(m_sizeButton);
connect(TBM,&QToolButton::clicked,this,&WLPositionWidget::on_pbMinusSper_pressed);
horLayout->addWidget(TBM);

TBP = new QToolButton(this);
TBP->setIcon(QPixmap(":/data/icons/plus2.png"));
TBP->setIconSize(m_buttonSize);
TBP->setAutoRepeat(true);
TBP->setSizePolicy(sizePolicy);
//TBP->setMinimumSize(m_sizeButton);
connect(TBP,&QToolButton::clicked,this,&WLPositionWidget::on_pbPlusSper_pressed);
horLayout->addWidget(TBP);

//ui.laElementControl->addLayout(horLayout);
verLayoutEL->addLayout(horLayout);

//JOG
horLayout=new QHBoxLayout(this);

labelTypeManual = new QLabel(this);
labelTypeManual->setFont(font);
labelTypeManual->setText("JOG");
labelTypeManual->setSizePolicy(sizePolicyE);

horLayout->addWidget(labelTypeManual);

pbFast = new QToolButton(this);
pbFast->setFont(font);
pbFast->setText(tr("fast"));
pbFast->setIconSize(m_buttonSize);
pbFast->setSizePolicy(sizePolicy);

connect(pbFast,&QToolButton::pressed,this,&WLPositionWidget::on_pbFast_pressed);
connect(pbFast,&QToolButton::pressed,this,&WLPositionWidget::on_pbFast_released);

horLayout->addWidget(pbFast);

sbFman = new QDoubleSpinBox(this);
sbFman->setAlignment(Qt::AlignLeft);
sbFman->setRange(0,100);
sbFman->setValue(10);
sbFman->setPrefix("");
sbFman->setSuffix("%");
sbFman->setButtonSymbols(QAbstractSpinBox::NoButtons);
sbFman->setSizePolicy(sizePolicyE);
sbFman->setFont(font);

connect(sbFper,SIGNAL(valueChanged(double)),MillMachine,SLOT(setPercentSpeed(double)));

horLayout->addWidget(sbFman);

verLayoutEL->addLayout(horLayout);
//ui.laElementControl->addLayout(horLayout);

//horLayout=new QHBoxLayout(this);

TBM = new QToolButton(this);
TBM->setIcon(QPixmap(":/data/icons/minus1.png"));
TBM->setIconSize(m_buttonSize);
TBM->setAutoRepeat(true);
TBM->setSizePolicy(sizePolicy);
connect(TBM,&QToolButton::clicked,this,&WLPositionWidget::on_pbMinusFman_pressed);
horLayout->addWidget(TBM);


TBP = new QToolButton(this);
TBP->setIcon(QPixmap(":/data/icons/plus2.png"));
TBP->setIconSize(m_buttonSize);
TBP->setAutoRepeat(true);
TBP->setSizePolicy(sizePolicy);
connect(TBP,&QToolButton::clicked,this,&WLPositionWidget::on_pbPlusFman_pressed);
horLayout->addWidget(TBP);

verLayoutEL->addLayout(horLayout);
}

float WLPositionWidget::calcStepMov()
{
if(m_curIndexListMan==0)
    return 0.0;
 else
    return labelTypeManual->text().toFloat();
}

void WLPositionWidget::setFocusElement(char f)
{
if(sbFper->suffix().back()=="*") {sbFper->setSuffix(sbFper->suffix().chopped(1));}
else if(sbFman->suffix().back()=="*") {sbFman->setSuffix(sbFman->suffix().chopped(1));}
else if(sbSper->suffix().back()=="*") {sbSper->setSuffix(sbSper->suffix().chopped(1));}

if(f=='F') sbFper->setSuffix(sbFper->suffix()+"*");
else if(f=='S') sbSper->setSuffix(sbSper->suffix()+"*");
else if(f=='J') sbFman->setSuffix(sbFman->suffix()+"*");

focusElement=f;
}


void WLPositionWidget::keyPressEvent ( QKeyEvent * event )
{
if(!event->isAutoRepeat())
{
switch(event->key())
   {
   case Qt::Key_Left:    if(pbMinusX->isEnabled()) {pbMinusX->setDown(true);onPBAxis("X", -1,1);} break;
   case Qt::Key_Right:   if(pbPlusX->isEnabled())  {pbPlusX->setDown(true); onPBAxis("X",  1,1);} break;
   case Qt::Key_Down:    if(pbMinusY->isEnabled()) {pbMinusY->setDown(true);onPBAxis("Y", -1,1);} break;
   case Qt::Key_Up:      if(pbPlusY->isEnabled())  {pbPlusY->setDown(true); onPBAxis("Y",  1,1);} break;
   case Qt::Key_PageDown:if(pbMinusZ->isEnabled()) {pbMinusZ->setDown(true);onPBAxis("Z", -1,1);} break;
   case Qt::Key_PageUp:  if(pbPlusZ->isEnabled())  {pbPlusZ->setDown(true); onPBAxis("Z",  1,1);} break;
   }

switch(event->key())
   {
   case Qt::Key_Shift:   pbFast->setDown(true);
                         on_pbFast_pressed();
                         break;

   case Qt::Key_F:       setFocusElement('F'); break;
   case Qt::Key_S:       setFocusElement('S'); break;
   case Qt::Key_J:       setFocusElement('J'); break;
   }
}

switch(event->key())
   {
   case Qt::Key_Plus:    on_pbPlus_pressed();    break;
   case Qt::Key_Minus:   on_pbMinus_pressed();   break;
   }


event->accept();
}

void WLPositionWidget::keyReleaseEvent ( QKeyEvent * event )
{
if(!event->isAutoRepeat())
{
  switch(event->key())
  {
  case Qt::Key_Left:    if(pbMinusX->isEnabled()) {pbMinusX->setDown(false); onPBAxis("X", 1,0);} break;
  case Qt::Key_Right:   if(pbPlusX->isEnabled())  {pbPlusX->setDown(false);  onPBAxis("X", 1,0);} break;
  case Qt::Key_Down:    if(pbMinusY->isEnabled()) {pbMinusY->setDown(false); onPBAxis("Y", 1,0);} break;
  case Qt::Key_Up:      if(pbPlusY->isEnabled())  {pbPlusY->setDown(false);  onPBAxis("Y", 1,0);} break;
  case Qt::Key_PageDown:if(pbMinusZ->isEnabled()) {pbMinusZ->setDown(false); onPBAxis("Z", 1,0);} break;
  case Qt::Key_PageUp:  if(pbPlusZ->isEnabled())  {pbPlusZ->setDown(false);  onPBAxis("Z", 1,0);} break;
  }

  switch(event->key())
  {
  case Qt::Key_Shift:   pbFast->setDown(false);
                        on_pbFast_released();
                        break;
  }
}

event->accept();
}

void WLPositionWidget::focusOutEvent(QFocusEvent *event)
{
Q_UNUSED(event);

if(pbMinusX->isEnabled()
 &&pbMinusX->isDown())    {pbMinusX->setDown(false); onPBAxis("X", 1,0);}

if(pbPlusX->isEnabled()
 &&pbPlusX->isDown())     {pbPlusX->setDown(false);  onPBAxis("X", 1,0);}

if(pbMinusY->isEnabled()
 &&pbMinusY->isDown())    {pbMinusY->setDown(false); onPBAxis("Y", 1,0);}

if(pbPlusY->isEnabled()
 &&pbPlusY->isDown())     {pbPlusY->setDown(false);  onPBAxis("Y", 1,0);}

if(pbMinusZ->isEnabled()
 &&pbMinusZ->isDown()) {pbMinusZ->setDown(false); onPBAxis("Z", 1,0);}

if(pbPlusZ->isEnabled()
  &&pbPlusZ->isDown())  {pbPlusZ->setDown(false);  onPBAxis("Z", 1,0);}

pbFast->setDown(false);
}


void WLPositionWidget::mousePressEvent(QMouseEvent *event)
{
QMenu menu(this);
QAction *act;

if(labelS->geometry().contains(event->pos())) {
 act=menu.addAction(tr("set S correct"),this,SLOT(onSetSCor()));
 act=menu.addAction(tr("clear correct"),this,SLOT(onClearSCorList()));

 menu.exec(labelS->mapToGlobal(pos()));
 }else  if (labelTypeManual->geometry().contains(event->pos()))
        {
        if(++m_curIndexListMan==m_listManDist.size())
          {
          m_curIndexListMan=0;
          }

        labelTypeManual->setText(m_listManDist[m_curIndexListMan]);
        }

return;
}

void WLPositionWidget::updateProgress()
{
QString str;

ui.proBar->setVisible(MillMachine->isRunProgram());
ui.labelTime->setVisible(MillMachine->isRunProgram());
ui.cbExGCode->setVisible(!MillMachine->isRunProgram());

if(!MillMachine->isRunProgram())  return;

long           made=MillMachine->getIProgram();
long          order=Program->getElementCount();
double timeElement=MillMachine->getTimeElement()/1000;

long time_s=timeElement*(order-made+MillMachine->getMotionDevice()->getModulePlanner()->getCountBuf()
                                   +MillMachine->getTrajIProgramSize());

long h,m,s,d;

h=time_s/3600;
time_s-=h*3600;

m=time_s/60;
time_s-=m*60;

s=time_s;

str=(QString(("%1:%2:%3")).arg(h).arg(m).arg(s));

if(h<0)
/*
QTime curTime;

curTime=QTime::currentTime();

s+=curTime.second();
if(s>=60) {m++; s-=60;}

m+=curTime.minute();
if(m>=60) {h++; m-=60;}

d=0;
h+=curTime.hour();
while(h>=24)
     {h-=24;d++;}
*/
str+=(QString(("/%1:%2:%3:%4")).arg(d).arg(h).arg(m).arg(s));

ui.labelTime->setText(str);

ui.proBar->setValue((float)(Program->getLastMovElement())
                   /(float)(Program->getElementCount())*100.0);
/*
ui.labelBufPC-> setText(tr("PC     :")+QString::number(MillMachine->getTrajSize()));
ui.labelBufDev->setText(tr("Device :")+QString::number(MillMachine->getMotionDevice()->getModulePlanner()->getSizeBuf()
                                                      -MillMachine->getMotionDevice()->getModulePlanner()->getFree()));
*/
}

void WLPositionWidget::updateOnButton()
{
bool ntryPos=false;
static bool flash=false;

ui.pbOnMachine->setStyleSheet(flash
                           &&(!ui.pbOnMachine->isChecked()) ? "background-color: rgb(255, 100, 100);border-style: solid;"
                               :(MillMachine->isRunScript() ? "background-color: yellow ;border-style: solid;"
                                                           :"border-style: solid;"));

foreach(WLMillDrive *MD,MillMachine->getDrives())
 {
 if(!MD->isTruPosition())   {ntryPos=true; break;}
 }

ui.pbFindDrivePos->setStyleSheet(ntryPos
                               &&flash
                               &&ui.pbOnMachine->isChecked() ? "background-color: rgb(255, 100, 100);border-style: solid;"
                                                                            :"border-style: solid;");
flash=!flash;
}


void WLPositionWidget::onTeachAxis(QString nameDrive)
{
WLMillDrive *Drive=MillMachine->getDrive(nameDrive);
if(Drive!=nullptr)
 {
 WLEnterNum  EnterNum (this);
 EnterNum.setLabel(tr("Current position Drive ")+nameDrive+" = ");
 EnterNum.setNow(Drive->getAxisPosition());

 if(EnterNum.exec())
        {
        Drive->setPosition(EnterNum.getNow());
        MillMachine->goDriveTeach(nameDrive);
        }
 }
}

void WLPositionWidget::onSetSCor()
{
if(MillMachine->isUseCorrectSOut())  {
 MillMachine->addCurrentSCor();
 sbSper->setValue(100);
 }
else {
     QMessageBox::information(this,tr("information"),tr("S correct is off, please on in Edit->WLMill"));
     }
}

void WLPositionWidget::onClearSCorList()
{
auto ret=QMessageBox::question(this,tr("Question")
                              ,tr("Delete all data correct S?")
                              ,QMessageBox::Ok|QMessageBox::Cancel);
if(ret==QMessageBox::Ok)
 {
 MillMachine->clearSCorList();
 }
}

void WLPositionWidget::on_pbFast_pressed()
{     
MillMachine->setPercentManual(100.0);
}

void WLPositionWidget::on_pbFast_released()
{
MillMachine->setPercentManual(sbFman->value());
}

void WLPositionWidget::on_pbPlusFman_pressed()
{
int index=m_listFper.indexOf(sbFman->value());

if(index!=-1)
 {
 index++;
 if(index<m_listFper.size())  sbFman->setValue(m_listFper[index]);
 }
else {
 for(int i=0;i<m_listFper.size();i++)
  {
  if(sbFman->value()<m_listFper[i])
      {
      sbFman->setValue(m_listFper[i]);
      break;
      }
  }
}


}

void  WLPositionWidget::on_pbMinusFman_pressed()
{
int index=m_listFper.indexOf(sbFman->value());

if(index!=-1)
  {
  index--;
  if(index>=0)  sbFman->setValue(m_listFper[index]);
  }
else {
 for(int i=m_listFper.size()-1;i>=0;i--)
  {
  if(sbFman->value()>m_listFper[i])
      {
      sbFman->setValue(m_listFper[i]);
      break;
      }
  }
}
}

void WLPositionWidget::on_pbPlus_pressed()
{
switch(focusElement)
{
case 'F': on_pbPlusFper_pressed(); break;
case 'S': on_pbPlusSper_pressed(); break;
case 'J': on_pbPlusFman_pressed(); break;
}

}

void WLPositionWidget::on_pbMinus_pressed()
{
switch(focusElement)
{
case 'F': on_pbMinusFper_pressed(); break;
case 'S': on_pbMinusSper_pressed(); break;
case 'J': on_pbMinusFman_pressed(); break;
}

}

void WLPositionWidget::onPBAxis(QString name, int rot,bool press)
{

if(press)
    {
    if(pbFast->isDown())
        MillMachine->setPercentManual(100.0f);
    else
        MillMachine->setPercentManual(sbFman->value());

    MillMachine->goDriveManual(name,rot,calcStepMov());
    }
 else
    {
    if(calcStepMov()==0)
        MillMachine->goDriveManual(name,0,0);
    }
}



void WLPositionWidget::updateFSLabel()
{
labelF->setData(MillMachine->getCurSpeed()*60);
labelS->setData(MillMachine->getCurSOut());
}

void WLPositionWidget::onPBFindDrivePos()
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

gALabelX->setGPos(GP.x);
gALabelY->setGPos(GP.y);
gALabelZ->setGPos(GP.z-MillMachine->getGCode()->getHofst());
gALabelA->setGPos(GP.a);
gALabelB->setGPos(GP.b);

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

gALabelX->update();
gALabelY->update();
gALabelZ->update();
gALabelA->update();
gALabelB->update();

ui.pbRotSC->setText(QString::number(MillMachine->m_GCode.getRefPoint0SC(MillMachine->m_GCode.getActivSC()).a,'f',2));

ui.labelActivGCode->setText(MillMachine->m_GCode.getActivGCodeString());


if(MillMachine->m_motDevice->getModuleConnect())
 ui.labelConnect->setEnabled(MillMachine->m_motDevice->getModuleConnect()->isConnect());
else
 ui.labelConnect->setEnabled(false);

if(MillMachine->m_motDevice->getModuleConnect())
 ui.labelConnect->setEnabled(MillMachine->m_motDevice->getModuleConnect()->isConnect());
else
 ui.labelConnect->setEnabled(false);


WLModuleAxis *ModuleAxis=static_cast<WLModuleAxis*>(MillMachine->getMotionDevice()->getModule(typeMAxis));

if(ModuleAxis->getInput(MAXIS_inProbe)->getNow())
    ui.labelInProbe->setPixmap(QPixmap(":/data/icons/ion.png"));
else
    ui.labelInProbe->setPixmap(QPixmap(":/data/icons/ioff.png"));

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

void WLPositionWidget::onPushDrive(QString nameDrive,int type)
{
if(disButton) return;

if(type==WLGAxisLabel::typeName)
 {
 QMenu menu(this);
 QAction *act;

 act=menu.addAction(tr("0"));
 connect(act, &QAction::triggered,MillMachine,[=](){MillMachine->setCurPositionSC(nameDrive,0);});

 act=menu.addAction(tr("1/2"));
 connect(act, &QAction::triggered,MillMachine,[=](){MillMachine->setCurPositionSC(nameDrive,MillMachine->getCurPositionSC(nameDrive)/2);});

 if(nameDrive=="Z")
 {
 act=menu.addAction(tr("set H pause")); 
 act->setEnabled(MillMachine->isUseHPause());
 connect(act, &QAction::triggered,MillMachine,[=](){MillMachine->setHPause(MillMachine->getCurPosition(nameDrive));});
 }

 QMenu menuOper(this);
 menuOper.setTitle(tr("action"));

 act=menuOper.addAction(tr("Find"));
 connect(act, &QAction::triggered,MillMachine,[=](){MillMachine->goDriveFind(nameDrive);});

 act=menuOper.addAction(tr("Reset Find"));
 connect(act, &QAction::triggered,MillMachine,[=](){MillMachine->getDrive(nameDrive)->setTruPosition(false);});

 act=menuOper.addAction(tr("Teach"));
 connect(act, &QAction::triggered,this,[=](){onTeachAxis(nameDrive);});

 menu.addMenu(&menuOper);
 //act=menu.addAction(tr("Set Plus  Limit"));
 //act=menu.addAction(tr("Set Minus Limit"));

 act=menu.addAction(tr("reset alarm"));
 connect(act, &QAction::triggered,MillMachine,[=](){MillMachine->getDrive(nameDrive)->resetAlarm();});


      if(nameDrive=="X") menu.exec(gALabelX->mapToGlobal(pos()));
 else if(nameDrive=="Y") menu.exec(gALabelY->mapToGlobal(pos()));
 else if(nameDrive=="Z") menu.exec(gALabelZ->mapToGlobal(pos()));
 else if(nameDrive=="A") menu.exec(gALabelA->mapToGlobal(pos()));
 else if(nameDrive=="B") menu.exec(gALabelB->mapToGlobal(pos()));

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
