#ifndef WLDEVICEWIDGET_H
#define WLDEVICEWIDGET_H


#include <QDialog>
#include <QList>

#include "wldevice.h"
#include "ui_wldevicewidget.h"

namespace Ui {
class WLDeviceWidget;
}

class WLDeviceWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLDeviceWidget(QWidget *parent = nullptr);
    ~WLDeviceWidget();


private:
    Ui::WLDeviceWidget *ui;

QList<WLDeviceInfo> m_ListInfo;

public:

WLDeviceInfo getDeviceInfo() {return m_ListInfo.isEmpty() ? WLDeviceInfo():m_ListInfo[ui->cbDevice->currentIndex()];}

protected:

private slots:

    void updateList();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


public slots:
    void setLabel(QString txt) {ui->label->setText(txt);}
};

#endif // WLDEVICEWIDGET_H
