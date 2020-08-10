#include "WLMill.h"
#include <QTimer>
#include <QToolBox>
#include <QColor>
#include <QLineEdit>
#include <QTime>

#include <QMessageBox>
#include <QTextCursor>
#include <QDockWidget>
#include <QHBoxLayout> 
#include <QVBoxLayout> 
#include <QDebug> 
#include <QXmlStreamReader> 

#include "WLWhellWidget.h"
#include "WLEditMillWidget.h"
#include "WLPamWidget.h"
#include "WLDriveWidget.h"
#include "WLEnterNum.h"

#include "WLEditPoint.h"
#include "WLMillDriveWidget.h"
#include "WLDeviceWidget.h"
#include "WLDelay.h"


WLMill::WLMill(QWidget *parent)
: QMainWindow(parent)
{
    m_bclose=false;
    m_lifeM=0;

	QTimer *timerLifeM=new QTimer;
	connect(timerLifeM,SIGNAL(timeout()),SLOT(addLifeM()));
	timerLifeM->start(60*1000);

    MessManager =new WLMessManager(this);
	
	connect(this,SIGNAL(sendMessage(QString)),MessManager,SLOT(setMessage(QString)),Qt::QueuedConnection);
		
    Program = new WLGProgram(nullptr);
	
	connect(Program,SIGNAL(sendMessage(QString,QString,int)),MessManager,SLOT(setMessage(QString,QString,int)),Qt::QueuedConnection);

    EVMScript=new WLEVScript(0);
    EVMScript->moveToThread(EVMScript);

	Dialog= new WLDialog(this);
	EVMScript->addDialogWidget(Dialog);
    EVMScript->start();

    MillMachine = new WLMillMachine(Program,EVMScript);

    Program->setShowGCode(&MillMachine->m_GCode);

	connect(MillMachine,SIGNAL(sendMessage(QString,QString,int)),MessManager,SLOT(setMessage(QString,QString,int)),Qt::QueuedConnection);
    connect(MillMachine,SIGNAL(changedSK()),Program,SLOT(updateShowTraj()),Qt::DirectConnection);

	connect(MillMachine,SIGNAL(ready()),SLOT(readyMachine()));
    MillMachine->start();

    VisualWidget=new WLVisualWidget(Program,MillMachine);

	setCentralWidget(VisualWidget);

    Log = new WLLog(this);

    connect(MillMachine,SIGNAL(saveLog(QString,QString)),Log,SLOT(writeLog(QString,QString)));
    connect(MessManager,SIGNAL(saveLog(QString,QString)),Log,SLOT(writeLog(QString,QString)));

	qDebug()<<" createDockProgram";
    createDockProgram();	

	createTBView();
	createTBMcode();
	createTBMessage();

    QTimer *autoSaveTimer = new QTimer;
    connect(autoSaveTimer,SIGNAL(timeout()),SLOT(saveConfig()));
    autoSaveTimer->start(5*60*1000);

  //EVLScript=new WLEVScript(this);
  //EVLScript->start();
  //EVLScript->moveToThread(EVLScript);

    

	/*
	EVLScript=new WLEVScript(0);
	EVLScript->moveToThread(EVLScript);
    EVLScript->start();

	
	//QScriptValue objectMM2 = EVMScript->engine->newQObject(MillMachine);
    EVLScript->engine->globalObject().setProperty("MACHINE",objectMM);
*/
	//createTBScript();
	/*
	ES=new WLEVScript(0);
	ES->start();
	ES->moveToThread(ES);

	//connect(ES,SIGNAL(sendMessage(QString,QString,int)),MessManager,SLOT(setMessage(QString,QString,int)),Qt::QueuedConnection);
	 
	QScriptValue objectDOUT = ES->engine->newQObject(MillMachine->motDevice->DOUT);
    ES->engine->globalObject().setProperty("DOUT",objectDOUT);

	QScriptValue objectDIN = ES->engine->newQObject(MillMachine->motDevice->DIN);
    ES->engine->globalObject().setProperty("DIN",objectDIN);

	MillMachine->setEVScript(ES);

	ESLoop=new WLEVScript(0);
	ESLoop->start();
	ESLoop->moveToThread(ES);

	connect(ESLoop,SIGNAL(sendMessage(QString,QString,int)),MessManager,SLOT(setMessage(QString,QString,int)),Qt::QueuedConnection);
	 

    ES->engine->globalObject().setProperty("DOUT",objectDOUT);
    ES->engine->globalObject().setProperty("DIN",objectDIN);
	
	MillMachine->setEVScript(ES);*/
	//MillMachine->setEVMScript(EVMScript);
    //MillMachine->setEVLScript(EVLScript);

	//MillMachine->start();
    setWindowTitle("WLMill");
	qDebug()<<"End Init WHITE LINE";
	createMenuBar();
}




void WLMill::createTBMessage()
{
TBMessage = new QToolBar(tr("Message"));

TBMessage->addWidget(MessManager);

TBMessage->setObjectName("tbMessage");

addToolBar(TBMessage);
}

