#ifndef WLMILLDRIVEDIALOG_H
#define WLMILLDRIVEDIALOG_H

#include <QDialog>
#include "wlmilldrive.h"
#include "ui_wlmilldrivewidget.h"

namespace Ui {
class WLMillDriveWidget;
}

class WLMillDriveWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLMillDriveWidget(WLMillDrive *_drive,QWidget *parent = nullptr);
    ~WLMillDriveWidget();

private:
    Ui::WLMillDriveWidget *ui;

    WLMillDrive *m_MDrive;

    // QDialog interface
public slots:
    void accept() {m_MDrive->setBacklash(ui->sbBacklash->value());}
};

#endif // WLMILLDRIVEDIALOG_H
