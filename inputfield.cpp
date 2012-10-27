/* ============================================================
*
* Date        : 2012-10-27
* Description : A simple GUI program written in Qt to calculate network
                adress and broadcast address given the IP and the mask
*
* Copyright (C) 2012 Dodon Victor <victordodon at gmail dot com>
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
