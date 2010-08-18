#include <QProcess>
#include <QTimer>
#include <QDebug>

#include "mainwindow.h"
#include "database.h"
#include "ui_mainwindow.h"
#include "newbackupwizard.h"

#include "helper.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    db = database::getInstance();

    ui->setupUi(this);
    ui->statusLabel->setText( helper::getServerStatus() );
    connect( ui->startStopButton, SIGNAL( clicked() ), this, SLOT( startStopButtonClicked() ) );
    updateGuiElements();

    QTimer *timer = new QTimer( this );
    connect(timer, SIGNAL(timeout()), this, SLOT( updateGuiElements()));

    connect( ui->startJobButton , SIGNAL( clicked() ), this, SLOT(startJobButtonClicked()) );

    setupTrayIcon();
    setupDataTreeWidget();
    connect( ui->dataTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT( treeItemClicked(QTreeWidgetItem*, int)) );

    timer->start( 1000 );

    startServer();
}

MainWindow::~MainWindow()
{
    delete database::getInstance();
    delete ui;
}

void MainWindow::startJobButtonClicked(){
	QList<QTreeWidgetItem*> list = ui->dataTreeWidget->selectedItems();

	QList<QTreeWidgetItem*>::iterator i;
	for (i = list.begin(); i != list.end(); ++i){
	    dataContainer data = db->getDataContainer( (*i)->text( 1 ).toInt() );
	    helper::startJob( data.getDataId() );
	}
}

void MainWindow::treeItemClicked( QTreeWidgetItem* item, int i){
    if( item->parent() != NULL ){

	ui->tabWidget->setCurrentIndex( 1 );

	logEntry log = db->getLogEntry( item->text( 1 ).toInt() );

	ui->jobStatusLabel->setText( log.getStatus() );
	ui->dateLabel->setText( item->text( 0 ) );
	ui->textBrowser->setText( log.getErrorMessage() );
	ui->dataSizeLabel->setText( log.getSize() + "kb" );

    } else {

	ui->tabWidget->setCurrentIndex( 0 );
	dataContainer data = db->getDataContainer( item->text( 1 ).toInt() );

	ui->locationLabel->setText( data.getName() );
	ui->remoteLocationLabel->setText( data.getRemoteLocation() );
	ui->lastBackupLabel->setText( "" );

    }
}


void MainWindow::createActions()
{
    addAction = new QAction(tr("Add new backup"), this);
    connect(addAction, SIGNAL(triggered()), this, SLOT(showWizard()));

    minimizeAction = new QAction(tr("Hide"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("Show"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}



void MainWindow::setupTrayIcon()
{
    createActions();

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(addAction);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu( trayIconMenu  );

    trayIcon->setIcon( QIcon("datenfresserGui.app/Contents/Resources/bad.svg") );
    trayIcon->show();
}

void MainWindow::setupDataTreeWidget()
{
	QList<dataContainer> results = db->getDataContainer();
	QList<dataContainer>::iterator i;

	for (i = results.begin(); i != results.end(); ++i){
	    QTreeWidgetItem *dataContainer = new QTreeWidgetItem( ui->dataTreeWidget );

	    if( ui->locationLabel->text().isEmpty() ){
		//init overview tab
		ui->locationLabel->setText( (*i).getName() );
		ui->remoteLocationLabel->setText( (*i).getRemoteLocation() );
		ui->lastBackupLabel->setText( "" );
	    }

	    dataContainer->setText(0, (*i).getName() );
	    dataContainer->setText(1, QString::number( (*i).getDataId() ));

	    QList<logEntry> logs = db->getLogEntries( (*i).getDataId() );
	    QList<logEntry>::iterator ii;

	    for (ii = logs.begin(); ii != logs.end(); ++ii){
		QTreeWidgetItem *treeItem = new QTreeWidgetItem( dataContainer );
		int id = (*ii).getLogId();
		QDateTime t = QDateTime::fromTime_t( (*ii).getEndTimestamp() );
		treeItem->setText(0, t.toString() );
		treeItem->setText(1, QString::number( id ) );
	    }
	}
}


void MainWindow::updateGuiElements()
{
    if( helper::getServerStatus() == "Running" ){
        ui->statusLabel->setText("Server is running");
        ui->startStopButton->setText("Stop");
    } else {
        ui->startStopButton->setText("Start");
        ui->statusLabel->setText("Server is stopped");
    }

    ui->currentJob->setText( db->getRunningJob() );

}

void MainWindow::startStopButtonClicked()
{
    if( helper::getServerStatus() == "Running" ){
	stopServer();
	updateGuiElements();
    } else {
	startServer();
	updateGuiElements();
    }
}

void MainWindow::startServer(  )
{
	QProcess *startDatenfresser = new QProcess( this );
	startDatenfresser->start( "/Users/sebastian/src/datenfresser/datenfresser.py" );
	startDatenfresser->waitForStarted();
}

void MainWindow::stopServer(  )
{
	qDebug() << "kill!" << QString::number( helper::getPid()) ;
	QProcess *kill = new QProcess( this );
	kill->start("kill", QStringList() << QString::number( helper::getPid()) );
}

void MainWindow::showWizard(){
    NewBackupWizard* wiz = new NewBackupWizard();
    wiz->show();
}
