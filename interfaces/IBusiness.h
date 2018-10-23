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
  virtual void GetPatientList() = 0;
  virtual void SaveNewPatient(Patient patient) = 0;
  virtual void DeletePatient(int patientId) = 0;

 signals:
  void SendPatientList(QVector<Patient> patients);
  void SendLoginStatus(bool loginStatus);

 public slots:
  virtual void ProcessLoginSuccess(QString user) = 0;
  virtual void ProcessPatients(QVector<Patient> patients) = 0;
  virtual void ProcessCommsError(int errorCode, QString errorSummary) = 0;
};

#endif  // IBUSINESS_H
