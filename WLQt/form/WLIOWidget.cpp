#include "WLIOWidget.h"
#include "WLEnterNum.h"

#include <qmessagebox.h>
WLIOWidget::WLIOWidget(QWidget *parent)
	: QTabWidget(parent)
{
//ui.setupUi(this);
//m_moduleIOPut=nullptr;

m_inputViewModel=nullptr;
m_outputViewModel=nullptr;
m_outPWMViewModel=nullptr;

m_tableViewIn=nullptr;
m_tableViewOut=nullptr;
m_tableViewOutPWM=nullptr;


m_IconOn  = new QIcon(":/data/icons/ion.png");
m_IconOff = new QIcon(":/data/icons/ioff.png");
}

WLIOWidget::~WLIOWidget()
{
delete m_IconOn;
delete m_IconOff;
}

void WLIOWidget::Init()
{
QStringList label;

if(m_inputViewModel)
  {
  m_tableViewIn=new QTableView();
  m_tableViewIn->setModel(m_inputViewModel);

  addTab(m_tableViewIn ,"DIN");

  connect(m_tableViewIn,SIGNAL(doubleClicked(QModelIndex)),SLOT(setDCTableInput(QModelIndex)));
  connect(m_inputViewModel,SIGNAL(changedData(QModelIndex)), m_tableViewIn,SLOT(update(QModelIndex)));


  m_tableViewOut=new QTableView();
  m_tableViewOut->setModel(m_outputViewModel);

  addTab(m_tableViewOut ,"DOUT");

  connect(m_tableViewOut,SIGNAL(doubleClicked(QModelIndex)),SLOT(setDCTableOutput(QModelIndex)));
  connect(m_outputViewModel,SIGNAL(changedData(QModelIndex)), m_tableViewOut,SLOT(update(QModelIndex)));
  }

if(m_outPWMViewModel)
  {
  m_tableViewOutPWM=new QTableView();
  m_tableViewOutPWM->setModel(m_outPWMViewModel);

  addTab(m_tableViewOutPWM,"OUTPWM");

  connect(m_tableViewOutPWM,SIGNAL(doubleClicked(QModelIndex)),SLOT(setDCTableOutPWM(QModelIndex)));
  connect(m_outPWMViewModel,SIGNAL(changedData(QModelIndex)), m_tableViewOutPWM,SLOT(update(QModelIndex)));
  }
/*
if(m_moduleAIOPut)
  {
  TableAIn = new QTableWidget(this);
  addTab(TableAIn,"AIN");

  TableAIn->setRowCount(m_moduleAIOPut->getSizeInputs());
  TableAIn->setColumnCount(1);

  label.clear();
  for(int i=0;i<m_moduleAIOPut->getSizeInputs();i++)
    label+=QString::number(i);

  TableAIn->setVerticalHeaderLabels(label);
  TableAIn->setHorizontalHeaderLabels(QString(tr("value,inv,F")).split(","));
  }
*/
QTimer *timer = new QTimer;
connect(timer,SIGNAL(timeout()),SLOT(updateData()));
timer->start(100);
}

/*
void WLIOWidget::initDOUT()
{
QStringList label;

if(DOUT!=NULL)
  {
  TableOut->setRowCount(DOUT->getSize());TableOut->setColumnCount(1);

  label.clear();
  for(int i=0;i<DOUT->getSize();i++)
	label+=QString::number(i);

  TableOut->setVerticalHeaderLabels(label);
  }

}*/

