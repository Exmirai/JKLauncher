#include "launcher.h"


SmartConnect::SmartConnect(QObject *sender, const char *signal, void (*pFunc)())
{
    VoidFunc = pFunc;
    QObject::connect(sender,signal,this,SLOT(voidSlot()));
}

void SmartConnect::voidSlot()
{
    VoidFunc();
}
