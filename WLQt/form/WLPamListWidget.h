#ifndef WLPAMLISTWIDGET_H
#define WLPAMLISTWIDGET_H

#include <QDialog>
#include "WLPamWidget.h"
#include "WLDrive.h"


namespace Ui {
class WLPamListWidget;
}

class WLPamListWidget : public QDialog
{
    Q_OBJECT

public:
    explicit WLPamListWidget(WLDrive *_drive,QWidget *parent = nullptr);
    ~WLPamListWidget();

    QList <dataPad> getPadList() {return padList;}

    void setEnabledEditVst(bool en) {m_editVst=en;}

private:
    QList <dataPad> padList;
    Ui::WLPamListWidget *ui;

    WLDrive *m_Drive;
    bool m_editVst;

private slots:
    void updateTable();
    void remove();
    void add();
    void edit(int row,int count);

    // QDialog interface
public slots:
    void accept() {m_Drive->pad()->setDataList(getPadList());}
};

#endif // WLPAMLISTWIDGET_H
