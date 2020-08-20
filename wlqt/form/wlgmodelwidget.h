#ifndef WLGMODELWIDGETT_H
#define WLGMODELWIDGETT_H

#include <QWidget>

namespace Ui {
class WLGModelWidget;
}

class WLGModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WLGModelWidget(QWidget *parent = nullptr);
    ~WLGModelWidget();

private:
    Ui::WLGModelWidget *ui;
};

#endif // WLGMODELWIDGETT_H
