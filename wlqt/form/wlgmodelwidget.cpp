#include "wlgmodelwidget.h"
#include "ui_wlgmodelwidget.h"

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
