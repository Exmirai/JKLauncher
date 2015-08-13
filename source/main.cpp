#include "launcher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings::LauncherPath = a.applicationDirPath();
    Settings::Load();
    MainWindow w;
    w.show();
    Starter::Start();
    return a.exec();
}

