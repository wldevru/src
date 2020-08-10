#ifndef WLEDITIOPUTWIDGETT_H
#define WLEDITIOPUTWIDGETT_H

#include <QWidget>
#include <QIcon>
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
private:
    Ui::WLEditIOPutWidget *ui;
    WLModuleIOPut *ModuleIOPut;

    bool m_input;

private slots:
   void update();

};

#endif // WLEDITIOPUTWIDGETT_H
