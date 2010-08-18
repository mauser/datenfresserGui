#include <QFile>
#include <QTextStream>

#include <QDebug>

#include <unistd.h>

#include "helper.h"


helper::helper()
{
}

int helper::getPid()
{
     QFile file( "/var/lib/datenfresser/datenfresser.pid" );
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text )){
         return -1;
     }

     QTextStream in( &file );
     QString line = in.readLine();
     return line.toInt();

}

QString helper::getServerStatus()
{
    if( getpgid( getPid() ) > 0 ){
        return QString("Running");
    } else {
        return QString("Stopped");
    }
}

void helper::startJob( int id )
{
     qDebug() << "trying to start job";
     QFile file( "/var/lib/datenfresser/immediate" );
     if ( file.open( QIODevice::Append | QIODevice::Text )){
	QTextStream out( &file );
	out << QString::number( id  ) << "\n";
    }
}




