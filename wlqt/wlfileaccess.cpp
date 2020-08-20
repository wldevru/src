#include "wlfileaccess.h"

WLFileAccess::WLFileAccess(QObject *parent)
	: QObject(parent)
{

}

WLFileAccess::~WLFileAccess()
{

}

bool WLFileAccess::createFile(QString namefile)
{
//QFile File(QCoreApplication::applicationDirPath()+"//datafile//"+namefile);
QFile File(namefile);
if(File.open(QIODevice::WriteOnly))
 {
 File.close();
 return true;
 }
return false;
}

bool WLFileAccess::write(QString namefile,QString str)
{
//QFile File(QCoreApplication::applicationDirPath()+"//datafile//"+namefile);
QFile File(namefile);
if(File.open(QIODevice::Append))
 {
 File.write(str.toLocal8Bit());
 File.close();
 return true;
 }
return false;
}

bool WLFileAccess::saveVal(QString namefile,QString nameData,QScriptValue data)
{
QMutexLocker locker(&mutex);
//QFile File(QCoreApplication::applicationDirPath()+"/datafile//"+namefile);
QFile File(namefile);
QTextStream stream(&File);

bool save=false;

QStringList List;
QString buf;

//cbuf=NULL;

if(File.open(QIODevice::ReadOnly))
 {
 List=stream.readAll().split("\n");
 
// stream<<"xoffset=185";
//File.close();

 for(int i=0;i<List.size();i++)
  if(List[i].section("=",0,0)==nameData)
    {
	List[i].clear();
	List[i]=nameData+"="+QString::number(data.toNumber());
	save=true;
	break;
    }  

 File.close();
 } 

if(!save)
	 List+=nameData+"="+data.toString();

if(File.open(QIODevice::WriteOnly))
 {
 for(int i=0;i<List.size();i++)
   if(!List[i].isEmpty())
   {
   qDebug()<<"save"<<List[i];   
   stream<<List[i]<<"\n";	   
   }
 
 File.close();
 return true;
 }


return false;
}

QScriptValue WLFileAccess::loadVal(QString namefile,QString nameData)
{
QMutexLocker locker(&mutex);

//QFile File(QCoreApplication::applicationDirPath()+"/datafile//"+namefile);
QFile File(namefile);
QTextStream stream(&File);
QStringList List;
QScriptValue  ret="nodata";

if(File.open(QIODevice::ReadOnly))
 {
 List=stream.readAll().split("\n");
 
// stream<<"xoffset=185";
//File.close();

 for(int i=0;i<List.size();i++)
  if(List[i].section("=",0,0)==nameData)
    {
	ret=List[i].section("=",1,1);		
	break;
    }  

 File.close(); 
 } 

return ret;
}
