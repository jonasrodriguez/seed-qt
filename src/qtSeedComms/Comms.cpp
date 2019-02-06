#include "Comms.h"
#include "MessageHelper.h"
#include <QObject>
#include <QDebug>


Comms::Comms() : ip_(""), auth_(""), page_number_(0), page_size_(20) {}

void Comms::SetCommsAddress(const CommsConfiguration &conf) {
  ip_ = "http://" + conf.ip + ":" + QString::number(conf.port);
};

void Comms::Login(QString user, QString password) {
  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QNetworkRequest request;  
  request.setUrl(QUrl(ip_ + SeedLoginEndpoint));
  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    "application/x-www-form-urlencoded");
  QByteArray loginInfo =
      QString("login=" + user + "&password=" + password).toLocal8Bit();
  manager->post(request, loginInfo);
  QObject::connect(manager, &QNetworkAccessManager::finished,
                   [=](QNetworkReply* reply) { ProcessLogin(reply, user); });
}

void Comms::ProcessLogin(QNetworkReply* reply, QString user) {
  if (reply->error() != QNetworkReply::NoError) {
    auth_ = "";
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
    return;
  }
  auth_ = reply->rawHeader("Authorization");
  GetPatientList(0);

  emit LoginSuccess(user);
}

void Comms::GetPatientList(int page) {
  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QString pagination("");
  if (page >= 0) {
       pagination = "?page=" + QString::number(page) + "&size=" + QString::number(page_size_);
  }
  QNetworkRequest request;
  request.setUrl(QUrl(ip_ + SeedEndpoint + pagination));
  request.setRawHeader("Authorization", auth_);
  manager->get(request);
  QObject::connect(
      manager, &QNetworkAccessManager::finished,
      [&](QNetworkReply* reply) { ProcessGetPatientsList(reply); });
};

void Comms::ProcessGetPatientsList(QNetworkReply* reply) {
  QString errors("");

  if (reply->error() != QNetworkReply::NoError) {
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
    return;
  }

  QVector<Patient> patients;
  int page_number = 0;
  int total_patients;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
  total_patients = MessageHelper::NumberOfPatients(jsonDoc);
  if (total_patients > 0) {
    MessageHelper::ReadPatientContent(jsonDoc, patients, page_number);
  }

  emit SendPatients(patients, total_patients, page_number);
}

void Comms::PostPatient(const Patient &patient) {
  qDebug() << "Comms::PostPatient";
  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QByteArray patientJson = MessageHelper::CreateJsonPatient(patient);
  QNetworkRequest request;
  request.setUrl(QUrl(ip_ + SeedEndpoint + "/patient"));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setRawHeader("Authorization", auth_);
  manager->post(request, patientJson);
  QObject::connect(manager, &QNetworkAccessManager::finished,
                   [&](QNetworkReply* reply) { ProcessPostPatient(reply); });
}

void Comms::ProcessPostPatient(QNetworkReply* reply) {
  qDebug() << "Comms::ProcessPostPatient";
  if (reply->error() != QNetworkReply::NoError) {
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
  } else
    GetPatientList(0);
}

void Comms::PutPatient(const Patient &patient) {
  qDebug() << "Comms::PutPatient";
  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QByteArray patientJson = MessageHelper::CreateJsonPatient(patient);
  QNetworkRequest request;
  request.setUrl(QUrl(ip_ + SeedEndpoint + "/" + patient.id));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setRawHeader("Authorization", auth_);
  manager->put(request, patientJson);
  QObject::connect(manager, &QNetworkAccessManager::finished,
                   [&](QNetworkReply* reply) { ProcessPutPatient(reply); });
}

void Comms::ProcessPutPatient(QNetworkReply* reply) {
  qDebug() << "Comms::ProcessPutPatient";
  if (reply->error() != QNetworkReply::NoError) {
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
  } else
    GetPatientList(0);
}

void Comms::DeletePatient(const QString &uid) {
  qDebug() << "Comms::DeletePatient";
  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QNetworkRequest request;
  request.setUrl(QUrl(ip_ + SeedEndpoint + "/" + uid));
  request.setRawHeader("Authorization", auth_);
  manager->deleteResource(request);
  QObject::connect(manager, &QNetworkAccessManager::finished,
                   [&](QNetworkReply* reply) { ProcessDeletePatient(reply); });
}

void Comms::ProcessDeletePatient(QNetworkReply* reply) {
  qDebug() << "Comms::ProcessDeletePatient";
  if (reply->error() != QNetworkReply::NoError) {
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
  } else
    GetPatientList(0);
}
