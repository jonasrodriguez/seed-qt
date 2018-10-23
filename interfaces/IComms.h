#ifndef ICOMMS_H
#define ICOMMS_H

#include <QObject>
#include "BusinessDefinitions.h"

class IComms : public QObject {
  Q_OBJECT
 public:
  IComms() = default;
  virtual ~IComms() = default;

  virtual void SetCommsAddress(QString ip, QString port) = 0;
  virtual void Login(QString user, QString password) = 0;
  virtual void GetPatientList() = 0;
  virtual void PostPatient(Patient patient) = 0;
  virtual void DeletePatient(int patientId) = 0;

 signals:
  void SendPatients(QVector<Patient> patients);
  void LoginSuccess(QString user);
  void ReportCommsError(int errorCode, QString errorSummary);
};

#endif  // ICOMMS_H
