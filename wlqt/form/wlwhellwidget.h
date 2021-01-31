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
    explicit WLWhellWidget(WLWhell *_Whell,WLModuleIOPut *_MIOPut,WLModuleEncoder *_MEncoder, QWidget *parent = nullptr);
    ~WLWhellWidget();

    void saveData();
private:
    Ui::WLWhellWidget *ui;

     WLWhell       *Whell;

    QList <WLEditIOWidget*> ListEIWAxis;
    QList <WLEditIOWidget*> ListEIWX;

private:

void createInputs(WLModuleIOPut *MIOPut);

private slots:

void updateIndexs();
};

#endif // WLWHELLWIDGET_H
