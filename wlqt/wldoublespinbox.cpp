#include "wldoublespinbox.h"

WLDoubleSpinBox::WLDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent),
    validator(new QRegExpValidator(this))
{
validator->setRegExp(QRegExp("-{0,1}\\d{1,}(?:[,.]{0,1})\\d*"));
}


QValidator::State WLDoubleSpinBox::validate(QString &text, int &pos) const
{
text.replace(",",".");

QString validText=text.mid(prefix().size(),text.size()-prefix().size()-suffix().size());

return validator->validate(validText,pos);
}

double WLDoubleSpinBox::valueFromText(const QString &text) const
{
QString txt=text.mid(prefix().size(),text.size()-prefix().size()-suffix().size());

txt.replace(",",".");

return txt.toDouble();;
}

QString WLDoubleSpinBox::textFromValue(double val) const
{
return QString::number(val,'f',decimals());
}

