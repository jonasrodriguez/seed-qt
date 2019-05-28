#ifndef ICOMMS_H
#define ICOMMS_H

#include "Definitions.h"
#include <QObject>

class IComms : public QObject {
  Q_OBJECT
public:
  IComms() = default;
  virtual ~IComms() = default;

  virtual void SetCommsAddress(const seed::CommsConfiguration &conf) = 0;
  virtual QString GetCommsAddres() = 0;
  virtual void Login(QString user, QString password) = 0;
  virtual void GetPatientList(int page) = 0;
  virtual void PostPatient(const seed::Patient &patient) = 0;
  virtual void PutPatient(const seed::Patient &patient) = 0;
  virtual void DeletePatient(const QString &uid) = 0;

signals:
  void SendPatients(QVector<seed::Patient> patients, int total_patients,
                    int page_number);
  void LoginSuccess(QString user);
  void ReportCommsError(int errorCode, QString errorSummary);
};

#endif // ICOMMS_H
