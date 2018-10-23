#include "NewPatientDlg.h"
#include "BusinessDefinitions.h"

NewPatientDlg::NewPatientDlg(QObject *parent,
                             std::shared_ptr<IBusiness> &business_logic)
    : QObject(parent), business_logic_(business_logic) {}

void NewPatientDlg::saveNewPatient(QString name, QString surname, QString dob,
                                   QString email, QString coordinates,
                                   QString street, QString city,
                                   QString zipCode) {
  Patient patient;
  patient.name = name;
  patient.surname = surname;
  patient.email = email;
  //    patient.dateOfBirth = dob + "T000000";
  patient.dateOfBirth = "19841212T000000";  // Testing

  PatientAddress address;
  address.coordinates = coordinates;
  address.street = street;
  address.city = city;
  address.zip = zipCode;
  patient.address = address;

  business_logic_->SaveNewPatient(patient);
}
