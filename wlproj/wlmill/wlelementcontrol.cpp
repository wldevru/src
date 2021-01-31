#include "wlelementcontrol.h"
#include "ui_wlelementcontrol.h"

WLElementControl::WLElementControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLElementControl)
{
    ui->setupUi(this);    
}

WLElementControl::~WLElementControl()
{
    delete ui;
}

void WLElementControl::setWidget(QWidget *w)
{
w->setParent(this);
ui->horizontalLayout->addWidget(w,1);
}
