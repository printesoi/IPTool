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
#include <QLabel>
#include <QDebug>
#include <QSpinBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include "mainwindow.h"
#include "ipbyte.h"
#include "inputfield.h"
#include "ipv4.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_mainLayout(0), m_ip(0)
{
    m_mainLayout = new QGridLayout();
    m_ip = new IPv4();

    makeMenus();

    QLabel* ipLabel = new QLabel(this);
    ipLabel->setText("IP address:");
    byte0 = new IPByte(this);
    byte1 = new IPByte(this);
    byte2 = new IPByte(this);
    byte3 = new IPByte(this);

    m_mainLayout->addWidget(ipLabel, 0, 0, 1, 1);
    m_mainLayout->addWidget(byte0, 0, 1, 1, 1, Qt::AlignHCenter);
    m_mainLayout->addWidget(byte1, 0, 2, 1, 1, Qt::AlignHCenter);
    m_mainLayout->addWidget(byte2, 0, 3, 1, 1, Qt::AlignHCenter);
    m_mainLayout->addWidget(byte3, 0, 4, 1, 1, Qt::AlignHCenter);
    byte0->focus();

    connect(byte0, SIGNAL(byteChanged(uint8_t)),
            this, SLOT(slotAddressChanged()));
    connect(byte1, SIGNAL(byteChanged(uint8_t)),
            this, SLOT(slotAddressChanged()));
    connect(byte2, SIGNAL(byteChanged(uint8_t)),
            this, SLOT(slotAddressChanged()));
    connect(byte3, SIGNAL(byteChanged(uint8_t)),
            this, SLOT(slotAddressChanged()));

    QLabel* maskLabel = new QLabel(this);
    maskLabel->setText("/");

    QSpinBox* maskBox = new QSpinBox(this);
    maskBox->setMinimum(0);
    maskBox->setMaximum(32);
    maskBox->setValue(8);
    connect(maskBox, SIGNAL(valueChanged(int)),
            this, SLOT(slotMaskChanged(int)));

    m_mainLayout->addWidget(maskLabel, 0, 5, 1, 1);
    m_mainLayout->addWidget(maskBox,   0, 6, 1, 1);

    connect(byte0, SIGNAL(full(bool)),
            byte1, SLOT(slotFocus(bool)));
    connect(byte1, SIGNAL(full(bool)),
            byte2, SLOT(slotFocus(bool)));
    connect(byte2, SIGNAL(full(bool)),
            byte3, SLOT(slotFocus(bool)));

    netAddr = QVector<InputField*>(4);
    QLabel* netLabel = new QLabel(this);
    netLabel->setText("Network address:");
    m_mainLayout->addWidget(netLabel, 1, 0, 1, 1);
    for (int i = 0; i < 4; ++i)
    {
        netAddr[i] = new InputField(this);
        netAddr[i]->setEnabled(false);
        netAddr[i]->setAlignment(Qt::AlignCenter);
        m_mainLayout->addWidget(netAddr[i], 1, i + 1, 1, 1);
    }

    broadcastAddr = QVector<InputField*>(4);
    QLabel* bcastAddr = new QLabel(this);
    bcastAddr->setText("Broadcast address:");
    m_mainLayout->addWidget(bcastAddr, 2, 0, 1, 1);
    for (int i = 0; i < 4; ++i)
    {
        broadcastAddr[i] = new InputField(this);
        broadcastAddr[i]->setEnabled(false);
        broadcastAddr[i]->setAlignment(Qt::AlignCenter);
        m_mainLayout->addWidget(broadcastAddr[i], 2, i + 1, 1, 1);
    }

    QWidget *widget = new QWidget;
    widget->setLayout(m_mainLayout);
    setCentralWidget(widget);

    slotMaskChanged(maskBox->value());
    updateAdresses();
}

MainWindow::~MainWindow()
{
    delete m_ip;
}

void MainWindow::slotMaskChanged(int val)
{
    uint8_t prefix = val & 0xFF;
    m_ip->setPrefix(prefix);
    updateAdresses();
}

void MainWindow::slotAddressChanged()
{
    m_ip->setAddr(byte0->byte() << 24 | byte1->byte() << 16 | byte2->byte() << 8 | byte3->byte());
    updateAdresses();
}

void MainWindow::updateAdresses()
{
    for (int i = 0; i < 4; ++i)
    {
        netAddr[i]->setText(QString("%1").arg(m_ip->networkAddress() >> (24 - i * 8) & 0xFF));
        broadcastAddr[i]->setText(QString("%1").arg(m_ip->broadcastAddress() >> (24 - i * 8) & 0xFF));
    }
}

void MainWindow::makeMenus()
{
    QMenu* fileMenu = menuBar()->addMenu("File");
    QMenu* helpMenu = menuBar()->addMenu("Help");

    QAction* clearAction = fileMenu->addAction("Clear IP");
    QAction* quitAction = fileMenu->addAction("Quit");
    QAction* helpAction = helpMenu->addAction("About");

    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    helpAction->setShortcut(QKeySequence(Qt::Key_F1));
    clearAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));

    connect(clearAction, SIGNAL(triggered(bool)),
            this, SLOT(slotClear()));
    connect(quitAction, SIGNAL(triggered(bool)),
            this, SLOT(slotQuit()));
    connect(helpAction, SIGNAL(triggered(bool)),
            this, SLOT(slotHelp()));
}

void MainWindow::slotClear()
{
    byte0->clear();
    byte1->clear();
    byte2->clear();
    byte3->clear();
    byte0->focus();
}

void MainWindow::slotHelp()
{
    QMessageBox box;
    QString text = "A simple tool to calculate network addresses, \n"
                   "and broadcast addresses for given IP.\n\n"
                   "(C) Victor Dodon, 2012, victor.dodon@cti.pub.ro";
    box.setInformativeText(text);
    box.setMinimumWidth(300);
    box.exec();
    byte0->focus();
}

void MainWindow::slotQuit()
{
    close();
}
