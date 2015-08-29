#include "launcher.h"

#include "ui_mainwindow.h"
#include "ui_settings.h"

MainWindow::MainWindow(QApplication *app,QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
	this->app = app;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
    Settings::Save();
	//app->quit();
}
