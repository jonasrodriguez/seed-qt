#include "MessageHelper.h"
#include <QJsonArray>

int MessageHelper::NumberOfPatients(const QJsonDocument &doc) {
  QJsonObject obj = doc.object();
  QJsonValue total = obj.value(json_totalElements);

  return total.toInt();
}

void MessageHelper::ReadPatientContent(const QJsonDocument &doc,
                                       QVector<Patient> &patients,
                                       int &page_number) {

  QJsonObject obj = doc.object();
  page_number = obj.value(json_number).toInt();
  QJsonArray content = obj.value(json_content).toArray();
  foreach (const QJsonValue &value, content) {
    patients.push_back(ReadJsonPatient(value.toObject()));
  }
}

Patient MessageHelper::ReadJsonPatient(const QJsonObject &obj) {
  Patient patient;
  patient.id = obj[json_id].toString();
  patient.name = obj[json_name].toString();
  patient.surname = obj[json_surname].toString();
  patient.email = obj[json_email].toString();
  patient.dateOfBirth = obj[json_dob].toString();

  QJsonObject add = obj[json_address].toObject();

  patient.coordinates = add[json_coordinates].toString();
  patient.street = add[json_street].toString();
  patient.city = add[json_city].toString();
  patient.zip = add[json_zip].toString();
  return patient;
}

QByteArray MessageHelper::CreateJsonPatient(const Patient &patient) {
  QJsonObject patientObject;
  patientObject.insert(json_name, patient.name);
  patientObject.insert(json_surname, patient.surname);
  patientObject.insert(json_email, patient.email);
  patientObject.insert(json_dob, patient.dateOfBirth);

  QJsonObject addressObject;
  addressObject.insert(json_coordinates, patient.coordinates);
  addressObject.insert(json_street, patient.street);
  addressObject.insert(json_city, patient.city);
  addressObject.insert(json_zip, patient.zip);
  patientObject.insert(json_address, addressObject);

  QJsonDocument patientDocument(patientObject);

  return patientDocument.toJson();
}
