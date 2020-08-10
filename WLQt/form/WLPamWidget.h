#ifndef WLPAMWIDGET_H
#define WLPAMWIDGET_H

#include <QDialog>
#include <QPainter>
#include <QLineEdit>
#include "WLPad.h"
#include "ui_WLPamWidget.h"


class WLPamWidget : public QDialog
{
	Q_OBJECT

public:
    WLPamWidget(dataPad Pad,float Vmax,QWidget *parent = nullptr);
	~WLPamWidget();

dataPad getPad();

private:
	Ui::WLPamWidget ui;

    dataPad curPad;

protected:

void  paintEvent(QPaintEvent *);

private slots:

 void updateAccelLabel(int index);

 void updateVstLabel(double val);
 void updateVmaLabel(double val);

    void onAccept() {done(1);}
    void onReject() {done(0);}

public slots:
  void setEnabledEditName(bool enable) {ui.cbEditName->setEnabled(enable);}
  void setEnabledEditVst(bool enable)  {ui.sbVst->setEnabled(enable);}
};

#endif // WLPAMWIDGET_H
