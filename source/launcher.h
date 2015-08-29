#pragma once

#include <QApplication>
#include <QString>
#include <QImage>
#include <QMap>
#include <QProcess>
#include <QDebug>
#include <QHostAddress>
#include <QTime>
#include <QList>
#include <QThread>
#include <QtConcurrent>

#include <QUdpSocket>
#include <QTcpSocket>

#include "smartconnect.h"
#include "settings.h"
#include "mainwindow.h"
#include "profiles.h"
#include "starter.h"
#include "serverapi.h"
#include "jknetapi.h"
#include "workshop.h"

#define QStringPTChar(x) (x)->toLocal8Bit().data()
#define QStringTChar(x) (x).toLocal8Bit().data()
