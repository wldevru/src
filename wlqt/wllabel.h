#ifndef WLLABEL_H
#define WLLABEL_H

#include <QLabel>
#include <QString>

class WLLabel : public QLabel
{
	Q_OBJECT

public:
	WLLabel(QWidget *parent);
    WLLabel(QString m_prefix,QString m_suffix="",double m_data=0,int m_n=0);
	
	~WLLabel();

void setPrefix(QString str) {m_prefix=str;}
void setSuffix(QString str) {m_suffix=str;}

QString getPrefix() {return m_prefix;}

void setPSfix(QString Pstr,QString Sstr) {setPrefix(Pstr);setSuffix(Sstr);}

void setData(double d,int m_n=0);
void setData(QString txt);
void setDataN(int _n) {m_n=_n;}

void setPS(QString pr,QString su) {m_prefix=pr;m_suffix=su;}

double getData();

private:
    QString m_prefix;
    QString m_suffix;
    double m_data;
    int m_n;

public slots:

    void setDataD(double d){setData(d,m_n);}
    void setData(float d)  {setData(d,m_n);}
	void setData(long l)   {setData(l,0);}
	void setData(int i)    {setData(i,0);}
    void setText(QString txt);

protected:
	virtual	void mouseDoubleClickEvent ( QMouseEvent * event ) {emit dclicked(); QLabel::mouseDoubleClickEvent(event);}
    void mousePressEvent(QMouseEvent *event)                   {emit  clicked(); QLabel::mousePressEvent(event);}

signals:
	void dclicked();
    void  clicked();

    // QWidget interface
protected:

};

#endif // WLLABEL_H
