#include <QFocusEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QDebug>
#include "inputfield.h"

InputField::InputField(QWidget *parent) :
    QLineEdit(parent)
{
}

void InputField::focusOutEvent(QFocusEvent *e)
{
    if (e->lostFocus())
    {
        emit lostFocus(true);
        deselect();
        clearFocus();
        QLineEdit::focusOutEvent(e);
        if (text().isEmpty())
            setText(QString("0"));
    }
    else
        emit lostFocus(false);
}

void InputField::mousePressEvent(QMouseEvent *)
{
    selectAll();
}
