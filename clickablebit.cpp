#include <QMouseEvent>
#include "clickablebit.h"

ClickableBit::ClickableBit(QWidget *parent) :
    QLabel(parent)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    setNum(0);

    QWidget* widget = parent ? parent : this;
    int width = widget->fontMetrics().width('0');
    setFixedWidth(width);
}

void ClickableBit::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        toggleValue();
    }
}

void ClickableBit::slotSetValue(int value)
{
    int bit = value ? 1 : 0;
    setNum(bit);
    emit valueChanged(text().toInt());
}

void ClickableBit::toggleValue()
{
    if (text() == QString("0"))
        setNum(1);
    else
        setNum(0);
    emit clicked(text().toInt());
}
