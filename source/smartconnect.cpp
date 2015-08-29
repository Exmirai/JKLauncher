#include "launcher.h"


SmartConnect::SmartConnect(QObject *sender, const char *signal, void (*pFunc)(void))
{
    VoidFunc = pFunc;
    QObject::connect(sender,signal,this,SLOT(voidSlot()));
}

SmartConnect::SmartConnect(QObject *sender, const char *signal, void(*pFunc)(void*))
{
	PtrFunc = pFunc;
	QObject::connect(sender, signal, this, SLOT(PtrSlot()));
}

SmartConnect::SmartConnect(QObject *sender, const char *signal, void(*pFunc)(void*, void*))
{
	Ptr2Func = pFunc;
	QObject::connect(sender, signal, this, SLOT(Ptr2Slot()));
}

void SmartConnect::voidSlot()
{
   this->VoidFunc();
}

void SmartConnect::PtrSlot(void* arg1)
{
	this->PtrFunc(arg1);
}

void SmartConnect::Ptr2Slot(void* arg1, void *arg2)
{
	this->Ptr2Func(arg1, arg2);
}
