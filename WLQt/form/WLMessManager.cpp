#include "WLMessManager.h"

WLMessManager::WLMessManager(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButtonCErr,SIGNAL(clicked()),SLOT(clear()));
	updateList();

	pixmap=QPixmap(30,20);
	count_flash=0;
	updateList();	

	flashTimer = new QTimer;
	connect(flashTimer,SIGNAL(timeout()),SLOT(updateFlash()));
	flashTimer->start(250);

	updateFlash();
	qDebug()<<"create MessManager";
}

WLMessManager::~WLMessManager()
{

}

void WLMessManager::updateFlash()
{
  if(count_flash==0)
     {	 
     if(List.isEmpty())
      pixmap.fill(QColor(0,155,0));
	 else
      pixmap.fill(QColor(155,0,0));	 
     }
   else
     {
     pixmap.fill(QColor(cur?255:155,0,0));
	 cur=!cur;
	 count_flash--;
	 }

ui.label->setPixmap(pixmap);
}


void WLMessManager::clear()
{
QMutexLocker locker(&mutex);
count_flash=0;
List.clear();
updateList();
}

void WLMessManager::updateList()
{
QString time;
QString contSTR;

ui.comboBox->clear();

ui.pushButtonCErr->setDisabled(List.isEmpty());
ui.comboBox->setDisabled(List.isEmpty());

for(int i=0;i<List.size();i++)
  {
  time=List[i].time.toString("hh:mm:ss:zzz");
  contSTR="..."+QString::number(List[i].count)+"+";

  if(List[i].code<0)
	ui.comboBox->addItem(time+" >ERR "+List[i].name+":"+List[i].mess+"("+QString::number(List[i].code)+")"+contSTR);
  else															
	ui.comboBox->addItem(time+" >MSG "+List[i].name+":"+List[i].mess+"("+QString::number(List[i].code)+")"+contSTR);
  }
}

void WLMessManager::setMessage(QString name,QString mess,int code)
{
errData nData;

bool add=false;

emit saveLog("WLMessageManager",name+";"+mess+";"+QString::number(code));

mutex.lock();

nData.time=QTime::currentTime();
nData.name=name;
nData.mess=mess;
nData.code=code;
nData.count=1;

for(int i=0;i<List.size();i++)//find
 if(nData.name==List[i].name
  &&nData.mess==List[i].mess
  &&nData.code==List[i].code)
   {
   if(List[i].count<=100) ++List[i].count;
   List[i].time=nData.time; 
   nData.count=List[i].count;
   add=true;
   
   List.move(i,0);
   break;
   }

if(!add) List.prepend(nData);

if(code<=0) count_flash=10;

updateList();

mutex.unlock();

if(code<=0)
{

 if((mutexShow.tryLock())&&(nData.count<=100))
 {
 if(code==0) QMessageBox::information(this, tr("Message: "),name+":"+mess,QMessageBox::Ok);
     else
      if(code<0) QMessageBox::critical(this, tr("Error: "),name+":"+mess,QMessageBox::Ok);
 
 mutexShow.unlock();
 }

}
}

