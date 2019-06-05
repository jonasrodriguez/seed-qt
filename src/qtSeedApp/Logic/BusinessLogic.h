#pragma once

#include "IComms.h"
#include "IDb.h"
#include "Types.h"
#include <QObject>
#include <memory>

using namespace seed;

class BusinessLogic : public QObject {
  Q_OBJECT
public:
  BusinessLogic();
  ~BusinessLogic() = default;

  void StartUp();
  void ShutDown();

  void LoginUser(QString user, QString pass);
  void LogOut();
  void GetPatientList(int page);
  void SaveNewPatient(const Patient &patient);
  void UpdatePatient(const Patient &patient);
  void DeletePatient(const QString &uid);
  void GetPatientFromList(const Patient &patient);
  void UpdateConfiguration(const CommsConfiguration &conf);
  void GetConfiguration(CommsConfiguration &conf);
  bool IsUserLogger();
  void FillServerDummyPatients();

signals:
  void SendPatientList(const QVariantList &, const int &total_patients,
                       const int &page_number);
  void SendLoginStatus(const bool &loginStatus);
  void SendPatient(const Patient &patient);

public slots:
  void ProcessLoginSuccess(const QString &user);
  void ProcessPatients(const QVariantList &patients, const int &total_patients,
                       const int &page_number);
  void ProcessCommsError(const int &errorCode, const QString &errorSummary);

private:
  std::unique_ptr<IComms> comms_;
  std::unique_ptr<IDb> db_;
  bool is_user_logger_;
};
