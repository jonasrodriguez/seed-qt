#include "BusinessLogic.h"
#include "Comms.h"
#include "DbManager.h"
#include <QDebug>

BusinessLogic::BusinessLogic() : is_user_logger_(false) {
  comms_ = std::unique_ptr<IComms>(new Comms);
  db_ = std::unique_ptr<IDb>(new DbManager);

  QObject::connect(comms_.get(), &IComms::SendPatients, this,
                   &BusinessLogic::ProcessPatients);

  QObject::connect(comms_.get(), &IComms::LoginSuccess, this,
                   &BusinessLogic::ProcessLoginSuccess);

  QObject::connect(comms_.get(), &IComms::ReportCommsError, this,
                   &BusinessLogic::ProcessCommsError);
}

void BusinessLogic::StartUp() {
  db_->StartUp();

  CommsConfiguration conf;
  db_->GetCommConfiguration(conf);
  comms_->SetCommsAddress(conf);

  // Auto Login
  //  comms_->Login("Systelab", "Systelab");
}

void BusinessLogic::ShutDown() {
  QCoreApplication::processEvents();
  db_.reset();
  comms_.reset();
}

void BusinessLogic::LoginUser(QString user, QString pass) {
  comms_->Login(user, pass);
}

void BusinessLogic::ProcessLoginSuccess(const QString &user) {
  QString user_logged(user);
  is_user_logger_ = true;
  emit SendLoginStatus(true);
}

void BusinessLogic::LogOut() { is_user_logger_ = false; }

void BusinessLogic::GetPatientList(int page) { comms_->GetPatientList(page); }

void BusinessLogic::ProcessPatients(const QVector<Patient> &patients,
                                    const int &total_patients,
                                    const int &page_number) {
  emit SendPatientList(patients, total_patients, page_number);
}

void BusinessLogic::SaveNewPatient(const Patient &patient) {
  comms_->PostPatient(patient);
}

void BusinessLogic::UpdatePatient(const Patient &patient) {
  comms_->PutPatient(patient);
}

void BusinessLogic::DeletePatient(const QString &uid) {
  comms_->DeletePatient(uid);
}

void BusinessLogic::ProcessCommsError(const int &errorCode,
                                      const QString &errorSummary) {
  if (errorCode == 401) {
    is_user_logger_ = false;
    emit SendLoginStatus(false);
  }
  qDebug() << "errorCode" << errorCode;
  qDebug() << "errorSummary" << errorSummary;
}

void BusinessLogic::GetPatientFromList(const Patient &patient) {
  emit SendPatient(patient);
}

void BusinessLogic::UpdateConfiguration(const CommsConfiguration &conf) {
  if (db_->UpdateCommConfiguration(conf))
    comms_->SetCommsAddress(conf);
}

void BusinessLogic::GetConfiguration(CommsConfiguration &conf) {
  db_->GetCommConfiguration(conf);
}

bool BusinessLogic::IsUserLogger() { return is_user_logger_; }

//** For testing server pagination only **
// Seed-cpp server currently has no concurrence support
// Be sure to lower the threar pool to one (unsigned int threadPoolSize = 1)
// before using this or it will crash!
void BusinessLogic::FillServerDummyPatients() {
  Patient patient;
  for (int i = 0; i < 10; i++) {
    patient.name = "name" + QString::number(i);
    patient.surname = "surname" + QString::number(i);
    patient.email = "email" + QString::number(i);
    patient.dateOfBirth = "20181231T000000";
    patient.address.coordinates = "cor" + QString::number(i);
    patient.address.street = "street" + QString::number(i);
    patient.address.city = "city" + QString::number(i);
    patient.address.zip = "zip" + QString::number(i);
    comms_->PostPatient(patient);
  }
}
