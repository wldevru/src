#ifndef WLFILEACCESS_H
#define WLFILEACCESS_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QMutex>
#include <QScriptValue>


class WLFileAccess : public QObject
{
	Q_OBJECT

public:
	WLFileAccess(QObject *parent);
	~WLFileAccess();

Q_INVOKABLE QScriptValue loadVal(QString namefile,QString nameData);
Q_INVOKABLE bool saveVal(QString namefile,QString nameData,QScriptValue data);

Q_INVOKABLE bool createFile(QString namefile);
Q_INVOKABLE bool write(QString namefile,QString str);
private:
	QMutex mutex;
};

#endif // WLFILEACCESS_H