void WLMill::createTBMcode()
{
QToolBar *TBMCode = new QToolBar(tr("tollbar M"));
TBMCode->setIconSize(QSize(48,48));

TBMCode->addAction(QIcon(":/data/icons/M3.png"),tr("run spindle cw")+"(F3)",MillMachine,SLOT(runScriptM3()))->setShortcut(QKeySequence("F3"));;;
TBMCode->addAction(QIcon(":/data/icons/M4.png"),tr("run spindle ccw")+"(F4)",MillMachine,SLOT(runScriptM4()))->setShortcut(QKeySequence("F4"));;
TBMCode->addAction(QIcon(":/data/icons/M5.png"),tr("stop spindle")+"(F5)",MillMachine,SLOT(runScriptM5()))->setShortcut(QKeySequence("F5"));;
TBMCode->addAction(QIcon(":/data/icons/M7.png"),tr("run additional cooling")+"(F7)",MillMachine,SLOT(runScriptM7()))->setShortcut(QKeySequence("F7"));;
TBMCode->addAction(QIcon(":/data/icons/M8.png"),tr("run cooling")+"(F8)",MillMachine,SLOT(runScriptM8()))->setShortcut(QKeySequence("F8"));;
TBMCode->addAction(QIcon(":/data/icons/M9.png"),tr("stop cooling")+"(F9)",MillMachine,SLOT(runScriptM9()))->setShortcut(QKeySequence("F9"));

TBMCode->addAction(QIcon(QCoreApplication::applicationDirPath()+"\\icons\\userFunc1.png"),("userFunc1()"),MillMachine,SLOT(runUserFunc1()));
TBMCode->addAction(QIcon(QCoreApplication::applicationDirPath()+"\\icons\\userFunc2.png"),("userFunc2()"),MillMachine,SLOT(runUserFunc2()));
TBMCode->addAction(QIcon(QCoreApplication::applicationDirPath()+"\\icons\\userFunc3.png"),("userFunc3()"),MillMachine,SLOT(runUserFunc3()));
TBMCode->addAction(QIcon(QCoreApplication::applicationDirPath()+"\\icons\\userFunc4.png"),("userFunc4()"),MillMachine,SLOT(runUserFunc4()));
TBMCode->addAction(QIcon(QCoreApplication::applicationDirPath()+"\\icons\\userFunc5.png"),("userFunc5()"),MillMachine,SLOT(runUserFunc5()));

connect(MillMachine,SIGNAL(changedReadyRunList(bool)),TBMCode,SLOT(setDisabled(bool)));

TBMCode->setObjectName("tbMCode");
addToolBar(TBMCode);
}

void WLMill::createTBView()
{/*
QFont font;
font.setFamily(QString::fromUtf8("Arial"));
font.setPointSize(12);
font.setBold(true);
font.setItalic(false);
font.setUnderline(false);
font.setWeight(75);
font.setStrikeOut(false);
*/
TBView = new QToolBar(tr("View"));

//TBView->setFont(font);
//TBView->addAction(tr("Построить"),this,SLOT(buildView()));
QToolButton *toolButton = new QToolButton(this);

QMenu *menuView = new QMenu;

menuView->addAction(tr("Top"),VisualWidget,SLOT(setViewUp()));
menuView->addAction(tr("Bottom")  ,VisualWidget,SLOT(setViewDown()));
menuView->addAction(tr("Left")  ,VisualWidget,SLOT(setViewLeft()));
menuView->addAction(tr("Right") ,VisualWidget,SLOT(setViewRight()));
menuView->addAction(tr("Front"),VisualWidget,SLOT(setViewFront()));
menuView->addAction(tr("Rear")  ,VisualWidget,SLOT(setViewRear()));

toolButton->setMenu(menuView);
toolButton->setPopupMode(QToolButton::InstantPopup);
toolButton->setText(tr("View"));

TBView->addWidget(toolButton);

TBView->addAction(tr("Center")  ,VisualWidget,SLOT(setViewCenter()));
TBView->addSeparator();


QAction *Action;
QMenu *showView = new QMenu;

toolButton = new QToolButton(this);

Action=showView->addAction(tr("Program"),VisualWidget,SLOT(setViewProgram()));
Action->setCheckable(true);
Action->setChecked(true);

Action=showView->addAction(tr("Trajectory"),VisualWidget,SLOT(setViewMill()));
Action->setCheckable(true);
Action->setChecked(true);

Action=showView->addAction(tr("Limits"),VisualWidget,SLOT(setViewLimits()));
Action->setCheckable(true);
Action->setChecked(true);

Action=showView->addAction(tr("Rot"),VisualWidget,SLOT(setViewRotPoint()));
Action->setCheckable(true);

toolButton->setMenu(showView);
toolButton->setPopupMode(QToolButton::InstantPopup);
toolButton->setText(tr("Show"));

TBView->addWidget(toolButton);


QMenu *typeView = new QMenu;
toolButton = new QToolButton(this);
QActionGroup *actionGroup = new QActionGroup(this);

Action=typeView->addAction(tr("XYZ"),VisualWidget,SLOT(setViewXYZ()));
Action->setCheckable(true);
Action->setChecked(true);
actionGroup->addAction(Action);

Action=typeView->addAction(tr("GModel"),VisualWidget,SLOT(setViewGModel()));
Action->setCheckable(true);
Action->setChecked(false);
actionGroup->addAction(Action);

actionGroup = new QActionGroup(this);

Action=typeView->addAction(tr("Model"),VisualWidget,SLOT(setViewOffsetModel()));
Action->setCheckable(true);
Action->setChecked(true);
actionGroup->addAction(Action);

Action=typeView->addAction(tr("Tool"),VisualWidget,SLOT(setViewOffsetTool()));
Action->setCheckable(true);
Action->setChecked(false);
actionGroup->addAction(Action);

toolButton->setMenu(typeView);
toolButton->setPopupMode(QToolButton::InstantPopup);
toolButton->setText(tr("Type"));

TBView->addWidget(toolButton);

#ifdef DEF_5D
QComboBox *tView=new QComboBox(this);
tView->addItems(QString(tr("Head/Head,Head/Table")).split(","));

TBView->addWidget(tView);
TBView->addSeparator();

connect(tView,SIGNAL(currentIndexChanged(int)),VisualWidget,SLOT(setTypeView(int)));
#endif

TBView->setObjectName("tbView");
addToolBar(TBView);
}


