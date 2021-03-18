#include "wleditgcode.h"
#include "ui_wleditgcode.h"

WLEditGCode::WLEditGCode(WLGCode *_gcode,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WLEditGCode)
{
    ui->setupUi(this);

    gcode=_gcode;

    ui->strBeforeProgram->setText(gcode->getStrBeforeProgram());
    ui->strAfterProgram->setText(gcode->getStrAfterProgram());

    ui->sbOffsetDrill->setValue(gcode->getOffsetBackLongDrill());
}

WLEditGCode::~WLEditGCode()
{
    delete ui;
}

void WLEditGCode::saveDataGCode()
{
gcode->setStrAfterProgram(ui->strAfterProgram->text());
gcode->setStrBeforeProgram(ui->strBeforeProgram->text());
gcode->setOffsetBackLongDrill(ui->sbOffsetDrill->value());
}

void WLEditGCode::accept()
{
saveDataGCode();
}
