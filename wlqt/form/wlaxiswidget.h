#ifndef WLAXISWIDGET_H
#define WLAXISWIDGET_H

#include <QDialog>

#include "wlaxis.h"

namespace Ui {
class WLAxisWidget;
}

class WLAxisWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLAxisWidget(WLAxis *_axis,bool main,double _offset,QWidget *parent = nullptr);
    ~WLAxisWidget();

public:
    void saveDataAxis();
    double getOffset();

    bool isUniqueInputs();
    bool isUniqueOutputs();

    double geDelaytSCurveMs();

    WLAxis *getAxis() {return m_axis;}

    quint8 getIndexInPEL();
    quint8 getIndexInMEL();
    quint8 getIndexInORG();
    quint8 getIndexInALM();

    quint8 getIndexOutENB();
    quint8 getIndexOutRALM();

    typeActIOPutAxis getActInPEL();
    typeActIOPutAxis getActInMEL();
    typeActIOPutAxis getActInALM();
private:
    Ui::WLAxisWidget *ui;

    WLAxis *m_axis;
    bool m_slave;

public slots:
    void accept() {saveDataAxis();}
    void setUnit(QString);
};

#endif // WLAXISWIDGET_H