void WLMill::createTBScript()
{
TBScript = new QToolBar(tr("Script"));

//TBScript->setFont(font);
//TBScript->addAction(tr("Построить"),this,SLOT(buildScript()));

TBScript->addAction(tr("resetScript") ,EVMScript,SLOT(reset()));

TBScript->addAction(tr("M100") ,MillMachine,SLOT(runScript0()));
TBScript->addAction(tr("M101") ,MillMachine,SLOT(runScript1()));
TBScript->addAction(tr("M102") ,MillMachine,SLOT(runScript2()));
TBScript->addAction(tr("M103") ,MillMachine,SLOT(runScript3()));
TBScript->addAction(tr("M104") ,MillMachine,SLOT(runScript4()));
TBScript->addAction(tr("M105") ,MillMachine,SLOT(runScript5()));
TBScript->addAction(tr("M106") ,MillMachine,SLOT(runScript6()));
TBScript->addAction(tr("M107") ,MillMachine,SLOT(runScript7()));
TBScript->addAction(tr("M108") ,MillMachine,SLOT(runScript8()));
TBScript->addAction(tr("M109") ,MillMachine,SLOT(runScript9()));
TBScript->addAction(tr("M110") ,MillMachine,SLOT(runScript10()));
TBScript->addAction(tr("M112") ,MillMachine,SLOT(runScript11()));
TBScript->addAction(tr("M113") ,MillMachine,SLOT(runScript12()));
TBScript->addAction(tr("M114") ,MillMachine,SLOT(runScript13()));
TBScript->addAction(tr("M115") ,MillMachine,SLOT(runScript14()));

TBScript->setObjectName("tbScript");
addToolBar(TBScript);
}
void WLMill::createMenuBar()
{
MenuBar = new QMenuBar;

QMenu *MFile= new QMenu(tr("File")); 
MFile->addAction(tr("Save program"),Program,SLOT(saveFile()));
MFile->addAction(tr("Save program as"),this,SLOT(onSaveAsProgram()));
MFile->addSeparator();
MFile->addAction(tr("Load program"),this,SLOT(onLoadProgram()));
MFile->addSeparator();

MFile->addAction(tr("Save coordinates"),this,SLOT(onSaveSC()));
MFile->addAction(tr("Load coordinates"),this,SLOT(onLoadSC()));
MFile->addAction(tr("Close"),this,SLOT(close()));
MFile->addSeparator();
MenuBar->addMenu(MFile);

QMenu *MEdit= new QMenu(tr("Edit")); 
MEdit->addAction((tr("Drive")+" X"),this,SLOT(onEditDriveX()));
MEdit->addAction((tr("Drive")+" Y"),this,SLOT(onEditDriveY()));
MEdit->addAction((tr("Drive")+" Z"),this,SLOT(onEditDriveZ()));
MEdit->addAction((tr("Drive")+" A"),this,SLOT(onEditDriveA()));
MEdit->addAction((tr("Drive")+" B"),this,SLOT(onEditDriveB()));


MFile->addSeparator();
MEdit->addAction(("WLMill"),this,SLOT(onEditWLMill()));
MEdit->addAction(tr("Colors"),this,SLOT(onSetColors()));
MEdit->addAction(tr("Whell"),this,SLOT(onEditWhell()));
MEdit->addAction(tr("Device"),this,SLOT(onEditDevice()));
MFile->addSeparator();
//MEdit->addAction(("WLMotion"),this,SLOT(onLoadConfigDevice()));
//MFile->addSeparator();
//MEdit->addAction(tr("Motion param"),this,SLOT(onEditPam()));

connect(MillMachine,SIGNAL(changedOn(bool)),MEdit,SLOT(setDisabled(bool)));

MenuBar->addMenu(MEdit);

QMenu *MHelp= new QMenu(tr("about")); 
MHelp->addAction(tr("program"),this,SLOT(about()));
MHelp->addAction(tr("Qt"),qApp,SLOT(aboutQt()));///??

MenuBar->addMenu(MHelp);

//connect(MillMachine,SIGNAL(ChangedEnableMoving(bool)),MenuBar,SLOT(setDisabled(bool)));

MenuBar->setObjectName("menubar");
setMenuBar(MenuBar);
}



