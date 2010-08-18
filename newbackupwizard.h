#ifndef NEWBACKUPWIZARD_H
#define NEWBACKUPWIZARD_H

#include <QtGui>
#include <QWizard>
#include <QLabel>

class NewBackupWizard : public QWizard
 {
     Q_OBJECT

 public:
     NewBackupWizard(QWidget *parent = 0);

     void accept();
 };

class IntroPage : public QWizardPage
 {
     Q_OBJECT

 public:
     IntroPage(QWidget *parent = 0);

 private:
     QLabel *label;
 };

class BasicsPage : public QWizardPage
 {
     Q_OBJECT

 public:
     BasicsPage(QWidget *parent = 0);

 private:
     QLabel *nameInfoLabel;
     QLabel *nameLabel;
     QLabel *remoteLocationInfoLabel;
     QLabel *remoteLocationLabel;


     QLineEdit* nameEdit;
     QLineEdit* remoteLocationEdit;
 };


class ArchivePage : public QWizardPage
 {
     Q_OBJECT

 public:
     ArchivePage(QWidget *parent = 0);

 private:
     QLabel *nameInfoLabel;
     QLabel *scheduleLabel;
     QLabel *remoteLocationInfoLabel;
     QLabel *remoteLocationLabel;


     QComboBox* scheduleComboBox;
     QComboBox* archiveScheduleBox;
 };


#endif // NEWBACKUPWIZARD_H
