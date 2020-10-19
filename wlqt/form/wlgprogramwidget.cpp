#include "wlgprogramwidget.h"
#include <QMessageBox>

WLGProgramWidget::WLGProgramWidget(WLGProgram *_Program,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    m_sizeListProgram=100;

	m_GProgram=_Program;

	m_changedProgram=false;

	connect(ui.textProgram,SIGNAL(cursorPositionChanged ()),SLOT(onChangedPositionTextProgram()));
    connect(ui.textProgram,SIGNAL(textChanged()),SLOT(onChangedTextProgram()));

	connect(ui.listProgram,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),SLOT(onChangedPositionListProgram()));

    //connect(ui.listProgram,SIGNAL(//
	
    ui.pbUpdate->setIcon(QIcon(":/data/icons/update.png"));
    ui.pbAccept->setIcon(QIcon(":/data/icons/accept.png"));
    ui.pbBackup->setIcon(QIcon(":/data/icons/backup.png"));
    ui.pbReload->setIcon(QIcon(":/data/icons/reload.png"));
	
    connect(ui.vsbProgram,SIGNAL(valueChanged(int)),SLOT(setEditElement(int)));

    ui.sbPosition->setKeyboardTracking(false);
    connect(ui.sbPosition,SIGNAL(valueChanged(int)),SLOT(setEditElement(int)));
    connect(ui.sbPosition,SIGNAL(valueChanged(int)),SIGNAL(changedEditElement(int)));

	connect(m_GProgram,SIGNAL(ChangedProgram()),SLOT(loadTextProgram()));

	connect(m_GProgram,SIGNAL(ChangedShowProgress(int)),ui.progressBar,SLOT(setValue(int)));

	connect(ui.pbAccept,SIGNAL(clicked()),SLOT(onAccept()));
	connect(ui.pbBackup,SIGNAL(clicked()),SLOT(onBackup()));
	connect(ui.pbReload,SIGNAL(clicked()),SLOT(onReload()));
	connect(ui.pbUpdate,SIGNAL(clicked()),SLOT(onUpdate()));
	
	connect(this,SIGNAL(changed(bool)),ui.pbAccept,SLOT(setEnabled(bool)));
	connect(this,SIGNAL(changed(bool)),ui.pbBackup,SLOT(setEnabled(bool)));	
		
	ui.textProgram->setEnabled(false);
    m_GCodeSH = new WLGCodeSH(ui.textProgram->document());
}

WLGProgramWidget::~WLGProgramWidget()
{

}

void WLGProgramWidget::onUpdate()
{
m_GProgram->updateShowTraj();
}

void WLGProgramWidget::onAccept()
{
if((QMessageBox::question(this, tr("Confirmation:"),
       tr("save program?"),
       QMessageBox::Yes|QMessageBox::No))== QMessageBox::Yes)
   {
   saveTextProgram();
   emit changed(m_changedProgram=false);
   }
}

void  WLGProgramWidget::showListProgram(int iCenter)
{
qDebug()<<"showListProgram"<<iCenter;
//QMutexLocker locker(&Program->Mutex);

QListWidgetItem *item;
QListWidgetItem *itemShow=nullptr;

if(iCenter<m_sizeListProgram/2)
  {m_startIProgram=0;m_endIProgram=m_sizeListProgram;}
else
if((iCenter+m_sizeListProgram/2)>m_GProgram->indexData.size()) 	
  {
  m_startIProgram=m_GProgram->indexData.size()-1-m_sizeListProgram;
  m_endIProgram=m_GProgram->indexData.size()-1;
  }
else
  {
  m_startIProgram=iCenter-m_sizeListProgram/2;
  m_endIProgram=iCenter+m_sizeListProgram/2;
  }

 ui.listProgram->blockSignals(true);
 ui.listProgram->clear();
 qDebug()<<"showListProgram"<<m_startIProgram<<m_endIProgram;

 //startIProgram=0;
 //endIProgram=Program->getElementTrajCount();

 for(int i=m_startIProgram;i<=m_endIProgram;i++)
      {    	
	  //Program->getElementTraj(i).str.re.remove("\n");
      item=new QListWidgetItem(QString::number(i)+": "+m_GProgram->getTextElement(i).simplified());

	 // qDebug()<<i<<"/"<<iCenter;

      if(i==iCenter)
       {/*item->setBackgroundColor(QColor(255,200,200)); */
        itemShow=item;qDebug()<<"detect";
       }

	  ui.listProgram->addItem(item);	 
      }
if(itemShow==nullptr) itemShow=item;

ui.listProgram->setFocus();
ui.listProgram->setCurrentItem(itemShow);
ui.listProgram->scrollToItem(itemShow);

ui.listProgram->blockSignals(false);

ui.vsbProgram->setValue(iCenter);
 qDebug()<<"endShow";
}

