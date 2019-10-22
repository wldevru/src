#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "WLMotion.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

  WLMotion *MDevice;

private:
    Ui::Widget *ui;

private slots:
    void togOut3();
    void movA0();

};

#endif // WIDGET_H
