#ifndef WLMPGWIDGET_H
#define WLMPGWIDGET_H

#include <QWidget>
#include <QKeyEvent>

#include "wlmpg.h"

namespace Ui {
class WLMPGWidget;
}

class WLMPGWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WLMPGWidget(WLMPG *_MPG,QWidget *parent = nullptr);
    ~WLMPGWidget();

private:
    Ui::WLMPGWidget *ui;

    WLMPG *m_MPG;

public slots:

    void update();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // WLMPGWIDGET_H
