#ifndef IBUSINESS_H
#define IBUSINESS_H

#include "Definitions.h"
#include <QObject>

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
  virtual void SaveNewPatient(const seed::Patient &patient) = 0;
  virtual void UpdatePatient(const seed::Patient &patient) = 0;
  virtual void DeletePatient(const QString &uid) = 0;
  virtual void GetPatientFromList(const seed::Patient &patient) = 0;
  virtual void UpdateConfiguration(const seed::CommsConfiguration &conf) = 0;
  virtual void GetConfiguration(seed::CommsConfiguration &conf) = 0;
  virtual bool IsUserLogger() = 0;
  virtual void FillServerDummyPatients() = 0;

signals:
  void SendPatientList(QVector<seed::Patient> patients, int total_patients,
                       int page_number);
  void SendLoginStatus(bool loginStatus);
  void SendPatient(seed::Patient patient);

public slots:
  virtual void ProcessLoginSuccess(QString user) = 0;
  virtual void ProcessPatients(QVector<seed::Patient> patients,
                               int total_patients, int page_number) = 0;
  virtual void ProcessCommsError(int errorCode, QString errorSummary) = 0;
};

#endif // IBUSINESS_H
