#include "launcher.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Settings::LauncherPath = app.applicationDirPath();
    Settings::Load();
    MainWindow mainWindow;
    mainWindow.show();
    Starter::Start();
    return app.exec();
}

