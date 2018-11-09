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
  void LogOut() override;
  void GetPatientList(int page) override;
  void SaveNewPatient(const Patient &patient) override;
  void UpdatePatient(const Patient &patient) override;
  void DeletePatient(const QString &uid) override;
  void GetPatientFromList(const Patient &patient) override;
  void UpdateConfiguration(const CommsConfiguration &conf) override;
  void GetConfiguration(CommsConfiguration &conf) override;
  bool IsUserLogger() override;

 public slots:
  void ProcessLoginSuccess(QString user) override;
  void ProcessPatients(QVector<Patient> patients, int total_patients, int page_number) override;
  void ProcessCommsError(int errorCode, QString errorSummary) override;

 private:
  std::unique_ptr<IComms> comms_;
  std::unique_ptr<IDb> db_;
  bool is_user_logger_;
};
