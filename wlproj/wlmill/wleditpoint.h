#ifndef WLEDITPOINT_H
#define WLEDITPOINT_H

#include <QDialog>
#include <QDoubleSpinBox>
#include "ui_wleditpoint.h"
#include "wlframe.h"

typedef struct WLEditPointData
{
QLabel *label;
QDoubleSpinBox *sb;
}WLEditPointData;

class WLEditPoint : public QDialog
{
	Q_OBJECT

public:
    WLEditPoint();
	~WLEditPoint();

	WLFrame getFrame(); 
	void setLabel(QString txt) {ui.label->setText(txt);}

    void setNameData(QString names);
    void setValueStr(QString _valueString);

    QString getValueStr();
private:
	Ui::WLEditPoint ui;

    QList <WLEditPointData> dataList;
    QString valueString;

private slots:
		void onOk() {done(1);}
};

#endif // WLEDITPOINT_H
