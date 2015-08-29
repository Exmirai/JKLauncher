#pragma once

//FIXME
#include <QObject>

class SmartConnect : public QObject
{
    Q_OBJECT

public:
    explicit SmartConnect(QObject* sender,const char* signal,void (*pFunc)(void));
	explicit SmartConnect(QObject* sender, const char* signal, void(*pFunc)(void*));
	explicit SmartConnect(QObject* sender, const char* signal, void(*pFunc)(void*, void*));

    void (*VoidFunc)(void);
	void(*PtrFunc)(void *arg1);
	void(*Ptr2Func)(void *arg1, void *arg2);

private slots:
    void voidSlot();
	void PtrSlot(void*);
	void Ptr2Slot(void*, void*);
};