void  WLGProgramWidget::loadTextProgram()
{
qDebug()<<"loadTextProgram"<<m_GProgram->getElementCount();

QString buf;
ui.labelName->setText(tr("name: ")+m_GProgram->getName());
ui.labelName->setToolTip(m_GProgram->getNameFile());
//qDebug()<<"loadTextProgram1";
//qDebug()<<"loadTextProgram2";

if(m_GProgram->getElementCount()<20000)
 { 
 qDebug()<<"istProgram<20000"<<m_GProgram->getElementCount();
 ui.stackedWidget->setCurrentIndex(1);
 ui.textProgram->setEnabled(true);
 ui.textProgram->blockSignals(true);
 ui.textProgram->setPlainText(m_GProgram->getTextProgram());
 ui.textProgram->blockSignals(false);

 //QTimer::singleShot(100,this,SLOT(saveTextProgram()));
 }
else
 {
 ui.stackedWidget->setCurrentIndex(0);
 ui.sbPosition->setRange(0,m_GProgram->getElementCount());
 ui.vsbProgram->setRange(0,m_GProgram->getElementCount());
 ui.vsbProgram->setPageStep(m_sizeListProgram);
 showListProgram(0);
 }

emit changed(m_changedProgram=false);
qDebug()<<"endloadTextProgram";
}

void WLGProgramWidget::saveTextProgram()
{
m_GProgram->setTextProgram(ui.textProgram->toPlainText());
}

void WLGProgramWidget::onBackup()
{
//qDebug()<<"onBackup";
loadTextProgram();
emit changed(m_changedProgram=false);
}

void WLGProgramWidget::onReload()
{
m_GProgram->reloadFile(true);
}

void WLGProgramWidget::onChangedTextProgram()
{
qDebug()<<"onChangedTextProgram";
if(ui.textProgram->isEnabled()&&(m_changedProgram==false))
	{
	qDebug()<<"send";
	emit changed(m_changedProgram=true);
    }
}

void WLGProgramWidget::setEditDisabled(bool dis)
{
ui.pbAccept->setDisabled(dis);
ui.pbBackup->setDisabled(dis);
ui.pbReload->setDisabled(dis);

ui.textProgram->setReadOnly(dis);
}
	

void WLGProgramWidget::setEditElement(int iElement)
{
qDebug()<<"set iElement"<<iElement<<ui.stackedWidget->currentIndex()<<m_changedProgram;

if(0<=iElement)
{
 if(ui.stackedWidget->currentIndex()==1)
 {
  if(m_changedProgram) return;

  int pos=0;
  QTextCursor cursor=ui.textProgram->textCursor();

  ui.textProgram->setFocus();

  //for(int i=0;i<iElement;i++)
  pos= m_GProgram->indexData[iElement-1].offsetInFile;

  cursor.setPosition(pos);
  qDebug()<<"setPosET"<<pos;
  cursor.select(QTextCursor::LineUnderCursor);

  blockSignals(true);
  ui.textProgram->setTextCursor(cursor);
  blockSignals(false);
 }
 else
  {
  showListProgram(iElement);
  }
}
}

void WLGProgramWidget::onChangedPositionTextProgram()
{
QTextCursor cursor=ui.textProgram->textCursor();
int posF=cursor.position();
int pos=0;

if(!m_changedProgram)
for(int i=0;i<m_GProgram->getElementCount();i++)
     {			 
	 if(posF<=(m_GProgram->indexData[i].offsetInFile-1)) 
	    {
	    qDebug()<<"onChangedPositionTextProgram()"<<posF<<(m_GProgram->indexData[i].offsetInFile-1);
        emit changedEditElement(i);
		break;
	    }
     }
}

void WLGProgramWidget::onChangedPositionListProgram()
{
if(ui.listProgram->count()==0) return;

ui.listProgram->blockSignals(true);

QListWidgetItem *item=ui.listProgram->currentItem();
qDebug()<<"ui.listProgram->count()"<<ui.listProgram->count();
if(ui.listProgram->item(ui.listProgram->count()-1)==item)
  {
  if((m_endIProgram+1)<(m_GProgram->getElementCount()))
      {
      ui.listProgram->takeItem(0);
      m_endIProgram++;
      ui.listProgram->addItem(QString::number(m_endIProgram)+": "+m_GProgram->getTextElement(m_endIProgram).simplified().toLocal8Bit());      
      m_startIProgram++;

	  //ui.listProgram->setCurrentRow(endIProgram);
	  //ui.listProgram->setCurrentRow(endIProgram-1);
      }
  }
else
  if(ui.listProgram->item(0)==item)
  {
  qDebug()<<"startIProgram="<<m_startIProgram;
  if((m_startIProgram)>=1)
      {	  
	  qDebug()<<"startIProgram--";
	  ui.listProgram->takeItem(ui.listProgram->count()-1);
      m_startIProgram--;
      ui.listProgram->insertItem(0,QString::number(m_startIProgram)+": "+m_GProgram->getTextElement(m_startIProgram).simplified().toLocal8Bit());
      m_endIProgram--;

//	  ui.listProgram->setCurrentRow(startIProgram);
//	  ui.listProgram->setCurrentRow(startIProgram+1);
      }
  }

ui.listProgram->blockSignals(false);

emit changedEditElement(m_startIProgram+ui.listProgram->row(ui.listProgram->currentItem()));
}
