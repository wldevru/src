#include "wllog.h"

WLLog::WLLog(QObject *parent)
	: QObject(parent)
{
m_dir=QCoreApplication::applicationDirPath()+"/log/";
}

WLLog::~WLLog()
{

}


void WLLog::writeLog(QString Name,QString Data)
{   
qDebug()<<"saveLog"<<m_dir;
QMutexLocker locker(&m_mutex);

QDate Date=QDate::currentDate();
QString fileName;
QDir DR(m_dir);

DR.mkdir(m_dir);
DR.mkdir(QString::number(Date.year()));
DR.cd(QString::number(Date.year()));
DR.mkdir(QString::number(Date.month()));
DR.cd(QString::number(Date.month()));

if(!DR.isReadable()) DR.mkdir(m_dir);

fileName=DR.path()+"//"
	    +QString::number(Date.year())
	    +QString::number(Date.month())
		+QString::number(Date.day())+".log";

QFile File(fileName);
if(File.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)) 
 {
 QTextStream stream(&File);
 stream<<Date.toString("dd/MM/yyyy")<<" "<<QTime::currentTime().toString()<<" \""<<Name<<"\" "<<" \""<<Data<<"\""<<endl;
 File.close();
 }
}
