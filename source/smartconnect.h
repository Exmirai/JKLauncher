#pragma once

//FIXME
#include <QObject>

class SmartConnect : public QObject
{
    Q_OBJECT

public:
    SmartConnect(QObject* sender,const char* signal,void (*pFunc)(void));
    void (*VoidFunc)(void);

private slots:
    void voidSlot();
};
