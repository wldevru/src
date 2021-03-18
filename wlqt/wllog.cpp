#include "wllog.h"

QString WLLog::debugFile="";
bool WLLog::enableDebug=false;
WLLog *WLLog::m_instance=nullptr;
QMutex WLLog::debugMutex;

WLLog::WLLog(QObject *parent)
	: QObject(parent)
{
m_dirLog=QCoreApplication::applicationDirPath()+"/log/";

initDebugFileName();
}

WLLog::~WLLog()
{
}

WLLog *WLLog::getInstance()
{
if(!m_instance) m_instance = new WLLog;

return m_instance;
}

void WLLog::saveDebugFile(QString dir,QString comment)
{
QMutexLocker locker(&debugMutex);

if(dir.isEmpty()) dir=getDirDebug();

QDate Date=QDate::currentDate();

QString fileName=dir+"//"
                    +QString::number(Date.year())
                    +QString::number(Date.month())
                    +QString::number(Date.day())
                    +"-"
                    +QTime::currentTime().toString("hhmmss")
                    +"_"
                    +QApplication::applicationName()+".log";

QFile fileOut(fileName);

if(fileOut.size()!=0)
 {
 QFile::remove(fileName);
 }

if(fileOut.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
 {
 QTextStream stream(&fileOut);
 stream<<"Debug comment:"<<comment<<endl<<endl;

 QFile file2(debugFile+"2.log");
 QFile file1(debugFile+"1.log");
 QFile  file(debugFile+".log");


 if(file.open(QIODevice::ReadOnly|QIODevice::Text))
     {
     stream<<file.readAll();
     }

 if(file1.open(QIODevice::ReadOnly|QIODevice::Text))
     {
     stream<<"<<<FILE1>>>"<<endl;
     stream<<file1.readAll();
     }

 if(file2.open(QIODevice::ReadOnly|QIODevice::Text))
     {
     stream<<"<<<FILE2>>>"<<endl;
     stream<<file2.readAll();
     }

 fileOut.close();
 }


}


void WLLog::writeLog(QString Name,QString Data)
{   
qDebug()<<"WLLog::writeLog "<<Name<<Data;

QMutexLocker locker(&m_mutex);

QDate Date=QDate::currentDate();
QString fileName;
QDir DR(m_dirLog);

DR.mkdir(m_dirLog);
DR.mkdir(QString::number(Date.year()));
DR.cd(QString::number(Date.year()));
DR.mkdir(QString::number(Date.month()));
DR.cd(QString::number(Date.month()));

if(!DR.isReadable()) DR.mkdir(m_dirLog);

fileName=DR.path()+"//"
	    +QString::number(Date.year())
	    +QString::number(Date.month())
		+QString::number(Date.day())+".log";

QFile File(fileName);
if(File.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)) 
 {
 QTextStream stream(&File);
 stream<<QTime::currentTime().toString()<<" \""<<Name<<"\" "<<" \""<<Data<<"\""<<endl;
 File.close();
 }
}

void WLLog::initDebugFileName()
{
QDate Date=QDate::currentDate();
QString fileName;
QString dir=getDirDebug();
QDir DR(dir);

if(!DR.isReadable()) DR.mkdir(dir);

debugFile=DR.path()+"//debug";

}

void WLLog::deleteOldLogs()
{
QFile::remove(debugFile+"2.log");
QFile::rename(debugFile+"1.log",debugFile+"2.log");
QFile::remove(debugFile+"1.log");
QFile::rename(debugFile+".log",debugFile+"1.log");
}

void WLLog::setEnableDebug(bool en)
{
QMutexLocker locker(&debugMutex);

    if(en)    {
    initDebugFileName();
    qInstallMessageHandler(WLLog::messageHandler);
    }
    else {
    qInstallMessageHandler(nullptr);
    }

enableDebug=en;

emit changedDebug(enableDebug);
}

void WLLog::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &txt)
{
//check file size and if needed create new log!
QMutexLocker locker(&debugMutex);

QFile outFileCheck(debugFile+".log");

int size = outFileCheck.size();

if (size > LOGSIZE) //check current log size
 {
 deleteOldLogs();
 initDebugFileName();
 }

QFile outFile(debugFile+".log");

if(outFile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
 {
 QTextStream stream(&outFile);
 stream<<QTime::currentTime().toString("hh:mm:ss:zzz")<<" "<< txt << endl;

 outFile.close();
 }
}
