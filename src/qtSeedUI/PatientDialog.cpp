#include "PatientDialog.h"
#include "BusinessDefinitions.h"

PatientDialog::PatientDialog(QObject *parent, std::shared_ptr<IBusiness> &business_logic)
    : QObject(parent), business_logic_(business_logic) {
    qpatient_ = std::unique_ptr<PatientHelper>(new PatientHelper);
    qpatient_->setDummyValues();
}

void PatientDialog::saveNewPatient(QString name, QString surname, QString dob,
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

//  business_logic_->SaveNewPatient(patient);
}

void PatientDialog::savePatientInfo(PatientHelper* patient) {
    Patient p = patient->getPatient();
    qDebug() << "Patient name: " << p.name;
    qDebug() << "Patient name: " << p.surname;
}

PatientHelper* PatientDialog::getQPatient() {
  return qpatient_.get();
}
