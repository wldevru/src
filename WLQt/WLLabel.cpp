#include "WLLabel.h"

WLLabel::WLLabel(QWidget *parent)
	: QLabel(parent)
{
setPrefix("");
setSuffix("");
setData(0);
}

WLLabel::WLLabel(QString prefix,QString suffix,double data,int n)
{
Prefix=prefix;
Suffix=suffix;
setData(data,n);
}

WLLabel::~WLLabel()
{

}

void setDataLong(long);
void setDataDouble(long);

void WLLabel::setData(double d,int _n)
{
m_data=d;
m_n=_n;
setText(QString("%1").arg((m_data),0,'f',m_n));
}

double WLLabel::getData()
{
    return m_data;
}

void WLLabel::setText(QString txt)
{
QLabel::setText(Prefix+txt+Suffix);
}

void WLLabel::setData(QString txt)
{
setText(txt);
}