void WLMill::createDockProgram()
{
DockProgram=new QDockWidget(this);

ProgramWidget = new WLGProgramWidget(Program,this);

//connect(ProgramWidget,SIGNAL(changed()),this,SLOT(setStarChangedProgram()));
//connect(ProgramWidget,&WLGProgramWidget::changed,this,&WLMill::sendProSLOT(sendProgramToShow()));


connect(VisualWidget,&WLVisualWidget::changedEditElement,ProgramWidget,&WLGProgramWidget::setEditElement);

connect(ProgramWidget,&WLGProgramWidget::changedEditElement,VisualWidget,&WLVisualWidget::setEditElement);
connect(MillMachine,&WLMillMachine::changedReadyRunList,ProgramWidget,&WLGProgramWidget::setEditDisabled);

DockProgram->setWindowTitle(tr("Program"));
DockProgram->setWidget(ProgramWidget);

DockProgram->setObjectName("DProgram");
DockProgram->setFeatures(QDockWidget::DockWidgetFloatable
                        |QDockWidget::DockWidgetMovable
                        |QDockWidget::DockWidgetClosable);

addDockWidget(Qt::RightDockWidgetArea,DockProgram);

}

void WLMill::createDockPosition()
{
/*
QFont font;
font.setFamily(QString::fromUtf8("Arial"));
font.setPointSize(12);
font.setBold(true);
font.setItalic(false);
font.setUnderline(false);
font.setWeight(75);
font.setStrikeOut(false);
*/
DockPosition=new QDockWidget(this);

DockPosition->setWindowTitle(tr("Positions"));
DockPosition->setObjectName("DPosition");

PositionWidget=new WLPositionWidget(MillMachine,Program);

//connect(PositionWidget,&WLPositionWidget::changedHomePosition,Program,&WLGProgram::setSLOT(setHomePosition(WLFrame)));
//connect(PositionWidget,SIGNAL(changedBackPosition(WLFrame)),Program,SLOT(setBackPosition(WLFrame)));

//connect(MillMachine,SIGNAL(changedReadyRunList(bool)),PositionWidget,SLOT(setEditDisabled(bool)));

connect(PositionWidget,SIGNAL(changedViewSC(int)),VisualWidget,SLOT(setViewSC(int)));



//DockPosition->setFont(font);

DockPosition->setWidget(PositionWidget);
DockPosition->setFeatures(QDockWidget::NoDockWidgetFeatures|QDockWidget::DockWidgetMovable);

addDockWidget(Qt::RightDockWidgetArea,DockPosition);

}


void WLMill::createDockMillControl()
{

/*
QFont font;
font.setFamily(QString::fromUtf8("Arial"));
font.setPointSize(12);
font.setBold(true);
font.setItalic(false);
font.setUnderline(false);
font.setWeight(75);
font.setStrikeOut(false);
*/
DockMillControl=new QDockWidget(this);

DockMillControl->setWindowTitle(tr("Mill Control"));
DockMillControl->setObjectName("DMillControl");

MillControl = new WLMillControl(MillMachine,Program,this);

DockMillControl->setWidget(MillControl);

DockMillControl->setFeatures(QDockWidget::DockWidgetFloatable
                            |QDockWidget::DockWidgetMovable);

addDockWidget(Qt::LeftDockWidgetArea,DockMillControl);
}


void WLMill::createDockIOPut()
{
	/*
QFont font;
font.setFamily(QString::fromUtf8("Arial"));
font.setPointSize(12);
font.setBold(true);
font.setItalic(false);
font.setUnderline(false);
font.setWeight(75);
font.setStrikeOut(false);
*/

qDebug()<<"createDock";

DockIOPut=new QDockWidget(this);

DockIOPut->setWindowTitle("In/Out");
DockIOPut->setObjectName("DIOPut");

IOPutWidget =new WLIOPutWidget();

IOPutWidget->setModuleIOPut(MillMachine->m_motDevice->getModuleIOPut());
IOPutWidget->setModulePWM(MillMachine->m_motDevice->getModulePWM());

IOPutWidget->Init();

DockIOPut->setWidget(IOPutWidget);
DockIOPut->setFeatures(QDockWidget::DockWidgetFloatable
                      |QDockWidget::DockWidgetMovable
                      |QDockWidget::DockWidgetClosable);

addDockWidget(Qt::LeftDockWidgetArea,DockIOPut);
}

void WLMill::updateEnableMoved(bool en)
{
Q_UNUSED(en)
//TextProgram->setReadOnly(en);
}


void WLMill::createDockControls()
{
}

void WLMill::setStateButtonGo(bool state)
{
qDebug()<<"setStateButtonGo"<<state;
TButtonGo->setDown(!state);
}

void WLMill::Error(QString name,QString data)
{
QString Pstr;
QTextStream str(&Pstr);
str<<name<<":"<<data;
QMessageBox::information(this, tr("Stop error"),Pstr,QMessageBox::Ok);
}


