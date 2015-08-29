#pragma once

#include <QMainWindow>
#include <QWidget>

namespace Ui
{
    class MainWindow;
    class Setting;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	QApplication *app;
    explicit MainWindow(QApplication *app,QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
};

