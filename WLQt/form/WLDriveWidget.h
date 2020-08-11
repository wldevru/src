#ifndef WLAXISWIDGET_H
#define WLAXISWIDGET_H

#include <QDialog>
#include <QMessageBox>
#include "WLDrive.h"
#include "WLPamListWidget.h"

#include "ui_WLDriveWidget.h"

namespace Ui {
class WLDriveWidget;
}

class WLDriveWidget : public QDialog
{
	Q_OBJECT

public:
    WLDriveWidget(WLDrive *_Drive,QWidget *parent = nullptr);
    ~WLDriveWidget();


    void addTabWidget(QDialog *dialog,QString name) {ui.tabWidget->addTab(dialog,name);}
private:
    Ui::WLDriveWidget ui;

    WLDrive *m_Drive;
    WLDriveDim m_ddim;

public:

 void saveDataDrive();

private slots:

	void updateCBDimm(int);
	void updateCBTypePulse(int);

    void updateFindLogic(int);

	void updateLabelSDDist(double V);
	void onVerifyError();


    // QDialog interface
public slots:
    void accept();
};

#endif // WLAXISWIDGET_H
