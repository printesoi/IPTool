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

#include <QGridLayout>
#include <QFocusEvent>
#include <QDebug>
#include "ipbyte.h"
#include "inputfield.h"

IPByte::IPByte(QWidget *parent) :
    QWidget(parent), m_layout(0), m_lineEdit(0), m_bits(8)
{
    setByte(0);

    setFixedWidth(100);
    setFixedHeight(50);

    m_layout = new QGridLayout(this);
    m_lineEdit = new InputField(this);
    m_lineEdit->setAlignment(Qt::AlignHCenter);
    updateText();

    QWidget* widget = parent ? parent : this;
    int height = widget->fontMetrics().height() + 5;
    m_lineEdit->setFixedHeight(height);

    m_layout->addWidget(m_lineEdit, 0, 0, 1, 8);
    for (int i = 0; i < 8; ++i)
    {
        m_bits[i] = new ClickableBit(this);
        m_layout->addWidget(m_bits[i], 1, i, 1, 1);
        connect(m_bits[i], SIGNAL(clicked(int)),
                this, SLOT(slotBitClicked(int)));
    }

    connect(m_lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(slotTextChanged(QString)));
}

IPByte::~IPByte()
{
}

void IPByte::updateText()
{
    m_lineEdit->setText(QString("%1").arg(m_byte));
}

void IPByte::slotBitClicked(int value)
{
    uint8_t _bit = value ? 1 : 0;
    int index = 7 - m_bits.indexOf(static_cast<ClickableBit*>(sender()));
    if (index >= 0)
    {
        if (_bit)
            setByte(m_byte | (1 << index));
        else
            setByte(m_byte &= (0xFF ^ (1 << index)));
        updateText();
    }
}

void IPByte::updateBits(uint8_t value)
{
    for (int i = 0; i < 8; ++i)
    {
        uint8_t bit = (value >> (7 - i)) & 1;
        m_bits[i]->slotSetValue(bit);
    }
}

void IPByte::slotTextChanged(QString text)
{
    if (m_lineEdit->text().isEmpty())
    {
        setByte(0);
        updateBits(m_byte);
        return;
    }

    bool ok;
    uint16_t value = text.toInt(&ok);
    if (!ok)
    {
        m_lineEdit->clear();
    }
    else
    {
        if (value > 0xFF)
        {
            m_lineEdit->setText(text.left(text.length() - 1));
        }
        else
        {
            if (value * 10 > 255)
            {
                emit full(true);
            }
            setByte(value & 0xFF);
            updateBits(m_byte);
        }
    }
}

void IPByte::setByte(uint8_t byte)
{
    m_byte = byte;
    emit byteChanged(byte);
}

void IPByte::focus()
{
    m_lineEdit->setFocus(Qt::MouseFocusReason);
    m_lineEdit->selectAll();
}

void IPByte::slotFocus(bool)
{
    focus();
}

uint8_t IPByte::byte()
{
    return m_byte;
}

void IPByte::clear()
{
    m_lineEdit->setText("0");
}
