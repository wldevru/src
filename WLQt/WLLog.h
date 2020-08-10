#ifndef WLLOG_H
#define WLLOG_H

#include <QMutex>
#include <QDir>
#include <QTextStream>
#include <qdatetime.h>
#include <QObject>
#include <QDebug>
#include <QApplication>

class WLLog : public QObject
{
	Q_OBJECT

public:
    WLLog(QObject *parent=nullptr);
	~WLLog();

   void setDirLog(QString _dir) {if(!_dir.isEmpty()) m_dir=_dir;}
QString getDirLog()            {return m_dir;}

private:
     QMutex m_mutex;
    QString m_dir;
	
public slots:
	void  writeLog(QString Name,QString Data);
};

#endif // WLLOG_H
