#include "PatientDialog.h"
#include "BusinessDefinitions.h"

PatientDialog::PatientDialog(QObject *parent, std::shared_ptr<IBusiness> &business_logic)
    : QObject(parent), business_logic_(business_logic), new_patient_(true) {

    patient_helper_ = std::unique_ptr<PatientHelper>(new PatientHelper);
    QObject::connect(business_logic_.get(), &IBusiness::SendPatient,
                     this, &PatientDialog::GetPatientInfoFromList);
}

void PatientDialog::savePatientInfo(PatientHelper* patient) {
    Patient p = patient->getPatient();
    if (new_patient_)
        business_logic_->SaveNewPatient(p);
    else
        business_logic_->UpdatePatient(p);
}

PatientHelper* PatientDialog::getQPatient() {
  return patient_helper_.get();
}

void PatientDialog::GetPatientInfoFromList(Patient patient) {
  new_patient_ = false;
  patient_helper_->setPatient(patient);
}

void PatientDialog::clearPatientDialog() {
  new_patient_ = true;
  patient_helper_->initializePatient();
}
