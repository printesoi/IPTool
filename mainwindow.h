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
