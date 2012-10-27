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

#ifndef IPV4_H
#define IPV4_H

#include <stdint.h>

class QString;

class IPv4
{
public:

    enum {
        BINARY = 2,
        OCTAL = 8,
        DECIMAL = 10,
        HEXA = 16
    };

    IPv4();
    IPv4(uint32_t addr);
    IPv4(uint32_t addr, uint32_t mask);
    IPv4(uint32_t addr, uint8_t prefix);

    void setAddr(uint32_t addr);
    void setNetMask(uint32_t mask);
    void setPrefix(uint8_t prefix);

    uint32_t address();
    uint32_t netMask();
    uint8_t  prefix();

    uint32_t networkAddress();
    uint32_t broadcastAddress();

    bool isValid();
    QString formattedAdrress(uint8_t base = DECIMAL);

private:
    uint32_t maskFromPrefix(uint8_t prefix);
    uint8_t prefixFromMask(uint32_t mask);

    uint32_t defaultMask(uint32_t addr);
    uint8_t  defaultPrefix(uint32_t addr);

    void updateAllFields();

private:
    uint32_t m_addr;
    uint32_t m_mask;
    uint8_t  m_prefix;

    uint32_t m_netAddr;
    uint32_t m_broadcastAddr;
};

#endif // IPV4_H
