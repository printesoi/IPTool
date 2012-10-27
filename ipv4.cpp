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

#include <QString>
#include "ipv4.h"

// constructors ============================================================

IPv4::IPv4()
{
    setAddr(0);
    setNetMask(0);
    setPrefix(0);
    updateAllFields();
}

IPv4::IPv4(uint32_t addr)
{
    setAddr(addr);
    setNetMask(defaultMask(addr));
    setPrefix(defaultPrefix(addr));
    updateAllFields();
}

IPv4::IPv4(uint32_t addr, uint32_t mask)
{
    setAddr(addr);
    setNetMask(mask);
    setPrefix(prefixFromMask(mask));
    updateAllFields();
}

IPv4::IPv4(uint32_t addr, uint8_t prefix)
{
    setAddr(addr);
    setNetMask(maskFromPrefix(prefix));
    setPrefix(prefix);
    updateAllFields();
}

// public methods =========================================================

void IPv4::setAddr(uint32_t addr)
{
    m_addr = addr;
    updateAllFields();
}

void IPv4::setNetMask(uint32_t mask)
{
    m_mask = mask;
    updateAllFields();
}

void IPv4::setPrefix(uint8_t prefix)
{
    if (prefix > 32)
        return;

    m_prefix = prefix;
    m_mask = maskFromPrefix(prefix);
    updateAllFields();
}

uint32_t IPv4::address()
{
    return m_addr;
}

uint32_t IPv4::netMask()
{
    return m_mask;
}

uint8_t IPv4::prefix()
{
    return m_prefix;
}

uint32_t IPv4::networkAddress()
{
    return m_netAddr;
}

uint32_t IPv4::broadcastAddress()
{
    return m_broadcastAddr;
}

bool IPv4::isValid()
{
    return true;
}

QString IPv4::formattedAdrress(uint8_t base)
{
    QString str("");
    uint8_t byte1 = (m_addr >> 24) & 0xFF;
    uint8_t byte2 = (m_addr >> 16) & 0xFF;
    uint8_t byte3 = (m_addr >> 8) & 0xFF;
    uint8_t byte4 = m_addr & 0xFF;

    switch (base)
    {
    case DECIMAL:
    case BINARY:
    case OCTAL:
    case HEXA:
        str = QString("%1.%2.%3.%4").arg(byte1, 0, base)
                .arg(byte2, 0, base)
                .arg(byte3, 0, base)
                .arg(byte4, 0, base);
        break;
    }

    return str;
}

// private methods ==========================================================

uint32_t IPv4::defaultMask(uint32_t addr)
{
    return maskFromPrefix(defaultPrefix(addr));
}

uint8_t IPv4::defaultPrefix(uint32_t addr)
{
    uint8_t firstByte = (addr >> 24) & 0xFF;
    if (firstByte < 0x80)
        return 8;
    else if (firstByte < 0xC0)
        return 16;
    return 24;
}

uint32_t IPv4::maskFromPrefix(uint8_t prefix)
{
    if (prefix > 32)
        return 0;

    uint32_t mask = 0;
    for (int i = 0; i < prefix; ++i)
        mask |= (1 << (31 - i));

    return mask;
}

uint8_t IPv4::prefixFromMask(uint32_t mask)
{
    uint8_t prefix = 0;
    int8_t i = 31;

    while ((i >= 0) && (mask & (1 << i)))
    {
        --i;
        ++prefix;
    }

    return prefix;
}

void IPv4::updateAllFields()
{
    m_netAddr = m_addr & m_mask;

    uint32_t hostPart = 0xFFFFFFFF ^ m_mask;
    m_broadcastAddr = m_netAddr | hostPart;
}
