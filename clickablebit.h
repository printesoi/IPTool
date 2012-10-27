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
