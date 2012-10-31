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

// Qt includes
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QSpinBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

// Local includes
#include "mainwindow.h"
#include "ipbyte.h"
#include "inputfield.h"
#include "ipv4.h"
#include "logarea.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_mainLayout(new QGridLayout()), m_ip(new IPv4())
{
    makeMenus();

    QLabel* ipLabel = new QLabel(this);
    ipLabel->setText("IP address:");
    m_mainLayout->addWidget(ipLabel, 0, 0, 1, 1);

    m_bytes = QVector<IPByte*>(4);

    for (int i = 0; i < 4; ++i)
    {
        m_bytes[i] = new IPByte(this);
        m_mainLayout->addWidget(m_bytes[i], 0, i + 1, 1, 1, Qt::AlignHCenter);
        connect(m_bytes[i], SIGNAL(byteChanged(uint8_t)),
                this, SLOT(slotAddressChanged()));
    }
    m_bytes[0]->focus();

    QLabel* maskLabel = new QLabel(this);
    maskLabel->setText("/");

    QSpinBox* maskBox = new QSpinBox(this);
    maskBox->setMinimum(1);
    maskBox->setMaximum(31);
    maskBox->setValue(8);
    connect(maskBox, SIGNAL(valueChanged(int)),
            this, SLOT(slotMaskChanged(int)));

    m_mainLayout->addWidget(maskLabel, 0, 5, 1, 1);
    m_mainLayout->addWidget(maskBox,   0, 6, 1, 1);

    for (int i = 0; i < 3; ++i)
    {
        connect(m_bytes[i],     SIGNAL(full(bool)),
                m_bytes[i + 1], SLOT(slotFocus(bool)));
    }

    m_mask = QVector<InputField*>(4);
    QLabel* extMaskLabel = new QLabel(this);
    extMaskLabel->setText("Extended mask");
    m_mainLayout->addWidget(extMaskLabel, 1, 0, 1, 1);
    for (int i = 0; i < 4; ++i)
    {
        m_mask[i] = new InputField(this);
        m_mask[i]->setEnabled(false);
        m_mask[i]->setAlignment(Qt::AlignCenter);
        m_mainLayout->addWidget(m_mask[i], 1, i + 1, 1, 1);
    }

    m_netAddr = QVector<InputField*>(4);
    QLabel* netLabel = new QLabel(this);
    netLabel->setText("Network address:");
    m_mainLayout->addWidget(netLabel, 2, 0, 1, 1);
    for (int i = 0; i < 4; ++i)
    {
        m_netAddr[i] = new InputField(this);
        m_netAddr[i]->setEnabled(false);
        m_netAddr[i]->setAlignment(Qt::AlignCenter);
        m_mainLayout->addWidget(m_netAddr[i], 2, i + 1, 1, 1);
    }

    m_broadcastAddr = QVector<InputField*>(4);
    QLabel* bcastAddr = new QLabel(this);
    bcastAddr->setText("Broadcast address:");
    m_mainLayout->addWidget(bcastAddr, 3, 0, 1, 1);
    for (int i = 0; i < 4; ++i)
    {
        m_broadcastAddr[i] = new InputField(this);
        m_broadcastAddr[i]->setEnabled(false);
        m_broadcastAddr[i]->setAlignment(Qt::AlignCenter);
        m_mainLayout->addWidget(m_broadcastAddr[i], 3, i + 1, 1, 1);
    }

    m_logArea = new LogArea(this);
    m_logArea->setFixedHeight(100);

    m_mainLayout->addWidget(m_logArea, 4, 0, 1, 7);

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
    m_ip->setAddr(m_bytes[0]->byte() << 24 | m_bytes[1]->byte() << 16 | m_bytes[2]->byte() << 8 | m_bytes[3]->byte());
    updateAdresses();
}

void MainWindow::updateAdresses()
{
    uint32_t mask = m_ip->netMask();
    for (int i = 0; i < 4; ++i)
    {
        m_mask[i]->setText(QString("%1").arg(mask >> (24 - i * 8) & 0xFF));
        m_netAddr[i]->setText(QString("%1").arg(m_ip->networkAddress() >> (24 - i * 8) & 0xFF));
        m_broadcastAddr[i]->setText(QString("%1").arg(m_ip->broadcastAddress() >> (24 - i * 8) & 0xFF));
    }
    m_logArea->appendMessage(m_ip->message());
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
    foreach (IPByte* b, m_bytes)
        b->clear();
    m_bytes[0]->focus();
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
    m_bytes[0]->focus();
}
