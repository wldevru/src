#ifndef WLTOOLSWIDGET_H
#define WLTOOLSWIDGET_H

#include <QWidget>
#include "wlgcode.h"

namespace Ui {
class WLToolsWidget;
}

class WLToolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WLToolsWidget(WLGCode *_GCode,QWidget *parent = nullptr);
    ~WLToolsWidget();

private:
    Ui::WLToolsWidget *ui;

    WLGCode *m_GCode;

private slots:
    void updateTableTools();
    void onAcceptTableTools();
    void onPBSetHToZero();
};

#endif // WLTOOLSWIDGET_H
