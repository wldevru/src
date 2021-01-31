#ifndef WLELEMENTCONTROL_H
#define WLELEMENTCONTROL_H

#include <QWidget>

namespace Ui {
class WLElementControl;
}

class WLElementControl : public QWidget
{
    Q_OBJECT

public:
    explicit WLElementControl(QWidget *parent = nullptr);
    ~WLElementControl();

    void setWidget(QWidget *w);

private:
    Ui::WLElementControl *ui;
};

#endif // WLELEMENTCONTROL_H
