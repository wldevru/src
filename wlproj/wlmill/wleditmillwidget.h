#ifndef WLEDITMILLWIDGET_H
#define WLEDITMILLWIDGET_H

#include <QWidget>
#include <QSerialPortInfo>

#include "wlmillmachine.h"
#include "ui_wleditmillwidget.h"


class WLEditMillWidget : public QDialog
{
	Q_OBJECT

public:
	WLEditMillWidget(WLMillMachine *_MillMachine,QDialog *parent = 0);
	~WLEditMillWidget();

void saveData();

private:
	WLMillMachine *MillMachine;

	Ui::WLEditMillWidget ui;

private:
   void initTableCorrectS();
   QList <SCorrectSOut> getCorrectSList();

private slots:
	void onVerifyError();
    void onAccept() {done(1);}
    void onReject() {done(0);}
    //void updatePort();
    //void onSetPort();


};

#endif // WLEDITMILLWIDGET_H
