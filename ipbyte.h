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

#ifndef IPBYTE_H
#define IPBYTE_H

#include <QWidget>
#include <QVector>
#include <stdint.h>
#include "clickablebit.h"

class QGridLayout;
class InputField;

class IPByte : public QWidget
{
    Q_OBJECT
public:
    explicit IPByte(QWidget *parent = 0);
    virtual ~IPByte();
    void focus();
    uint8_t byte();
    void clear();
    
signals:
    void full(char c);
    void full(bool);
    void byteChanged(uint8_t);

private slots:
    void slotBitClicked(int value);
    void slotTextChanged(QString);
    void slotFocus(bool);
    
private:
    void updateText();
    void updateBits(uint8_t value);
    void setByte(uint8_t byte);

private:
    QGridLayout* m_layout;
    InputField* m_lineEdit;
    QVector<ClickableBit*> m_bits;

    uint8_t m_byte;
};

#endif // IPBYTE_H
