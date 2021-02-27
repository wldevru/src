#ifndef WLEDITMPGWIDGET_H
#define WLEDITMPGWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include "wlmpg.h"
#include "wlmoduleioput.h"
#include "wleditiowidget.h"

namespace Ui {
class WLEditMPGWidget;
}

class WLEditMPGWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLEditMPGWidget(WLMPG *_MPG,WLModuleIOPut *_MIOPut,WLModuleEncoder *_MEncoder, QWidget *parent = nullptr);
    ~WLEditMPGWidget();

    void saveData();
private:
    Ui::WLEditMPGWidget *ui;

     WLMPG       *MPG;

    QList <WLEditIOWidget*> ListEIWAxis;
    QList <WLEditIOWidget*> ListEIWX;

private:

void createInputs(WLModuleIOPut *MIOPut);

private slots:

void updateIndexs();
};

#endif // WLEDITMPGWIDGET_H