WLMill::~WLMill()
{
qDebug("DELETE WHITE");
MillMachine->reset();
/*
saveDataState();
saveLast();
saveLife();
*/
EVMScript->quit();
EVMScript->wait();

//MillMachine->quit();
//MillMachine->wait();
//EVLScript->quit();
//EVLScript->wait();

saveConfig();

//delete EVLScript;

delete VisualWidget;
delete Program;
delete MillMachine;
delete EVMScript;

qDebug("DELETE WHITE END");
}

void WLMill::onLoadConfigDevice()
{/*
QString fileName = QFileDialog::getSaveFileName(this, tr("Load config WLMotion"),fileName,"xml (*.xml)");

if(!fileName.isEmpty()) 
	{
	MillMachine->motDevice->readFromFile(fileName,false);
    }	
*/
}

void WLMill::onEditDrive(QString nameDrive)
{
if(MillMachine->getDrive(nameDrive))
  {
  WLDriveWidget AW(MillMachine->getDrive(nameDrive));
  WLMillDriveWidget MDW(MillMachine->getDrive(nameDrive));

  AW.addTabWidget(&MDW,tr("other"));

  AW.show();

  if(AW.exec())
    {
    AW.saveDataDrive();
    MillMachine->updateMainDimXYZ();
    }

  MillMachine->saveConfig();
  }

}


void WLMill::onEditWLMill()
{
WLEditMillWidget EditMill(MillMachine);
EditMill.show();

if(EditMill.exec())
   {
   EditMill.saveData();
   }
}


void WLMill::onSaveSC()
{
if(lastFileSC.isEmpty()) lastFileSC=QCoreApplication::applicationDirPath();

QString fileName = QFileDialog::getSaveFileName(this, tr("Save coordinates"),lastFileSC,"sc (*.scxml)");

if(!fileName.isEmpty())
{
QFile FileXML(lastFileSC=fileName);
if(FileXML.open(QIODevice::WriteOnly))
{
QXmlStreamWriter stream(&FileXML);

stream.setAutoFormatting(true);

stream.setCodec(QTextCodec::codecForName("Windows-1251"));
stream.writeStartDocument("1.0");

stream.writeStartElement("WhiteLineSC");

 for(int i=0;i<sizeSC;i++)
 {
 stream.writeStartElement("SC");
 stream.writeAttribute("i",QString::number(i));

 stream.writeAttribute("Frame",MillMachine->m_GCode.getOffsetSC(i).toString());
 stream.writeAttribute("refPoint0",MillMachine->m_GCode.getRefPoint0SC(i).toString());
 stream.writeAttribute("refPoint1",MillMachine->m_GCode.getRefPoint1SC(i).toString());
 stream.writeEndElement();
 }

 stream.writeStartElement("author");
 stream.writeAttribute("Name","BocharovSergey");
 stream.writeAttribute("e-mail","bs_info@mail.ru");
 stream.writeAttribute("phone","+79139025883");
 stream.writeEndElement();

stream.writeEndElement();

stream.writeEndDocument();

 FileXML.close();
}

}
}

void WLMill::onEditScript()
{
WLEditText EditText;
WLMCodeSH  codeSH(EditText.getDocument());
EditText.setText(EVMScript->getCode());
EditText.setLabel(tr("Please modify:"));

EditText.show();
if(EditText.exec())
  {
  EVMScript->setCode(EditText.getText());
  }

}

void WLMill::onLoadSC()
{
if(lastFileSC.isEmpty()) lastFileSC=QCoreApplication::applicationDirPath();

QString fileName = QFileDialog::getOpenFileName(this, tr("Download coordinates"),lastFileSC,("sc (*.scxml)"));

if(!fileName.isEmpty())
{
QFile FileXML(lastFileSC=fileName);

QXmlStreamReader stream;

qDebug()<<"load ConfigXML";
//bool ret=0;

if(FileXML.open(QIODevice::ReadOnly))
  {
 qDebug()<<"open ConfigXML";
  stream.setDevice(&FileXML);

  while(!stream.atEnd())
   {
   if(stream.readNext()==QXmlStreamReader::StartElement)
   if(stream.name()=="WhiteLineSC")
    {
    //Program->loadFile(stream.attributes().value("LastProgram").toString());

	 while(!stream.atEnd())
	 { 
        stream.readNextStartElement();
		qDebug()<<"findElement "<<stream.name()<<" "<<stream.tokenString();
	    if(stream.name()=="WhiteLineSC") break;
		if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;
		/*
		if(stream.name()=="Operating")
		  {
          setLifeM(stream.attributes().value("Minute").toString().toULong());
		  continue;
		  }

		if(stream.name()=="Name")
		  {
		  Program->loadFile(stream.readElementText());
		  continue;
	      }

		if(stream.name()=="HomePos")
		 {
		 qDebug()<<"loadHomePos";
		 WL3DPoint P;
		 P.x=stream.attributes().value("x").toString().toFloat();
		 P.y=stream.attributes().value("y").toString().toFloat();
		 P.z=stream.attributes().value("z").toString().toFloat();
		 
		 Program->setHomePosition(P);
		 continue;
		 }
		*/
		if(stream.name()=="SC")
		 {
		 qDebug()<<"loadSC";
         //int i=0;
         //i=stream.attributes().value("i").toString().toInt();
/*
		 WLFrame Fr;

		 Fr.fromString(stream.attributes().value("Frame").toString());
		 MillMachine->GCode.setOffsetSC(i,Fr);
		 
		 Fr.fromString(stream.attributes().value("refPoint0").toString());
		 MillMachine->GCode.setRefPoint0SC(i,Fr);
		 
		 Fr.fromString(stream.attributes().value("refPoint1").toString());
		 MillMachine->GCode.setRefPoint1SC(i,Fr);
*/
		 MillMachine->saveConfig();
		 continue;		 
	     }
     
	 }	 
    }
   }
  }
}
}

