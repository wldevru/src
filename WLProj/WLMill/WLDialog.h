#ifndef WLDIALOG_H
#define WLDIALOG_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include "WLEnterNum.h"
#include "WLEnterString.h"

class WLDialog : public QWidget
{
	Q_OBJECT

public:
	WLDialog(QWidget *parent);
	~WLDialog();

private:

signals:	
 void enterNum(double);	
 void enterString(QString);	
 void enterCancel();	

public slots:

 void showMessage(QString txt);
 void showEnterNum(QString txt);
 void showEnterString(QString txt);
 void showSaveFile(QString txt,QString lastFile);
	
};

#endif // WLDIALOG_H
