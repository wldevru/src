#ifndef WLGMODELWIDGET_H
#define WLGMODELWIDGET_H

#include <QDialog>
#include "wlgmodel.h"

namespace Ui {
class WLGModelWidget;
}

class WLGModelWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLGModelWidget(WLGModel *_GModel,QWidget *parent = nullptr);
    ~WLGModelWidget();

private:
    Ui::WLGModelWidget *ui;

    WLGModel *m_GModel;

private:
    void createTable();
    void saveData();

    // QDialog interface
public slots:
    void accept() {saveData(); done(1);}
    void reject() {done(0);}
};

#endif // WLGMODELWIDGET_H
