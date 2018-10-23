#pragma once
#include <memory>
#include "IBusiness.h"
#include "IComms.h"
#include "IDb.h"

class BusinessLogic : public IBusiness {
 public:
  BusinessLogic();
  ~BusinessLogic() = default;

  void StartUp() override;
  void ShutDown() override;

  void LoginUser(QString user, QString pass) override;
  void GetPatientList() override;
  void SaveNewPatient(Patient patient) override;
  void DeletePatient(int patientId) override;

 public slots:
  void ProcessLoginSuccess(QString user) override;
  void ProcessPatients(QVector<Patient> patients) override;
  void ProcessCommsError(int errorCode, QString errorSummary) override;

 private:
  std::unique_ptr<IComms> comms_;
  std::unique_ptr<IDb> db_;
  QString logged_user_;
};
