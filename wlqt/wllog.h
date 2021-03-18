#ifndef WLLOG_H
#define WLLOG_H

#include <QMutex>
#include <QDir>
#include <QDirIterator>
#include <QTextStream>
#include <qdatetime.h>
#include <QObject>
#include <QDebug>
#include <QApplication>

#define LOGSIZE  1024 * 500 //log size in bytes
#define LOGFILES 5

class WLLog : public QObject
{
	Q_OBJECT

public:
    WLLog(QObject *parent=nullptr);
	~WLLog();

   void setDirLog(QString _dir) {if(!_dir.isEmpty()) m_dirLog=_dir;}
QString getDirLog()               {return m_dirLog;}

private:
    QMutex m_mutex;
    QString m_dirLog;

 static QMutex debugMutex;
	
public slots:
    void writeLog(QString Name,QString Data);
    void setEnableDebug(bool en);

signals:

    void changedDebug(bool);

private:
  static bool enableDebug;
  static QString debugFile;
  static  void initDebugFileName();
  static  void deleteOldLogs();

private:
  static WLLog *m_instance;

public:
  static WLLog *getInstance();
  static QString getDirDebug()             {return QCoreApplication::applicationDirPath()+"/debug/";;}

  static void saveDebugFile(QString dir="",QString comment="");
  static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString& txt);
  static bool isEnableDebug() {return enableDebug;}
};

#endif // WLLOG_H
