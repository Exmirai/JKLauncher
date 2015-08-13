#pragma once

#include <QApplication>
#include <QString>
#include <QImage>
#include <QMap>
#include <QProcess>
#include <QDebug>

#include "smartconnect.h"
#include "settings.h"
#include "mainwindow.h"
#include "profiles.h"
#include "network.h"
#include "starter.h"

#define QStringPTChar(x) x->toLocal8Bit().data()
#define QStringTChar(x) x.toLocal8Bit().data()
