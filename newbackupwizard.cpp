#include "newbackupwizard.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include "database.h"

 NewBackupWizard::NewBackupWizard(QWidget *parent) : QWizard(parent)
 {
     addPage(new IntroPage);
     addPage(new BasicsPage);
     addPage(new ArchivePage);

     /*
     addPage(new OutputFilesPage);
     addPage(new ConclusionPage);
    */

     //setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png"));
     //setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));

     setWindowTitle(tr("Yeee old Wizard"));
 }

  void NewBackupWizard::accept()
 {

     QString remoteLocation = field("remoteLocation").toString();
     QString name = field("name").toString();
     int archiveSchedule = field("archiveSchedule").toInt();
     int schedule = field("schedule").toInt();

     QString scheduleString;
     QString archiveScheduleString;

     if(schedule == 0) scheduleString = "daily";
     if(schedule == 1) scheduleString = "weekly";
     if(schedule == 2) scheduleString = "monthly";

     if(archiveSchedule == 0) archiveScheduleString = "daily";
     if(archiveSchedule == 1) archiveScheduleString = "weekly";
     if(archiveSchedule == 2) archiveScheduleString = "monthly";


     database* d = database::getInstance();
     dataContainer* data = new dataContainer();

     data->setArchiveSchedule( archiveScheduleString );
     data->setSchedule( scheduleString );
     data->setName( name );
     data->setArchiveMethod( "hardlinks" );
     data->setOptions("" );
     data->setComment( "" );
     data->setRemoteLocation( remoteLocation );
     data->setLocalPath( name );

     d->addEntry( data );

     QDialog::accept();
 }


 IntroPage::IntroPage(QWidget *parent)
     : QWizardPage(parent)
 {
     setTitle(tr("Introduction"));
     setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

     label = new QLabel(tr("This wizard will assist you in adding a new backup to your setup."));
     label->setWordWrap(true);

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(label);
     setLayout(layout);
 }

 BasicsPage::BasicsPage(QWidget *parent)
     : QWizardPage(parent)
 {
     setTitle(tr("Basic Settings"));
    // setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

     nameInfoLabel = new QLabel(tr("The name of your backup must be ambiguous. Only letters are allowed!"));
     nameInfoLabel->setWordWrap(true);

     remoteLocationInfoLabel = new QLabel(tr("Example: example.org:/home/jdoe"));
     nameInfoLabel->setWordWrap(true);

     nameLabel = new QLabel(tr("Name:"));
     nameEdit = new QLineEdit;
     nameLabel->setBuddy( nameEdit );

     remoteLocationLabel = new QLabel(tr("Remote location:"));
     remoteLocationEdit = new QLineEdit;
     remoteLocationLabel->setBuddy( remoteLocationEdit );

     QGridLayout *layout = new QGridLayout;
     layout->addWidget(nameLabel, 0, 0);
     layout->addWidget(nameEdit, 0, 1);
     layout->addWidget( nameInfoLabel , 1, 0);
     layout->addWidget(remoteLocationLabel, 2, 0);
     layout->addWidget(remoteLocationEdit, 2, 1);
     layout->addWidget( remoteLocationInfoLabel , 3, 0);

     setLayout(layout);

     registerField("name", nameEdit);
     registerField("remoteLocation", remoteLocationEdit);

 }

 ArchivePage::ArchivePage(QWidget *parent)
     : QWizardPage(parent)
 {
     setTitle(tr("Archiving Settings"));
     //setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

     nameInfoLabel = new QLabel(tr("Choose if your backup should be done daily,weekly or monthly"));
     nameInfoLabel->setWordWrap(true);

     remoteLocationInfoLabel = new QLabel(tr("Choose if your backup should be archived daily,weekly or monthly"));
     nameInfoLabel->setWordWrap(true);

     scheduleLabel = new QLabel(tr("Schedule:"));
     scheduleComboBox = new QComboBox;

     scheduleComboBox->addItem("daily");
     scheduleComboBox->addItem("weekly");
     scheduleComboBox->addItem("monthly");


     scheduleLabel->setBuddy( scheduleComboBox );

     remoteLocationLabel = new QLabel(tr("Archiving schedule:"));
     archiveScheduleBox = new QComboBox;

     archiveScheduleBox->addItem("daily");
     archiveScheduleBox->addItem("weekly");
     archiveScheduleBox->addItem("monthly");

     remoteLocationLabel->setBuddy( archiveScheduleBox );

     QGridLayout *layout = new QGridLayout;
     layout->addWidget(scheduleLabel, 0, 0);
     layout->addWidget(scheduleComboBox, 0, 1);
     layout->addWidget( nameInfoLabel , 1, 0);
     layout->addWidget(remoteLocationLabel, 2, 0);
     layout->addWidget(archiveScheduleBox, 2, 1);
     layout->addWidget( remoteLocationInfoLabel , 3, 0);

     setLayout(layout);

     registerField("schedule", scheduleComboBox);
     registerField("archiveSchedule", archiveScheduleBox);

 }
