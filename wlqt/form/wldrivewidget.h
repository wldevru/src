#ifndef WLDRIVEWIDGET_H
#define WLDRIVEWIDGET_H

#include <QDialog>
#include <QMessageBox>
#include "wldrive.h"
#include "wlpamlistwidget.h"
#include "wlaxiswidget.h"

#include "ui_wldrivewidget.h"

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
    void insertTabWidget(int index,QDialog *dialog,QString name) {ui.tabWidget->insertTab(index,dialog,name);}

    QString verifyError();
    QString getUnit() {return m_unit;}
private:
    Ui::WLDriveWidget ui;

    WLPamListWidget *m_PamTab;

    WLDrive *m_Drive;
    WLDriveDim m_ddim;

    QList <WLAxisWidget*> axisWidgetList;
    QString m_unit;
public:

 void saveDataDrive();

private slots:

    void updateUnit();
    void updateTabAxis();

	void updateCBDimm(int);
	void updateCBTypePulse(int);

    void updateFindLogic(int);

    void updateLabelSDDist();
	void onVerifyError();

    void onCorrectStepSize();

    // QDialog interface
public slots:
    void accept();

signals:
void changedUnit(QString);

// QWidget interface
protected:
void keyPressEvent(QKeyEvent *event);
};

#endif // WLDRIVEWIDGET_H
