#include "WLGModelWidgett.h"
#include "ui_WLGModelWidget.h"

WLGModelWidget::WLGModelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLGModelWidget)
{
    ui->setupUi(this);
}

WLGModelWidget::~WLGModelWidget()
{
    delete ui;
}
