#include "database.h"

#include <QtSql>
#include <QString>
#include <QDebug>


#include <iostream>

database* database::instance = NULL;

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( "/var/lib/datenfresser/datenfresser.db" );
    if( db.open() == false )
    {
	qDebug() << "Can not open database";
    }
}

database::~database()
{
    db.close();
    qDebug() << "closing db";
}




void database::addEntry( dataContainer* c ){

    QSqlQuery query;

    query.prepare( "INSERT INTO datacontainer(name,comment,localPath,remotePath,type,options,schedule,archive,archive_method) VALUES (:name,:comment,:local,:remote,'rsync',:options,:schedule,:archive_schedule,:archive_method)");

    query.bindValue( ":name",c->getName() );
    query.bindValue( ":local",c->getLocalPath() );
    query.bindValue(":comment" , c->getComment() );
    query.bindValue(":remote", c->getRemoteLocation() );
    query.bindValue(":options", c->getOptions() );
    query.bindValue(":schedule", c->getSchedule() );
    query.bindValue(":archive_schedule", c->getArchiveSchedule() );
    query.bindValue(":archive_method", c->getArchiveMethod() );

    if(!query.exec())
    {
        qDebug() << "> Query exec() error." << query.lastError();
    } else {
        qDebug() << ">Query exec() success.";
    }

}

QList<logEntry> database::getLogEntries( int dataID )
{
    QString sql = "SELECT logID, type, dataID, start_timestamp, end_timestamp, status, err_msg, transferredData FROM log WHERE type = 'rsync' AND dataID=" + QString::number( dataID ) + " ORDER BY start_timestamp desc";
    QSqlQuery query(sql, db);

    QList<logEntry> list;
    while ( query.next() ) {
	logEntry log;

	log.setLogId( query.value( 0 ).toInt() );
	log.setType( query.value( 1 ).toString() );
	log.setDataId( query.value(2).toInt() );
	log.setStartTimestamp( query.value( 3 ).toDouble() );
	log.setEndTimestamp( query.value( 4 ).toDouble() );
	log.setStatus( query.value( 5 ).toString() );
	log.setErrorMessage( query.value( 6 ).toString() );
	log.setSize( query.value( 7 ).toString() );

	list.append( log );
    }

    return list;
}


logEntry database::getLogEntry( int logId)
{
    QString sql = "SELECT logID, type, dataID, start_timestamp, end_timestamp, status, err_msg, transferredData FROM log WHERE logID=" + QString::number( logId );
    QSqlQuery query(sql, db);

    logEntry log;

    while ( query.next() ) {

	log.setLogId( query.value( 0 ).toInt() );
    	log.setType( query.value( 1 ).toString() );
	log.setDataId( query.value(2).toInt() );
	log.setStartTimestamp( query.value( 3 ).toDouble() );
	log.setEndTimestamp( query.value( 4 ).toDouble() );
	log.setStatus( query.value( 5 ).toString() );
	log.setErrorMessage( query.value( 6 ).toString() );
	log.setSize( query.value( 7 ).toString() );

    }
    return log;
}


QList<dataContainer> database::getDataContainer()
{
    QString sql = "SELECT name, dataID, remotePath  FROM dataContainer";
    QSqlQuery query(sql, db);

    QList<dataContainer> list;

    while ( query.next() ) {
	dataContainer data;
	data.setName( query.value( 0 ).toString() );
	data.setDataId( query.value( 1 ).toInt() );
	data.setRemoteLocation( query.value( 2 ).toString() );
	list.append( data );
    }

    return list;
}

dataContainer database::getDataContainer( int ID )
{
    QString sql = "SELECT name, dataID, remotePath FROM dataContainer WHERE dataContainer.dataID = " + QString::number( ID );
    QSqlQuery query(sql, db);

    dataContainer data;

    while ( query.next() ) {
	data.setName( query.value( 0 ).toString() );
	data.setDataId( ID );
	data.setRemoteLocation( query.value( 2 ).toString() );
    }
    return data;
}


QString database::getRunningJob()
{

    QString sql = "SELECT log.logID , log.start_timestamp, dataContainer.name FROM log,dataContainer WHERE log.status='running' AND log.dataID = dataContainer.dataID ";
    QSqlQuery query(sql, db);
    while ( query.next() ) {
	QString name = query.value( 2 ).toString();
	return name;
    }
    return QString("No Job running");

}



 QString database::getLastJob(){

    QString sql="SELECT logID from log where type='rsync' ORDER BY start_timestamp DESC LIMIT 1";
    QSqlQuery query(sql, db);
    while ( query.next() ) {
	QString id = query.value( 0 ).toString();
	return id;
    }
    return QString("No Job running");

}
