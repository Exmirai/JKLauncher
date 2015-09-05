#include "launcher.h"


namespace Starter
{
    bool isrunning;
    QProcess *process;
	SmartConnect *onexit;
    void Start(void)
	{
        //TODO: remove magic strings
        QStringList arguments;
        arguments << "+set" << "fs_game" << Modification::currentmod;
		arguments << "+set" << "cl_renderer" << Modification::currentrender;


        process = new QProcess(); //create process instance

		onexit = new SmartConnect(process, SIGNAL(finished(int, QProcess::ExitStatus)), [](void *arg1, void *arg2){
																													qDebug() << (int)arg1;  //ErrorCodes for JKA: 0 success,
																																		    //                    1 manual kill || interrupt signal
																																			//                    2 other signals
																																			//					  3 error
																													qDebug() << (QProcess::ExitStatus*)arg2; 
																												  });

        process->start(Settings::JKFolder + "openjk.x86", arguments);
    }

    void Stop(void)
    {
        if (process != nullptr && process->Running)
        {
            process->kill();
        }
    }
}
