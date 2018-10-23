#include "Comms.h"
#include <QJsonDocument>
#include <QObject>

Comms::Comms() : ip_(""), auth_("") {}

void Comms::SetCommsAddress(QString ip, QString port) {
  ip_ = ip + ":" + port;
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
  GetPatientList();

  emit LoginSuccess(user);
}

void Comms::GetPatientList() {
  QNetworkAccessManager* manager = new QNetworkAccessManager();

  QNetworkRequest request;
  request.setUrl(QUrl(ip_ + SeedEndpoint));
  request.setRawHeader("Authorization", auth_);
  manager->get(request);
  QObject::connect(
      manager, &QNetworkAccessManager::finished,
      [&](QNetworkReply* reply) { ProcessGetPatientsList(reply); });
};

void Comms::ProcessGetPatientsList(QNetworkReply* reply) {
  QVector<Patient> patients;
  QString errors("");

  if (reply->error() != QNetworkReply::NoError) {
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
    return;
  }

  QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
  QJsonArray jsonArray = jsonDoc.array();

  foreach (const QJsonValue& value, jsonArray) {
    patients.push_back(ReadJsonPatient(value.toObject()));
  }

  emit SendPatients(patients);
}

void Comms::PostPatient(Patient patient) {
  qDebug() << "Comms::PostPatient";
  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QByteArray patientJson = CreateJsonPatient(patient);
  QNetworkRequest request;
  request.setUrl(QUrl(ip_ + SeedEndpoint));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setRawHeader("Authorization", auth_);
  manager->post(request, patientJson);
  QObject::connect(manager, &QNetworkAccessManager::finished,
                   [&](QNetworkReply* reply) { ProcessPostPatient(reply); });
}

void Comms::ProcessPostPatient(QNetworkReply* reply) {
  qDebug() << "Comms::ProcessPostPatient";
  QString errors("");

  if (reply->error() != QNetworkReply::NoError) {
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
    return;
  } else
    GetPatientList();
}

void Comms::DeletePatient(int patientId) {
  qDebug() << "Comms::DeletePatient";
  QNetworkAccessManager* manager = new QNetworkAccessManager();
  QNetworkRequest request;
  request.setUrl(QUrl(ip_ + SeedEndpoint + "/" + QString::number(patientId)));
  request.setRawHeader("Authorization", auth_);
  manager->deleteResource(request);
  QObject::connect(manager, &QNetworkAccessManager::finished,
                   [&](QNetworkReply* reply) { ProcessDeletePatient(reply); });
}

void Comms::ProcessDeletePatient(QNetworkReply* reply) {
  qDebug() << "Comms::ProcessDeletePatient";
  QString errors("");

  if (reply->error() != QNetworkReply::NoError) {
    emit ReportCommsError(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        reply->errorString());
    return;
  } else
    GetPatientList();
}

Patient Comms::ReadJsonPatient(QJsonObject obj) {
  Patient patient;
  patient.id = obj[json_id].toInt();
  patient.name = obj[json_name].toString();
  patient.surname = obj[json_surname].toString();
  patient.email = obj[json_email].toString();
  patient.dateOfBirth = obj[json_dob].toString();

  PatientAddress address;
  QJsonObject add = obj[json_address].toObject();

  address.coordinates = add[json_coordinates].toString();
  address.street = add[json_street].toString();
  address.city = add[json_city].toString();
  address.zip = add[json_zip].toString();
  patient.address = address;

  return patient;
}

QByteArray Comms::CreateJsonPatient(Patient patient) {
  QJsonObject patientObject;
  patientObject.insert(json_name, patient.name);
  patientObject.insert(json_surname, patient.surname);
  patientObject.insert(json_email, patient.email);
  patientObject.insert(json_dob, patient.dateOfBirth);

  QJsonObject addressObject;
  addressObject.insert(json_coordinates, patient.address.coordinates);
  addressObject.insert(json_street, patient.address.street);
  addressObject.insert(json_city, patient.address.city);
  addressObject.insert(json_zip, patient.address.zip);
  patientObject.insert(json_address, addressObject);

  QJsonDocument patientDocument(patientObject);

  return patientDocument.toJson();
}
