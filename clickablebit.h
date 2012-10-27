#ifndef CLICKABLEBIT_H
#define CLICKABLEBIT_H

#include <QLabel>

class QMouseEvent;

class ClickableBit : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableBit(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void toggleValue();
    
signals:
    void valueChanged(int value);
    void clicked(int value);
    
public slots:
    void slotSetValue(int value);
    
};

#endif // CLICKABLEBIT_H