void WLMill::onLoadProgram()
{
QString fileName = QFileDialog::getOpenFileName(this, tr("Load program"),Program->getNameFile(),("g-code (*.ncc *.nc *.tap);;all type(*.*)"));
if(!fileName.isEmpty())
      Program->loadFile(fileName,true); 
//updateTitleDockProgram(1);
}

void WLMill::onSaveAsProgram()
{
QString fileName = QFileDialog::getSaveFileName(this, tr("Save program as"),Program->getNameFile(),("g-code (*.ncc *.nc);;all type(*.*)"));
if(!fileName.isEmpty())
     Program->saveFile(fileName); 
//updateTitleDockProgram(1);
}

void WLMill::UpdateTimes()
{
	TimeNow=QTime::currentTime();
	//ui.label_Time->setText(TimeNow.toString("hh:mm"));

	TimeEnd=TimeNow;
	

}


/*
void WLMill::moveCursorTextProgram()
{
//QStringList ListKadr;
int pos;

QTextCursor TextCursor=TextProgram->textCursor();
pos=TextCursor.position();
//qDebug("blo=%d",pos);
if(pos>=0) 
    {
	qDebug()<<"Pos="<<pos;
    emit ChangedEditElementPos(pos);	
	}
}
*/
/*
void WLMill::setCursorToEditElement(int l)
{
qDebug()<<"set edit line"<<l<<Program->getElementTraj(l).ipos
	<<Program->getElementTraj(l).iline
	<<Program->getElementTraj(Program->getElementTraj(l).iline).ipos;
/*
//pos-=size;*/
/*
if(!fEditProgram)
{
TextProgram->setFocus();
QTextCursor TextCursor=TextProgram->textCursor();

TextCursor.setPosition(Program->getElementTraj(l).ipos);
//qDebug()<<"setPosET"<<Program->getElementTraj(l).ipos;
TextCursor.select(QTextCursor::LineUnderCursor);

TextProgram->blockSignals(true);
TextProgram->setTextCursor(TextCursor);
TextProgram->blockSignals(false);
}
*/
/*
QStringList ListKadr;

int pos,size;
qDebug("set edit line=%d",l);

ListKadr=TextProgram->toPlainText().split("\n");
pos=0;
for(int i=0;i<ListKadr.size();i++)
  {
  if(i==l)
   {
   //pos-=size;
   TextProgram->setFocus();
   QTextCursor TextCursor=TextProgram->textCursor();
   
   TextCursor.setPosition(pos);

   TextCursor.select(QTextCursor::LineUnderCursor);

   TextProgram->blockSignals(true);
   TextProgram->setTextCursor(TextCursor);
   TextProgram->blockSignals(false);
   break;
   }
  pos+=size=ListKadr[i].size()+1;
  }

}
*/

void WLMill::closeEvent (QCloseEvent * event)
{   
switch(QMessageBox::question(this, tr("Confirmation:"),
       tr("Do you really want to exit the program?"), 
	   QMessageBox::Yes|QMessageBox::No))
	    {
		
        case QMessageBox::Yes:     qDebug()<<"exit";
                                   saveDataState();
			                       MillMachine->setOff(true);
			                       break;

        default:                   event->ignore();
			                       return;
		}

}


void WLMill::leaveEvent ( QEvent * event )
{
Q_UNUSED(event)
//Machine->Pause(1);
}


/*

void WLMill::setProgram()
{

QString	Text=Program->getTextProgram();

int maxView=5000;
long i;

for(i=0;maxView!=0&&i<Text.size();i++)
	if(Text[i]==('\n'))
	  {
      maxView--;
	  }
Text.resize(i);

TextProgram->setText(Text);
resetStarChangedProgram();
}
*/
	
void WLMill::readyMachine()
{
	/*
VisualWidget=new WLVisualWidget(Program,MillMachine);
setCentralWidget(VisualWidget);
connect(VisualWidget,SIGNAL(ChangedEditElement(int)),ProgramWidget,SLOT(setCursorToElement(int)));
*/
loadConfig();

createDockIOPut();
createDockMillControl();
createDockPosition();

loadDataState();


connect(MillMachine->m_motDevice,SIGNAL(changedVersion(quint32)),SLOT(updateTitle()));
connect(this,SIGNAL(changedLife()),SLOT(updateTitle()));

updateTitle();
//Program->reloadFile(true);
}

