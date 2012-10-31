#include "logarea.h"

LogArea::LogArea(QWidget *parent) :
    QTextEdit(parent)
{
    setFixedHeight(60);
    setReadOnly(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void LogArea::appendMessage(const QString &msg)
{
    append(msg);
}
