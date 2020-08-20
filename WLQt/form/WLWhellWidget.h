#ifndef WLWHELLWIDGET_H
#define WLWHELLWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include "wlwhell.h"
#include "wlmoduleioput.h"
#include "wleditiowidget.h"

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

    QList <WLEditIOWidget*> ListEIWAxis;
    QList <WLEditIOWidget*> ListEIWX;

private:

void createInputs();
};

#endif // WLWHELLWIDGET_H
