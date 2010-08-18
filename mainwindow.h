#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "database.h"

#include <iostream>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    database *db;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QAction *addAction;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *quitAction;


    void createActions();
    void setupTrayIcon();
    void setupDataTreeWidget();

public slots:
    void startJobButtonClicked();
    void startStopButtonClicked();
    void updateGuiElements();
    void treeItemClicked( QTreeWidgetItem* , int );
    void startServer();
    void stopServer();
    void showWizard();
};

#endif // MAINWINDOW_H
