#ifndef WLEVSCRIPT_H
#define WLEVSCRIPT_H

#include <QThread>
#include <QScriptEngine> 
#include <QTimer> 
#include <QDebug> 
#include "wldelayscript.h"
#include "wlfileaccess.h"
#include "wldialogscript.h"
#include "wldialogobscript.h"


class WLEVScript : public QThread
{
	Q_OBJECT

public:
	WLEVScript(QObject *parent);
	~WLEVScript();

void run();

QScriptEngine *engine;	

bool isBusy() {return busy||engine->isEvaluating();}

private:

bool busy;

WLDelay      *Delay;
WLFileAccess *FileAccess;
WLDialogObj  *Dialog;

QString code;
QString func;
QScriptValueList vList;
	
//private slots:
	//void evalCode() {qDebug()<<"retScript="<<engine->evaluate(code).toString();};
public:
	void addDialogWidget(WLDialog *DialogW);
	
	bool setCode(QString _code) ;
 QString getCode() {return code;}
    bool runFunc(QString _func) ;

public slots:
    void reset();

private slots:
	void evalCode();
	void evalFunc();

    void eval() {qDebug()<<"retScript=";}

	void setMessage(QString txt,int code) {emit sendMessage(tr("message"),txt,code);}

signals:
    void complete(QString);
    void changedBusy(bool);
	void sendMessage(QString,QString,int);
};

#endif // WLEVSCRIPT_H
