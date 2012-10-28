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
    QMainWindow(parent), m_mainLayout(new QGridLayout()), m_ip(new IPv4())
{
    makeMenus();

    QLabel* ipLabel = new QLabel(this);
    ipLabel->setText("IP address:");
    m_mainLayout->addWidget(ipLabel, 0, 0, 1, 1);

    bytes = QVector<IPByte*>(4);

    for (int i = 0; i < 4; ++i)
    {
        bytes[i] = new IPByte(this);
        m_mainLayout->addWidget(bytes[i], 0, i + 1, 1, 1, Qt::AlignHCenter);
        connect(bytes[i], SIGNAL(byteChanged(uint8_t)),
                this, SLOT(slotAddressChanged()));
    }
    bytes[0]->focus();

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

    for (int i = 0; i < 3; ++i)
    {
        connect(bytes[i],     SIGNAL(full(bool)),
                bytes[i + 1], SLOT(slotFocus(bool)));
    }

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

    QWidget *widget = new QWidget(this);
    widget->setLayout(m_mainLayout);
    setCentralWidget(widget);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

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
    m_ip->setAddr(bytes[0]->byte() << 24 | bytes[1]->byte() << 16 | bytes[2]->byte() << 8 | bytes[3]->byte());
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
            this, SLOT(close()));
    connect(helpAction, SIGNAL(triggered(bool)),
            this, SLOT(slotHelp()));
}

void MainWindow::slotClear()
{
    foreach (IPByte* b, bytes)
        b->clear();
    bytes[0]->focus();
}

void MainWindow::slotHelp()
{
    QMessageBox box;
    QString text = "A simple tool to calculate network address,"
                   " and broadcast address for given IP and prefix.\n\n"
                   "(C) Victor Dodon, 2012, victor.dodon@cti.pub.ro";
    box.setInformativeText(text);
    box.setMinimumWidth(350);
    box.exec();
    bytes[0]->focus();
}
