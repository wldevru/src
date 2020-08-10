#ifndef WLEDITIOPUTWIDGETT_H
#define WLEDITIOPUTWIDGETT_H

#include <QWidget>
#include <QIcon>
#include <QMessageBox>
#include "WLModuleIOPut.h"

namespace Ui {
class WLEditIOPutWidget;
}

class WLEditIOPutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WLEditIOPutWidget(QWidget *parent = nullptr);
    ~WLEditIOPutWidget();

    void setModuleIOPut(WLModuleIOPut *_ModuleIOPut,bool _input=true);
    void setLabel(QString label);

    void setValue(int val);
    int  value();

    WLIOPut *getIOPut() {return  m_input ? m_ModuleIOPut->getInputV(value()): m_ModuleIOPut->getOutputV(value());}

private:
    Ui::WLEditIOPutWidget *ui;
    WLModuleIOPut *m_ModuleIOPut;

    bool m_input;

private slots:
   void update();

   void togInvers() {getIOPut()->togInv();}



   // QWidget interface
protected:
   void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // WLEDITIOPUTWIDGETT_H
