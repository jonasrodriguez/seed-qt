#ifndef IBUSINESS_H
#define IBUSINESS_H

#include <QObject>
#include "BusinessDefinitions.h"

class IBusiness : public QObject {
  Q_OBJECT
 public:
  IBusiness() = default;
  virtual ~IBusiness() = default;

  virtual void StartUp() = 0;
  virtual void ShutDown() = 0;
  virtual void LoginUser(QString user, QString password) = 0;
  virtual void LogOut() = 0;
  virtual void GetPatientList(int page) = 0;
  virtual void SaveNewPatient(const Patient &patient) = 0;
  virtual void UpdatePatient(const Patient &patient) = 0;
  virtual void DeletePatient(const QString &uid) = 0;
  virtual void GetPatientFromList(const Patient &patient) = 0;
  virtual void UpdateConfiguration(const CommsConfiguration &conf) = 0;
  virtual void GetConfiguration(CommsConfiguration &conf) = 0;
  virtual bool IsUserLogger() = 0;

 signals:
  void SendPatientList(QVector<Patient> patients, int total_patients, int page_number);
  void SendLoginStatus(bool loginStatus);
  void SendPatient(Patient patient);

 public slots:
  virtual void ProcessLoginSuccess(QString user) = 0;
  virtual void ProcessPatients(QVector<Patient> patients, int total_patients, int page_number) = 0;
  virtual void ProcessCommsError(int errorCode, QString errorSummary) = 0;
};

#endif  // IBUSINESS_H
