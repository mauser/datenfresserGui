#include "newbackupwizard.h"

#include <QVboxLayout>
#include <QGridLayout>

 NewBackupWizard::NewBackupWizard(QWidget *parent) : QWizard(parent)
 {
     addPage(new IntroPage);


     addPage(new BasicsPage);
     /*
     addPage(new CodeStylePage);
     addPage(new OutputFilesPage);
     addPage(new ConclusionPage);
    */

     //setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png"));
     //setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));

     setWindowTitle(tr("Yeee old Wizard"));
 }

  void NewBackupWizard::accept()
 {
      /*
     QByteArray className = field("className").toByteArray();
     QByteArray baseClass = field("baseClass").toByteArray();
     QByteArray macroName = field("macroName").toByteArray();
     QByteArray baseInclude = field("baseInclude").toByteArray();

     QString outputDir = field("outputDir").toString();
     QString header = field("header").toString();
     QString implementation = field("implementation").toString();
    */
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
     setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark1.png"));

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

    /*
     layout->addWidget(qobjectMacroCheckBox, 2, 0, 1, 2);
     layout->addWidget(groupBox, 3, 0, 1, 2);*/
     setLayout(layout);

     /*QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(label);
	setLayout(layout);*/
 }

