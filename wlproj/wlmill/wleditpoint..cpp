#include "wleditpoint.h"

WLEditPoint::WLEditPoint()
{
	ui.setupUi(this);

    setWindowTitle(tr("Enter Point"));

	connect(ui.pushButtonCancle,SIGNAL(clicked()),SLOT(close()));
	connect(ui.pushButtonOk,SIGNAL(clicked()),SLOT(onOk()));

	setModal(true);
	
}

WLEditPoint::~WLEditPoint()
{

}


void WLEditPoint::setNameData(QString name)
{
QStringList List=name.split(",");
QHBoxLayout *hLayout;
WLEditPointData Data;

for(int i=0;i<List.size();i++)
    {
    Data.label=new QLabel(List[i],this);
    Data.sb=new QDoubleSpinBox(this);

    Data.sb->setRange(-100000,100000);

    hLayout = new QHBoxLayout;
    hLayout->addWidget(Data.label);
    hLayout->addWidget(Data.sb);

    dataList+=Data;
    ui.verticalLayout->addLayout(hLayout);
}
}

void WLEditPoint::setValueStr(QString value)
{
QStringList List=value.split(",");

valueString=value;

foreach(QString str,List)
{
QStringList valList=str.split(" ");

foreach(WLEditPointData data,dataList)
 {
 if(data.label->text()==valList.first())
    {
    data.sb->setValue(valList.last().toDouble());
    break;
    }
 }
}
}

QString WLEditPoint::getValueStr()
{
QString ret;
QStringList List=valueString.split(",");

for(int i=0;i<List.size();i++)
{
QStringList valList=List[i].split(" ");

foreach(WLEditPointData data,dataList)
 {
 if(data.label->text()==valList.first())
    {
    List[i]=valList.first()+" "+QString::number(data.sb->value());
    break;
    }
 }
 if(!ret.isEmpty()) ret+=",";
 ret+=List[i];
}

return ret;
}
