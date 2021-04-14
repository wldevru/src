#ifndef WLDOUBLESPINBOX_H
#define WLDOUBLESPINBOX_H

#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QRegExpValidator>
#include <QDoubleSpinBox>

class WLDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit WLDoubleSpinBox(QWidget *parent = nullptr);


private:
    QRegExpValidator* validator;

signals:

public slots:

    // QDoubleSpinBox interface
public:
    double valueFromText(const QString &text) const;
    QString textFromValue(double val) const;

    virtual QValidator::State validate(QString & text, int & pos) const;
};

#endif // WLDOUBLESPINBOX_H
