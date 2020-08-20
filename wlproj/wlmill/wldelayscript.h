#ifndef WLDELAY_H
#define WLDELAY_H

#include <QTimer>
#include <QThread>
#include <QDebug>

#define sizeTimers 32

class WLDelay : public QThread
{
	Q_OBJECT

public:
	WLDelay(QObject *parent);
	~WLDelay();

private:
    long m_count[sizeTimers];
    bool m_activ[sizeTimers];

    QTimer *Timer;

void run();

public:

    Q_INVOKABLE void star(int index)    {if(index<sizeTimers)    {m_activ[index]=true;}}
    Q_INVOKABLE void restart(int index) {if(index<sizeTimers)    {m_activ[index]=true;m_count[index]=0;}}
    Q_INVOKABLE void stop(int index)    {if(index<sizeTimers)    {m_activ[index]=false;}}
    Q_INVOKABLE long getCount(int index){if(index<sizeTimers)    return m_count[index]; else return -1;}

public slots:

private slots:

	//void timeEnd();
};

#endif // WLDELAY_H
