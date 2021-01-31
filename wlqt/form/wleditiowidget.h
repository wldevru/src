#ifndef WLEDITIOPUTWIDGETT_H
#define WLEDITIOPUTWIDGETT_H

#include <QWidget>
#include <QIcon>
#include <QMessageBox>
#include "wlmoduleioput.h"
#include "wlmodulepwm.h"
#include "wlmoduleencoder.h"
#include "wlmoduleaioput.h"
#include "wlenternum.h"

namespace Ui {
class WLEditIOWidget;
}

class WLEditIOWidget : public QWidget
{
    Q_OBJECT


public:
    explicit WLEditIOWidget(QWidget *parent = nullptr);
    ~WLEditIOWidget();

    void setModule(WLModule *_Module,bool _input=true);
    void setLabel(QString label);

    void setValue(int val);
    int  value();

    WLIOPut   *getIOPut();
    WLEncoder *getEncoder();
    WLPWM     *getPWM();

    bool isChecked();
    bool isEnable();

    QAbstractButton *getButton();

private:
    Ui::WLEditIOWidget *ui;

    bool m_input;
    bool m_enLatchInput;

WLModule *m_Module;

private slots:
   void update();

   void togInvers();

   void onActTogInvers();
   void onActLatchInput();
   void onActResetEncoder();
   void onActSetFreq();

   void setLatchInput(int);

public slots:
   void setCheckable(bool enable);
   void setChecked(bool check);

signals:
   void toggle(bool);
   // QWidget interface   
protected:   
   void mousePressEvent(QMouseEvent *event);
};

#endif // WLEDITIOPUTWIDGETT_H
