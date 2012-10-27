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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>

class QGridLayout;
class IPv4;
class IPByte;
class InputField;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotAddressChanged();
    void slotMaskChanged(int);

protected slots:
    void slotHelp();
    void slotClear();
    void slotQuit();

protected:
    void updateAdresses();
    void makeMenus();
    
private:
    QGridLayout* m_mainLayout;
    IPv4* m_ip;

    IPByte* byte0;
    IPByte* byte1;
    IPByte* byte2;
    IPByte* byte3;
    QVector<InputField*> netAddr;
    QVector<InputField*> broadcastAddr;


};

#endif // MAINWINDOW_H
