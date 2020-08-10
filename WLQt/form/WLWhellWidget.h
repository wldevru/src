#ifndef WLWHELLWIDGET_H
#define WLWHELLWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include "WLWhell.h"
#include "WLModuleIOPut.h"
#include "WLEditIOPutWidget.h"

namespace Ui {
class WLWhellWidget;
}

class WLWhellWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLWhellWidget(WLWhell *_Whell,WLModuleIOPut *_ModuleIOPut, QWidget *parent = nullptr);
    ~WLWhellWidget();

    void saveData();
private:
    Ui::WLWhellWidget *ui;

    WLModuleIOPut *ModuleIOPut;
    WLWhell       *Whell;

    QList <WLEditIOPutWidget*> ListEIWAxis;
    QList <WLEditIOPutWidget*> ListEIWX;

private:

void createInputs();
};

#endif // WLWHELLWIDGET_H