void WLMill::onEditDevice()
{
WLDeviceWidget DW;
WLDeviceInfo DevInfo;

DW.show();

if(DW.exec())
 {
 qDebug()<<"changed Device";
 DevInfo=DW.getDeviceInfo();

 if(!DevInfo.name.isEmpty())
  {
  MillMachine->m_motDevice->setInfo(DevInfo);
  //MillMachine->motDevice->closeConnect();
  //MillMachine->motDevice->openConnect();

     /*
  if(Dev->getNameDevice()==MillMachine->motDevice->getNameDevice())
     {
     MillMachine->motDevice->initSerialPort(Dev->getPortName());
     }
  else
     {
     MillMachine->motDevice->setNameDevice(Dev->getNameDevice());
     MillMachine->motDevice->initSerialPort(Dev->getPortName());
     }
*/
  QMessageBox::information(this,tr("Attention"),tr("Please restart WLMill"));
  close();
  }
 }

}

void WLMill::onEditWhell()
{
if(!MillMachine->m_motDevice->getModuleWhell()) return;

WLWhellWidget WhellWidget(MillMachine->m_motDevice->getModuleWhell()->getWhell(0)
                         ,MillMachine->m_motDevice->getModuleIOPut()
                         ,this);

WhellWidget.show();

if(WhellWidget.exec())
  {
  WhellWidget.saveData();
  }
}

void WLMill::onSetColors()
{
QColorDialog Dialog(this);
QColor lastColor=VisualWidget->getClearColor();

Dialog.setCurrentColor(lastColor);
Dialog.setModal(true);
Dialog.show();

connect(&Dialog,SIGNAL(currentColorChanged(QColor)),VisualWidget,SLOT(setClearColor(QColor)));

if(Dialog.exec())
 {
 VisualWidget->setClearColor(Dialog.currentColor());
 }
else
 {
 VisualWidget->setClearColor(lastColor);
 }

}

void WLMill::loadDataState()
{

QSettings settings("FileState",QSettings::IniFormat);
settings.setIniCodec("UTF-8");
restoreGeometry(settings.value("geometry").toByteArray());
restoreState(settings.value("windowState").toByteArray());

    /*
QSettings settings("WLDev", "WLMill");

restoreGeometry(settings.value("geometry").toByteArray());
restoreState(settings.value("windowState").toByteArray());
*/

    /*
QFile File(FileState);

if(!File.open(QIODevice::ReadOnly)) return;//emit messageError()return false;

QByteArray ByteArray;

ByteArray=File.readAll();

File.close();

qDebug()<<"loadDataState "<<restoreState(ByteArray);*/
}

void WLMill::saveDataState()
{
if(!MillMachine->isReady()) return;

QSettings settings("FileState",QSettings::IniFormat);
settings.setIniCodec("UTF-8");
settings.setValue("geometry", saveGeometry());
settings.setValue("windowState", saveState());
/*

QFile File(FileState);
if(!File.open(QIODevice::WriteOnly)) return;//emit messageError()return false;

File.write(saveState());
File.close();
*/
//qDebug()<<"saveDataState ;
}

 /*
void WLMill::updateTitleDockProgram(bool edit)
{
QString star;

if(edit) star="*"; 

DockProgram->setWindowTitle(star+Program->getNameFile());
}*/

void WLMill::updateTitle()
{
QString title;
quint32 verWLMill=VERSION_YEAR*10000+VERSION_MONTH*100+VERSION_DAY;

title=QString("WLMill %1h ver=%2").arg((float)getLifeM()/60.0,0,'f',1).arg(verWLMill);

#ifdef enableDemo
 title+=QString(" (demo)");
#endif

 if(MillMachine
  &&MillMachine->m_motDevice)
 {
 if(!MillMachine->m_motDevice->isReady())
  title+=" / "+MillMachine->m_motDevice->getNameDevice()+" ver="+QString::number(MillMachine->m_motDevice->getVersion());
else
  title+=QString(" /noDevice");
 }

setWindowTitle(title);
}




void WLMill::showMessage(QString name,QString data,int code)
{
//Machine->Stop();
//QMutexLocker locker(&lastErrorMutex);
QString Pstr;
QTextStream str(&Pstr);
str<<name<<": "<<data<<tr(", code=")<<code;

//if(Pstr!=lastError)
    {
	if(code!=0)
		QMessageBox::information(this, tr("Stop due to an error:"),Pstr,QMessageBox::Ok);
	else
		QMessageBox::information(this, tr("Stop: "),Pstr,QMessageBox::Ok);

	//lastError=Pstr;
	//QTimer::singleShot(500,this,SLOT(clearLastError()));
    }

}



