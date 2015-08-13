#pragma once
#include <QObject>
class SmartConnect : public QObject{
  Q_OBJECT
  void (*VoidFunc)(void);
public:
  SmartConnect(QObject* sender,const char* signal,void (*pFunc)(void));
private slots:
  void voidSlot();
};
