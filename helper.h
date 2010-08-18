#ifndef HELPER_H
#define HELPER_H

#include <QTreeWidgetItem>

class dataContainer
{
    public:

	QString getName(){
	    return name;
	}

	void setDataId( int id ){
	    dataId = id;
	}

	int getDataId(){
	    return dataId;
	}

	int getLastJobId(){
	    return lastJobId;
	}

	void setLastJobId( int id){
	    lastJobId = id;
	}

	QString getRemoteLocation(){
	    return remoteLocation;
	}

	QString getLocation(){
	    return location;
	}

        QString getComment(){
            return comment;
        }


	void setName( QString Name){
	    name = Name;
	}

	void setRemoteLocation( QString Location ){
	    remoteLocation = Location;
	}

	void setLocation( QString Location ){
	    location = Location;
	}

        void setComment( QString Comment){
            comment = Comment;
        }


        void setArchiveMethod( QString method){
            archiveMethod = method;
        }

        void setArchiveSchedule( QString schedule ){
            archiveSchedule = schedule;
        }

        void setSchedule( QString schedule ){
            this->schedule = schedule;
        }

        void setOptions( QString options){
            this->options = options;
        }

        QString getOptions(){
            return this->options;
        }

        QString getArchiveSchedule(){
            return this->archiveSchedule;
        }

        QString getSchedule(){
            return this->schedule;
        }

        QString getArchiveMethod(){
            return this->archiveMethod;
        }

        QString getLocalPath(){
            return this->localPath;
        }

        void setLocalPath(QString path){
            this->localPath = path;
        }

    private:
	int dataId;
	int lastJobId;

	QString name;
        QString comment;
	QString remoteLocation;
        QString localPath;
	QString	archiveMethod;
	QString archiveSchedule;
        QString schedule;
        QString options;
        QString location;

};

class logEntry
{
    public:

	QString getSize(){
	    return size;
	}

	void setSize( QString Size ){
	    size = Size;
	}

	void setStartTimestamp( double Timestamp ){
	    startTimestamp = Timestamp;
	}

	void setDataId( int ID){
	    dataId = ID;
	}

	void setLogId( int ID){
	    logId = ID;
	}

	void setEndTimestamp( double EndTimestamp ){
	    endTimestamp = EndTimestamp;
	}

	void setType( QString Type){
	    type = Type;
	}

	void setErrorMessage( QString Error ){
	    errorMessage = Error;
	}

	void setStatus( QString Status ){
	    status = Status;
	}

	QString getErrorMessage(){
	    return errorMessage;
	}

	double getStartTimestamp(){
	    return startTimestamp;
	}

	double getEndTimestamp(){
	    return endTimestamp;
	}

	QString getType(){
	    return type;
	}

	QString getStatus(){
	    return status;
	}

	int getDataId(){
	    return dataId;
	}

	int getLogId(){
	    return logId;
	}


    private:
	double startTimestamp;
	double endTimestamp;

	int dataId;
	int logId;

	QString size;
	QString errorMessage;
	QString type;
	QString status;
};


class helper
{
    public:
	helper();
	static int getPid();
	static QString getServerStatus();
	static void startJob( int Id );
};

class dataWidgetItem : public QTreeWidgetItem {
    public:
	void setDataId( int Id){
	    dataId = Id;
	}

	int getDataId() {
	    return dataId;
	}

    private:
	int dataId;
};

#endif // HELPER_H
