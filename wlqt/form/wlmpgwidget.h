#ifndef WLMPGWIDGET_H
#define WLMPGWIDGET_H

#include <QWidget>
#include <QKeyEvent>

#include "wlwhell.h"


namespace Ui {
class WLMPGWidget;
}


class WLMPGWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WLMPGWidget(WLWhell *_whell,QWidget *parent = nullptr);
    ~WLMPGWidget();

private:
    Ui::WLMPGWidget *ui;

    WLWhell *m_whell;

public slots:

    void update();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // WLMPGWIDGET_H
