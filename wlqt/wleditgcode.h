#ifndef WLEDITGCODE_H
#define WLEDITGCODE_H

#include <QDialog>
#include "wlgcode.h"

namespace Ui {
class WLEditGCode;
}

class WLEditGCode : public QDialog
{
    Q_OBJECT

public:
    explicit WLEditGCode(WLGCode *_gcode,QWidget *parent = nullptr);
    ~WLEditGCode();

private:
    Ui::WLEditGCode *ui;

    WLGCode *gcode;

private:

void saveDataGCode();
    // QDialog interface
public slots:
    void accept();
};

#endif // WLEDITGCODE_H
