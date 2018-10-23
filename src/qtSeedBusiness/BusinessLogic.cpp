#include "BusinessLogic.h"
#include <QDebug>
#include "Comms.h"
#include "DbManager.h"

BusinessLogic::BusinessLogic() : logged_user_("") {
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
  comms_->SetCommsAddress("http://127.0.0.1", "8080");

  //  LoginUser("Systelab","Systelab");
}

void BusinessLogic::ShutDown() {
  QCoreApplication::processEvents();
  db_.reset();
  comms_.reset();
}

void BusinessLogic::LoginUser(QString user, QString pass) {
  comms_->Login(user, pass);
}

void BusinessLogic::ProcessLoginSuccess(QString user) {
  logged_user_ = user;
  emit SendLoginStatus(true);
}

void BusinessLogic::GetPatientList() { comms_->GetPatientList(); }

void BusinessLogic::ProcessPatients(QVector<Patient> patients) {
  emit SendPatientList(patients);
}

void BusinessLogic::SaveNewPatient(Patient patient) {
  comms_->PostPatient(patient);
}

void BusinessLogic::DeletePatient(int patientId) {
  comms_->DeletePatient(patientId);
}

void BusinessLogic::ProcessCommsError(int errorCode, QString errorSummary) {
  if (errorCode == 401) {
    logged_user_ = "";
    emit SendLoginStatus(false);
  }
  qDebug() << "errorCode" << errorCode;
  qDebug() << "errorSummary" << errorSummary;
}
