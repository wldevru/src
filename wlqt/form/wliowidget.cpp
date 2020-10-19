#include "wliowidget.h"
#include "wlenternum.h"

#include <qmessagebox.h>
WLIOWidget::WLIOWidget(QWidget *parent)
	: QTabWidget(parent)
{
m_IconOn  = new QIcon(":/data/icons/ion.png");
m_IconOff = new QIcon(":/data/icons/ioff.png");
}

WLIOWidget::~WLIOWidget()
{
delete m_IconOn;
    delete m_IconOff;
}

void WLIOWidget::setDevice(WLMotion *Device)
{
if(Device->getModuleIOPut()) setModuleIOPut(Device->getModuleIOPut());
if(Device->getModulePWM())   setModulePWM(Device->getModulePWM());
if(Device->getModuleAIOPut())setModuleAIOPut(Device->getModuleAIOPut());
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
  }

if(m_outputViewModel)
  {
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

if(m_ainputViewModel)
  {
  m_tableViewAIn=new QTableView();
  m_tableViewAIn->setModel(m_ainputViewModel);

  addTab(m_tableViewAIn ,"AIN");

  //connect(m_tableViewIn,SIGNAL(doubleClicked(QModelIndex)),SLOT(setDCTableInput(QModelIndex)));
  connect(m_ainputViewModel,SIGNAL(changedData(QModelIndex)), m_tableViewAIn,SLOT(update(QModelIndex)));
  }

if(m_aoutputViewModel)
  {
  m_tableViewAOut=new QTableView();
  m_tableViewAOut->setModel(m_aoutputViewModel);

  addTab(m_tableViewAOut ,"AOUT");

  connect(m_tableViewAOut,SIGNAL(doubleClicked(QModelIndex)),SLOT(setDCTableAOutput(QModelIndex)));
  connect(m_aoutputViewModel,SIGNAL(changedData(QModelIndex)), m_tableViewAOut,SLOT(update(QModelIndex)));
  }

}

void WLIOWidget::setDCTableInput(QModelIndex mindex)
{
int row=mindex.row();

qDebug()<<"setDClick In"<<row;
switch(mindex.column())
{
case 1: if(QMessageBox::question(this,tr("Question"),tr("invert input")+" WLMotion "+QString::number(row)+" ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
		{
        m_inputViewModel->moduleIOPut()->getInput(row)->togInv();
		}
} 

}

void WLIOWidget::setDCTableOutput(QModelIndex mindex)
{
int row=mindex.row();

switch(mindex.column())
{
case 0: m_outputViewModel->moduleIOPut()->getOutput(row)->setTog();
        break;

case 1: if(QMessageBox::question(this,tr("Question"),tr("invert output")+" WLMotion "+QString::number(row)+" ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
          {
          m_outputViewModel->moduleIOPut()->getOutput(row)->togInv();
          }
        break;

default: break;
}   
}

void WLIOWidget::setDCTableOutPWM(QModelIndex mindex)
{
int row=mindex.row();

WLEnterNum EN;

switch(mindex.column())
{
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

void WLIOWidget::setDCTableAOutput(QModelIndex mindex)
{
int row=mindex.row();

WLEnterNum EN;

EN.setMinMaxNow(0,1,m_aoutputViewModel->moduleAIOPut()->getOutput(row)->value());
EN.setLabel(tr("Value (0-1):"));
EN.setSuffix(tr(""));

if(EN.exec())
        {
        m_aoutputViewModel->moduleAIOPut()->getOutput(row)->setValue(EN.getNow());
        }
}

