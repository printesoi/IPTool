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
