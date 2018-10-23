#pragma once
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include "IComms.h"

static const QString SeedEndpoint = "/seed/v1/patients";
static const QString SeedLoginEndpoint = "/seed/v1/users/login";

class Comms : public IComms {
 public:
  Comms();
  ~Comms() = default;

  void SetCommsAddress(QString, QString) override;
  void Login(QString user, QString password) override;
  void GetPatientList() override;
  void PostPatient(Patient patient) override;
  void DeletePatient(int patientId) override;

 private:
  Patient ReadJsonPatient(QJsonObject obj);
  QByteArray CreateJsonPatient(Patient patient);

  void ProcessLogin(QNetworkReply *, QString user);
  void ProcessGetPatientsList(QNetworkReply *);
  void ProcessPostPatient(QNetworkReply *);
  void ProcessDeletePatient(QNetworkReply *);

 private:
  QString ip_;
  QByteArray auth_;
};