void WLMill::saveConfig()
{
QFile FileXML(configWLMill);

if(!MillMachine->isReady()) return;

if(FileXML.open(QIODevice::WriteOnly))
{
QXmlStreamWriter stream(&FileXML);

stream.setAutoFormatting(true);

stream.setCodec(QTextCodec::codecForName("Windows-1251"));
stream.writeStartDocument("1.0");

stream.writeStartElement("WhiteLineMillConfig");

 stream.writeAttribute("maxShowPoints",QString::number(Program->maxShowPoints()));
 stream.writeAttribute("zoomDir",QString::number(VisualWidget->zoomDir()));
 stream.writeAttribute("LastProgram",Program->getNameFile());
 stream.writeAttribute("LastElementProgram",QString::number(Program->getLastMovElement()));
 stream.writeAttribute("LastSC",lastFileSC);


 stream.writeStartElement("Colors");
 stream.writeAttribute("clear",VisualWidget->getClearColor().name());
 stream.writeEndElement();

 /*
 stream.writeStartElement("HomePos");
 stream.writeAttribute("Frame",MillMachine->GCode.getHomePosition().toString());

 stream.writeEndElement();

 for(int i=0;i<sizeSC;i++)
 {
 stream.writeStartElement("SC");
 stream.writeAttribute("i",QString::number(i));

 stream.writeAttribute("Frame",MillMachine->GCode.getOffsetSC(i).toString());
 stream.writeAttribute("refPoint0",MillMachine->GCode.getRefPoint0SC(i).toString());
 stream.writeAttribute("refPoint1",MillMachine->GCode.getRefPoint1SC(i).toString());
 stream.writeEndElement();
 }
 */

 stream.writeStartElement("Operating"); 
 stream.writeAttribute("Minute",QString::number(getLifeM(),'g',36));	 
 stream.writeEndElement();


 stream.writeStartElement("author");
 stream.writeAttribute("Name","BocharovSergey");
 stream.writeAttribute("e-mail","bs_info@mail.ru");
 stream.writeAttribute("phone","+79139025883");
 stream.writeEndElement();

stream.writeEndElement();

stream.writeEndDocument();
qDebug()<<"Write XML";

 FileXML.close();
}
else
qDebug()<<"no Write XML";
}

int WLMill::loadConfig()
{
QFile FileXML(configWLMill);
QXmlStreamReader stream;
qDebug()<<"load ConfigXML";
bool ret=0;
QString lastProg;

if(FileXML.open(QIODevice::ReadOnly))
  {
  qDebug()<<"open ConfigXML";
  stream.setDevice(&FileXML);

  while(!stream.atEnd())
   {
   if(stream.readNext()==QXmlStreamReader::StartElement)
   if(stream.name()=="WhiteLineMillConfig")
    {
    qDebug()<<"read ConfigXML";
	ret=1;
	
    if(!stream.attributes().value("maxShowPoints").isEmpty())
     {
     Program->setMaxShowPoints(stream.attributes().value("maxShowPoints").toLong());
     }

    if(!stream.attributes().value("zoomDir").isEmpty())
     {
     VisualWidget->setZoomDir(stream.attributes().value("zoomDir").toInt());
     }

	lastProg=stream.attributes().value("LastProgram").toString();
	Program->setLastMovElement(stream.attributes().value("LastElementProgram").toString().toLong());

	//Program->loadFile(stream.attributes().value("LastProgram").toString()); перенесли в конец
	lastFileSC=(stream.attributes().value("LastSC").toString());

	 while(!stream.atEnd())
	 { 
       stream.readNextStartElement();
		qDebug()<<"findElement "<<stream.name()<<" "<<stream.tokenString();
	    if(stream.name()=="WhiteLineMillConfig") break;
		if(stream.tokenType()!=QXmlStreamReader::StartElement) continue;

		if(stream.name()=="Operating")
		  {
          setLifeM(stream.attributes().value("Minute").toString().toULong());
          continue;
          }

        if(stream.name()=="Colors")
          {
          QColor color;
          if(!stream.attributes().value("clear").isEmpty())
               {
               color.setNamedColor(stream.attributes().value("clear").toString());
               VisualWidget->setClearColor(color);
               }
          continue;
          }

		if(stream.name()=="Name")
		  {
		  Program->loadFile(stream.readElementText(),true);
		  continue;
	      }

        /*
		if(stream.name()=="HomePos")
		 {
		 qDebug()<<"loadHomePos";

		 WLFrame Fr;
		 Fr.fromString(stream.attributes().value("Frame").toString());
		 MillMachine->GCode.setHomePosition(Fr);

		 continue;
		 }
		if(stream.name()=="SC")
		 {
		 qDebug()<<"loadSC";
		 WL3DPoint SC;
		 int i=0;

		 i=stream.attributes().value("i").toString().toInt();

		 WLFrame Fr;

		 Fr.fromString(stream.attributes().value("Frame").toString());
		 MillMachine->GCode.setOffsetSC(i,Fr);
		 
		 Fr.fromString(stream.attributes().value("refPoint0").toString());
		 MillMachine->GCode.setRefPoint0SC(i,Fr);

		 Fr.fromString(stream.attributes().value("refPoint1").toString());
		 MillMachine->GCode.setRefPoint1SC(i,Fr); 
		 continue;		 
	     }
       //---
       */
	 }
	
    }
   }

  Program->loadFile(lastProg,true);//чтобы сразу не загружал программу
  }
  else
    ret=0;


return ret;
}


void WLMill::about()
{
QMessageBox::about(this,("program"),
		   tr(" WLMill <br>"
  		      " http://wldev.ru <br>"
			  " wldev@mail.ru <br>"
			  "<br>WhiteLine</b> <br>"
			  " Qt №<b>1549622</b><br>"              
#ifdef enableExportKuka
			  "buyer:"buyer
#endif
			  ));

}

void WLMill::help()
{
about();
}

