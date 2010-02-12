#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QList>


#include "helper.h"



class database
{
private:
    QSqlDatabase db;
public:
    database();
    QString getRunningJob();
    QString getLastJob();

    QList<dataContainer> getDataContainer();
    dataContainer getDataContainer( int );

    QList<logEntry> getLogEntries( int dataId );
    logEntry getLogEntry( int logID );

};

#endif // DATABASE_H


