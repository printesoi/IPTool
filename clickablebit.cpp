/* ============================================================
*
* Date        : 2012-10-27
* Description : A simple GUI program written in Qt to calculate network
                adress and broadcast address given the IP and the mask
*
* Copyright (C) 2012 Dodon Victor <victor dot dodon at cti dot pub dot ro>
*
* This program is free software; you can redistribute it
* and/or modify it under the terms of the GNU General
* Public License as published by the Free Software Foundation;
* either version 2, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* ============================================================ */

#include <QMouseEvent>
#include "clickablebit.h"

ClickableBit::ClickableBit(QWidget *parent) :
    QLabel(parent)
{
    QWidget* widget = parent ? parent : this;
    int width = widget->fontMetrics().width('0');
    setFixedWidth(width);

    setTextInteractionFlags(Qt::NoTextInteraction);
    setNum(0);
}

void ClickableBit::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        toggleValue();
        emit clicked(text().toInt());
    }
}

void ClickableBit::slotSetValue(int value)
{
    setNum(value ? 1 : 0);
    emit valueChanged(text().toInt());
}

void ClickableBit::toggleValue()
{
    setNum(text() == QString("0") ? 1 : 0);
}
