#include "launcher.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Settings::LauncherPath = app.applicationDirPath();
    Settings::Load();

	//JKNetAPI::Init();
	//Modification::Init();

    MainWindow mainWindow(&app);
	//QObject::connect(&mainWindow, SIGNAL())
    mainWindow.show();
	
    //Starter::Start();
    return app.exec();
}

