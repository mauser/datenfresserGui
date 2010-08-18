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
    ~database();

    QString getRunningJob();
    QString getLastJob();

    QList<dataContainer> getDataContainer();
    dataContainer getDataContainer( int );

    QList<logEntry> getLogEntries( int dataId );
    logEntry getLogEntry( int logID );

    void addEntry( dataContainer* );

    static database* instance;

    static database* getInstance()
    {
        if( instance == NULL ){
            instance = new database();
        }
        return instance;
    }
};

#endif // DATABASE_H


