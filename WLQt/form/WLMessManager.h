#ifndef WLMESSMANAGER_H
#define WLMESSMANAGER_H

#include <QWidget>
#include <QTime>
#include <QMessageBox>
#include <QMutex>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QTimer>
#include "ui_WLMessManager.h"

struct errData
{
QTime   time;
QString name;
QString mess;
int code;
int count;

};

class WLMessManager : public QWidget
{
	Q_OBJECT

public:
	WLMessManager(QWidget *parent = 0);
	~WLMessManager();


private:
	Ui::WLMessManager ui;

	QMutex mutex;
	QMutex mutexShow;
	QMutex mutexLog;

	QList <struct errData> List;

	QIcon *IconOn;
	QIcon *IconOff;

	QPixmap pixmap;

	QTimer *flashTimer;
	bool cur;
    int  count_flash;
private:
	void updateList();

private slots:
	void clear();
	void updateFlash();

public slots:
	void  setMessage(QString,QString,int);
    void  setMessage(QString txt,int code) {setMessage(txt,"",code);};
    void  setMessage(QString txt)          {setMessage(txt,"",0);}

signals:
    void saveLog(QString,QString);

};

#endif // WLMESSMANAGER_H
