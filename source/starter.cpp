#include "launcher.h"

namespace Starter{
    bool isrunning;
    QProcess *process;


    void Start(void){
        QStringList arguments;
        arguments << "+set" << "fs_game" << "japlus";
        process = new QProcess(); //create process instance
        process->start(Settings::JKFolder + "/openjk.x86", arguments);
        qDebug() << process->errorString();
        qDebug() << Settings::JKFolder;
    }

    void Stop(void){
        if (process != nullptr && process->Running){
            process->kill();
        }

    }
}