void WLIOWidget::setDCTableInput(QModelIndex mindex)
{
int row=mindex.row();

qDebug()<<"setDClick In"<<row;
switch(mindex.column())
{
//case 0: if(index<DOUT->getSize()) DOUT->tog(index); break;
	/*
case 1: if(QMessageBox::question(this,tr("Question"),tr("invert input")+" PC "+QString::number(row)+" ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
		{
		DIN->togInv(index);
		}
		break;*/
case 1: if(QMessageBox::question(this,tr("Question"),tr("invert input")+" WLMotion "+QString::number(row)+" ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
		{
        m_inputViewModel->moduleIOPut()->getInputV(row)->togInv();
		}
} 

}

void WLIOWidget::setDCTableOutput(QModelIndex mindex)
{
int row=mindex.row();

qDebug()<<"setDClick Out"<<row;
switch(mindex.column())
{
case 0: m_outputViewModel->moduleIOPut()->getOutputV(row)->setTog();
        break;
/*
case 1: if(QMessageBox::question(this,tr("Question"),tr("invert output")+" PC "+QString::number(row)+" ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
		{
		DOUT->togInv(index);
		}
		break;*/
case 1: if(QMessageBox::question(this,tr("Question"),tr("invert output")+" WLMotion "+QString::number(row)+" ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
          {
          m_outputViewModel->moduleIOPut()->getOutputV(row)->togInv();
          }
        break;

default: break;
}   
}

void WLIOWidget::setDCTableOutPWM(QModelIndex mindex)
{
int row=mindex.row();

WLEnterNum EN;
qDebug()<<"setDClick OutPWM"<<row;
switch(mindex.column())
{
//case 0: if(index<DOUT->getSize()) DOUT->tog(index); break;
/*
case 0: EN.setMinMaxNow(0.1,300,ModulePWM->getOutPWM(index)->getKOut()*100);
        EN.setLabel(tr("Eneter value:"));

        if(EN.exec())
          {
          ModulePWM->getOutPWM(index)->setKOut(EN.getNow()/100);
          }
        break;
*/
case 1: EN.setMinMaxNow(0,100, m_outPWMViewModel->modulePWM()->getOutPWM(row)->power()*100.0);
        EN.setLabel(tr("Eneter value:"));
        EN.setSuffix(tr("%"));

        if(EN.exec())
          {
          m_outPWMViewModel->modulePWM()->getOutPWM(row)->setOut(EN.getNow());
          }
        break;

case 2: if(QMessageBox::question(this,tr("Question"),tr("invert output")+" WLMotion "+QString::number(row)+" ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
        m_outPWMViewModel->modulePWM()->getOutPWM(row)->togInv();
        }
        break;

case 3: EN.setMinMaxNow(1,30000, m_outPWMViewModel->modulePWM()->getOutPWM(row)->freq());
        EN.setLabel(tr("Eneter Frequency:"));
        EN.setSuffix(tr("Hz"));

        if(EN.exec())
          {
         m_outPWMViewModel->modulePWM()->getOutPWM(row)->setFreq(EN.getNow());
          }
        break;
}
}


void WLIOWidget::updateData()
{
//m_tableViewIn->reset();
//m_tableViewOut->reset();
return;

QTableWidgetItem *item;

WLIOPut  *ioput;
WLAIOPut *aioput;
WLPWM    *pwm;
/*
if(m_moduleIOPut)
{
 for(int i=0;i<m_moduleIOPut->getSizeInputs();i++)
  {
  item = new QTableWidgetItem;
  item->setFlags(0);

  //if(MillMachine->motDevice->inputs[i]!=NULL)
  ioput=m_moduleIOPut->getInputV(i);
     {
     item->setFlags(ioput->isEnable()?Qt::ItemIsEnabled : Qt::NoItemFlags);
     item->setText(ioput->getComment());
     if(ioput->isInvalid())
         {
         item->setText("invalid");
         }
     item->setToolTip(ioput->getComment());
     item->setIcon(ioput->getNow() ? *m_IconOn:*m_IconOff);
     }

  TableIn->setItem(i,0,item);

  item = new QTableWidgetItem;
  item->setFlags(ioput->isEnable() ? Qt::ItemIsEnabled : Qt::NoItemFlags);
  item->setIcon(ioput->isInv()? *m_IconOn:*m_IconOff);

  TableIn->setItem(i,1,item);
  }

for(int i=0;i<m_moduleIOPut->getSizeOutputs();i++)
  {
  item = new QTableWidgetItem;
  item->setFlags(0);

  //if(MillMachine->outputs[i]!=NULL)
  ioput=m_moduleIOPut->getOutputV(i);
     {
     item->setFlags(ioput->isEnable()?Qt::ItemIsEnabled : Qt::NoItemFlags);
     item->setText(ioput->getComment());
     if(ioput->isInvalid())
         item->setText("invalid");
     item->setToolTip(ioput->getComment());
     item->setIcon(ioput->getNow() ? *m_IconOn:*m_IconOff);
     }
  TableOut->setItem(i,0,item);

  item = new QTableWidgetItem;
  item->setFlags(ioput->isEnable()?Qt::ItemIsEnabled : Qt::NoItemFlags);
  item->setIcon(ioput->isInv()? *m_IconOn:*m_IconOff);

  TableOut->setItem(i,1,item);
  }
}
*/

if(m_moduleAIOPut)
{
 for(int i=0;i<m_moduleAIOPut->getSizeInputs();i++)
  {
  item = new QTableWidgetItem;
  item->setFlags(0);

  //if(MillMachine->motDevice->inputs[i]!=NULL)
  aioput=m_moduleAIOPut->getInput(i);
     {
     item->setFlags(aioput->isEnable()?Qt::ItemIsEnabled : Qt::NoItemFlags);
     //item->setText(pwm->getComment());
     /*if(pwm->isInvalid())
         {
         item->setText("invalid");
         }*/
     //item->setToolTip("F="+QString::number(pwm->freq()));
     item->setText(QString::number(aioput->getValue()*100,'f',2)+"%");
     //item->setIcon(pwm->isUnlock() ? *IconOn:*IconOff);
     }

  TableAIn->setItem(i,0,item);
/*
  item = new QTableWidgetItem;
  item->setFlags(pwm->isEnable() ? Qt::ItemIsEnabled : Qt::NoItemFlags);
  item->setIcon(pwm->isInv()? *IconOn:*IconOff);

  TableOutPWM->setItem(i,1,item);

  item = new QTableWidgetItem;
  item->setFlags(pwm->isEnable() ? Qt::ItemIsEnabled : Qt::NoItemFlags);
  item->setText(QString::number(pwm->freq()));

  TableOutPWM->setItem(i,2,item);
*/
  }
}
}

