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
