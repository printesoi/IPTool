#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include <QLineEdit>

class InputField : public QLineEdit
{
    Q_OBJECT
public:
    explicit InputField(QWidget *parent = 0);

signals:
    void lostFocus(bool);

protected:
    virtual void focusOutEvent(QFocusEvent *);
    virtual void mousePressEvent(QMouseEvent *);
};

#endif // INPUTFIELD_H
