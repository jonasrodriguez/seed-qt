#pragma once
#include "IComms.h"
#include <QNetworkAccessManager>
#include <QtNetwork>

static const QString SeedEndpoint = "/seed/v1/patients";
static const QString SeedLoginEndpoint = "/seed/v1/users/login";

using namespace seed;

class Comms : public IComms {
public:
  Comms();
  ~Comms() = default;

  void SetCommsAddress(const CommsConfiguration &conf) override;
  void Login(QString user, QString password) override;
  void GetPatientList(int page) override;
  void PostPatient(const Patient &patient) override;
  void PutPatient(const Patient &patient) override;
  void DeletePatient(const QString &uid) override;

private:
  void ProcessLogin(QNetworkReply *, QString user);
  void ProcessGetPatientsList(QNetworkReply *);
  void ProcessPostPatient(QNetworkReply *);
  void ProcessPutPatient(QNetworkReply *);
  void ProcessDeletePatient(QNetworkReply *);

private:
  QString ip_;
  QByteArray auth_;
  int page_number_;
  int page_size_;
};
