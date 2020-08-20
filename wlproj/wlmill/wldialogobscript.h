#ifndef WLDIALOGOBJ_H
#define WLDIALOGOBJ_H

#include <QObject>
#include "wldialogscript.h"

class WLDialogObj : public QObject
{
	Q_OBJECT

public:
	WLDialogObj(QObject *parent);
	~WLDialogObj();

	//Q_INVOKABLE bool enterVal(QString txt);
Q_INVOKABLE void message(QString txt)                    {if(show) {emit sendMessage("DIALOG","last window is activ",0);}show=true;emit buildMessage(txt); };
Q_INVOKABLE void enterNum(QString txt)                   {if(show) {emit sendMessage("DIALOG","last window is activ",0);}show=true;emit buildEnterNum(txt); };
Q_INVOKABLE void enterString(QString txt)                {if(show) {emit sendMessage("DIALOG","last window is activ",0);}show=true;emit buildEnterString(txt); };
Q_INVOKABLE void enterSaveFile(QString txt,QString last) {if(show) {emit sendMessage("DIALOG","last window is activ",0);}show=true;emit buildSaveFile(txt,last); };

Q_INVOKABLE bool isShow()   {return show;};
Q_INVOKABLE bool isOk()     {return !cancel;};
Q_INVOKABLE bool isCancel() {return  cancel;};

Q_INVOKABLE double getNum() {return dataNum;};
Q_INVOKABLE QString getString() {return dataStr;};

void setWidgetDialog(WLDialog *_DialogW);
void reset();

private:
	bool show;
	bool cancel;

	 double dataNum;
	QString dataStr;

	WLDialog *DialogW;

signals:

	void buildMessage(QString);
	void buildEnterNum(QString);
    void buildEnterString(QString);
	void buildSaveFile(QString,QString);
	
	void sendMessage(QString,QString,int);

public slots:

	void setString(QString str) {show=false;cancel=false;dataStr=str;}
	void setNum(double num)     {show=false;cancel=false;dataNum=num;}
	void setCancel()            {show=false;cancel=true;}
		
};

#endif // WLDIALOGOBJ_H
